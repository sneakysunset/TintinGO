#include "GridManager.h"

#include "MainGameMode.h"
#include "Tile.h"
#include "TileActor.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


AGridManager::AGridManager()
{
	PrimaryActorTick.bCanEverTick = true;
	_rows = 10;
	_columns = 10;
	_tileWidth = 1;
	_useEditorTick = true;
}

void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}
#endif
}

void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	_gameManager = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	_gameManager->_tileWidth = _tileWidth;
}

bool AGridManager::ShouldTickIfViewportsOnly() const
{
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor && _useEditorTick)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AGridManager::BlueprintEditorTick(float DeltaTime)
{
}

//Creates Grid.
void AGridManager::InitializeGrid()	
{
	TArray<AActor*> tiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATile::StaticClass(), tiles);
	for (const auto& tile : tiles)
	{
		tile->Destroy();
	}

	// Clear the grid array
	tiles.Empty();

	UE_LOG(LogTemp, Warning, TEXT("Initialization"));
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			FActorSpawnParameters SpawnParams;
			FVector SpawnLocation = FVector(i * 100 * _tileWidth, j * 100 * _tileWidth , 0);
			FRotator SpawnRotation = FRotator(0, 0, 0);
			ATile* SpawnedTile = GetWorld()->SpawnActor<ATile>(_tileBP->GeneratedClass, SpawnLocation, SpawnRotation, SpawnParams);
#if WITH_EDITOR
			SpawnedTile->SetActorLabel(FString::Printf(TEXT("Tile_%d_%d"), static_cast<int>(i), static_cast<int>(j)));
#endif
			SpawnedTile->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
			SpawnedTile->SetActorLocation(SpawnLocation);
			SpawnedTile->_row = i;
			SpawnedTile->_column = j;
			SpawnedTile->SetActorScale3D(FVector(_tileWidth, _tileWidth, 1));
			//SpawnedTile->SetHighlighted(false);
		}
	}
}

//Update the links around tile in editor.
void AGridManager::UpdateLinks()
{
	TArray<AActor*> ActorsToFind;
	TArray<ATile*> tiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATile::StaticClass(), ActorsToFind);
	_gridTiles.Empty();
	_rows = 0;
	_columns = 0;
	for (int i = 0; i < ActorsToFind.Num(); i++)
	{
		ATile* tile = Cast<ATile>(ActorsToFind[i]);
		if(tile->_row > _rows) _rows = tile->_row;
		if(tile->_column > _columns) _columns = tile->_column;
		tiles.Add(tile);
	}
	_rows++;
	_columns++;
	for(int i = 0; i < _rows; i++)
	{
		_gridTiles.Add(FTileArray());
		for(int j = 0; j < _columns; j++)
		{
			_gridTiles[i].Tiles.Add(nullptr);
		}
	}
	
	//UE_LOG(LogTemp, Error, TEXT("TEST %d %d" ), _gridTiles.Num(), _gridTiles[0].Tiles.Num());
	
	for(int i = 0; i < tiles.Num(); i++)
	{
		_gridTiles[tiles[i]->_row].Tiles[tiles[i]->_column] = tiles[i];
		//UE_LOG(LogTemp, Error, TEXT("TEST %d %d" ),tiles[i]->_row, tiles[i]->_column);
	}
	//UE_LOG(LogTemp, Error, TEXT("TEST %d %d" ), _gridTiles.Num(), _gridTiles[0].Tiles.Num());
	/*for(auto tileRow : _gridTiles)
	{
		for(auto tile : tileRow.Tiles)
		{
			tile->RefreshLinks();
			//UE_LOG(LogTemp, Error, TEXT("TEST %d %d %d %d" ), _rows, _columns, tile->_row, tile->_column);
		}
	}*/
	for(int i = 0; i < _gridTiles.Num(); i++)
	{
		for(int j = 0; j < _gridTiles[i].Tiles.Num(); j++)
		{
			//UE_LOG(LogTemp, Error, TEXT("TEST %d %d" ), _gridTiles[i].Tiles[j]->_row,_gridTiles[i].Tiles[j]-> _column);
			_gridTiles[i].Tiles[j]->_gridManager = this;
			_gridTiles[i].Tiles[j]->RefreshLinks();
		}
	}

	_gridTiles.Empty(true);
}

//Old duplicate function from AGameManager but that I also use in editor so i kept it here.
ATile* AGridManager::GetTile(int32 i, int32 j)
{
	if (i >= 0 && i < _gridTiles.Num() && j >= 0 && j < _gridTiles[i].Tiles.Num())
	{
		if(!IsValid(_gridTiles[i].Tiles[j]))
		{
			UE_LOG(LogTemp, Warning, TEXT("ERROR TILE : %d %d"), i, j );
			return nullptr;
		}
		return _gridTiles[i].Tiles[j];
	}

	return nullptr;
}