#include "GridManager.h"

#include "Barrier.h"
#include "GameManager.h"
#include "State_TA_Move.h"
#include "Tile.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_Clue.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AGridManager* AGridManager::SingletonInstance = nullptr;

AGridManager* AGridManager::GetInstance() 
{
	return SingletonInstance;
}

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
	//UE_LOG(LogTemp, Warning, TEXT("Test"));
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}

#endif

}

void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	SingletonInstance = this;
	
	/*TArray<AActor*> ActorsToFind;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATileActor::StaticClass(), ActorsToFind);
	for(auto actor : ActorsToFind)
	{
		Destroy(actor);
	}*/
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

void AGridManager::ChangeTile(UBarrier* barrier, ATile* previousTile, ATile* currentTile)
{
	if(IsValid(previousTile))
	{
		for(auto body : previousTile->_tileActors)
		{
			if(body == nullptr) continue;
			UState_TActor* state = NewObject<UState_TA_Move>(UState_TA_Move::StaticClass());
			
			if(!barrier->_actors.Contains(body))
			{
				body->ChangeState(state);
				barrier->_actors.Add(body);
			}
		}
	}

	if(IsValid(currentTile))
	{
		for(auto body : currentTile->_tileActors)
		{
			if(body == nullptr) continue;
			UState_TActor* state = NewObject<UState_TA_Move>(UState_TA_Move::StaticClass());
			if(!barrier->_actors.Contains(body))
			{
				body->ChangeState(state);
				barrier->_actors.Add(body);
			}
		}
	}
}

void AGridManager::MarkStepsOnGrid(ATile* CenterTile)
{
	check(CenterTile != nullptr);
	for(int i = 0; i < _gridTiles.Num(); i++)
	{
		for(int j = 0; j < _gridTiles[i].Tiles.Num(); j++)
		{
			_gridTiles[i].Tiles[j]->_step = -1;
		}
	}
	CenterTile->_step = 0;
	//return;
	SetStepOnAdjacentsRecursive(CenterTile);
	
}

void AGridManager::SetStepOnAdjacentsRecursive(ATile* tile)
{
	//Haut-> Bas -> Droite -> Gauche
	SetStepOnAdjacentTile(tile, FVector2D(1, 0));
	SetStepOnAdjacentTile(tile, FVector2D(-1, 0));
	SetStepOnAdjacentTile(tile, FVector2D(0, 1));
	SetStepOnAdjacentTile(tile, FVector2D(0, -1));
}

void AGridManager::SetStepOnAdjacentTile(ATile* tile, FVector2D direction)
{
	if(TileIsAvailable(tile, direction))
	{
		ATile* nextTile = _gridTiles[tile->_row + direction.X].Tiles[tile->_column + direction.Y];
		nextTile->_step = tile->_step + 1;
		SetStepOnAdjacentsRecursive(nextTile);
	}
}

bool AGridManager::TileIsAvailable(ATile* tile, FVector2D direction)
{
	if(tile->_row + direction.X >= 0 && tile->_row + direction.X < _gridTiles.Num() &&
		tile->_column + direction.Y >= 0 && tile->_column + direction.Y < _gridTiles[0].Tiles.Num())
	{
		ATile* adjTile = _gridTiles[tile->_row + direction.X].Tiles[tile->_column + direction.Y];
		bool directionalCondition = direction.X == 1 ? tile->_upLink : false;
		directionalCondition = direction.X == -1 ? tile ->_downLink : directionalCondition;
		directionalCondition = direction.Y == 1 ? tile ->_rightLink : directionalCondition;
		directionalCondition = direction.Y == -1 ? tile ->_leftLink : directionalCondition;
		
		if(adjTile->_walkable && directionalCondition && (adjTile->_step == -1 || adjTile->_step > tile->_step + 1))
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

TArray<ATile*> AGridManager::GetPath(ATile* endTile, bool getCurrentTile)
{
	TArray<ATile*> path;
	ATile* currentTile = endTile;
	path.Add(currentTile);
	int32 lastStep = 0;
	if(!getCurrentTile) lastStep = 1;
	while(currentTile->_step > lastStep)
	{
		currentTile = GetNextTileInPath(currentTile);
		path.Add(currentTile);
	}
	return path;
}

ATile* AGridManager::GetNextTileInPath(ATile* tile)
{
	if(tile->_column + 1 >= 0 && tile->_column + 1 < _gridTiles[0].Tiles.Num() && _gridTiles[tile->_row].Tiles[tile->_column + 1]->_step == tile->_step - 1 && tile->_rightLink)
		return _gridTiles[tile->_row].Tiles[tile->_column + 1];
	else if(tile->_column - 1 >= 0 && tile->_column- 1 < _gridTiles[0].Tiles.Num() && _gridTiles[tile->_row].Tiles[tile->_column - 1]->_step == tile->_step - 1&& tile->_leftLink)
		return _gridTiles[tile->_row].Tiles[tile->_column - 1];
	else if(tile->_row + 1 >= 0 && tile->_row + 1 < _gridTiles.Num() && _gridTiles[tile->_row + 1].Tiles[tile->_column]->_step == tile->_step - 1 && tile->_upLink)
		return _gridTiles[tile->_row + 1].Tiles[tile->_column];
	else if(tile->_row - 1 >= 0 && tile->_row - 1 < _gridTiles.Num() && _gridTiles[tile->_row - 1].Tiles[tile->_column]->_step == tile->_step - 1 && tile->_downLink)
    	return _gridTiles[tile->_row - 1].Tiles[tile->_column];
	else return nullptr;
}

void AGridManager::BlueprintEditorTick(float DeltaTime)
{
}

void AGridManager::InitializeGrid()	
{
	for (auto& row : _gridTiles)
	{
		for (ATile* tile : row.Tiles)
		{
			if (tile)
			{
				tile->Destroy();
			}
		}
	}

	// Clear the grid array
	_gridTiles.Empty();

	UE_LOG(LogTemp, Warning, TEXT("Initialization"));
	for (size_t i = 0; i < _rows; i++)
	{
		_gridTiles.Add(FTileArray());
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
			SpawnedTile->_gridManager = this;
			SpawnedTile->SetActorScale3D(FVector(_tileWidth, _tileWidth, 1));
			_gridTiles[i].Tiles.Add(SpawnedTile);
			//SpawnedTile->SetHighlighted(false);
		}
	}

	_rows = _gridTiles.Num();
	_columns = _gridTiles[0].Tiles.Num();
}

void AGridManager::UpdateLinks()
{
	//UE_LOG(LogTemp, Warning, TEXT("grid tiles size %d"), tile.Tiles.Num());
	for(int32 i = 0; i < _gridTiles.Num(); i++)
	{
		for (int32 j = 0; j < _gridTiles[i].Tiles.Num(); j++)
		{
			_gridTiles[i].Tiles[j]->_gridManager = this;
			_gridTiles[i].Tiles[j]->RefreshLinks();
		}
	}
}

ATile* AGridManager::WorldCoordinatesToTilePosition(const FVector& worldCoordinates)
{
	const int32 x = FMath::RoundToInt32( static_cast<float>(FMath::CeilToInt32(worldCoordinates.X)) / _tileWidth / 100.0f) ;
	const int32 y = FMath::RoundToInt32( static_cast<float>(FMath::CeilToInt32(worldCoordinates.Y)) / _tileWidth / 100.0f) ;

	if (x >= 0 && x < _rows && y >= 0 && y < _columns && _gridTiles[x].Tiles[y]->_walkable)
		return _gridTiles[x].Tiles[y];
	else
		return nullptr;
}

ATile* AGridManager::GetTile(int32 i, int32 j)
{
	if (i >= 0 && i < _gridTiles.Num() && j >= 0 && j < _gridTiles[i].Tiles.Num())
	{
		return _gridTiles[i].Tiles[j];
	}

	return nullptr;
}


