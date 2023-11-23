#include "GridManager.h"
#include "Tile.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_Character_Tintin.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

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
	_initializeGrid = false;
	_useEditorTick = true;
	_walkable_TileMaterial = nullptr;
	_startPos_TileMaterial = nullptr;
	_endPos_TileMaterial = nullptr;
	_unwalkable_TileMaterial = nullptr;
	_highlighted_TileMaterial = nullptr;
	_highlightedPath_TileMaterial = nullptr;
}

void AGridManager::Tick(float DeltaTime)
{
#if WITH_EDITOR
	//UE_LOG(LogTemp, Warning, TEXT("Test"));
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}

#endif
	Super::Tick(DeltaTime);

}

void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	SingletonInstance = this;
	for (int i = 0; i < _gridTiles.Num(); i++)
	{
		for (int j = 0; j < _gridTiles[i].Tiles.Num(); j++)
		{
			if(_gridTiles[i].Tiles[j]->_tileType == ETileType::StartingPosition)
			{
				ATile* tile = _gridTiles[i].Tiles[j];
				FActorSpawnParameters params;
				params.bNoFail = true;
				params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				FVector position = tile->GetActorLocation();
				FRotator rotation = FRotator(0, 0, 0);
				ATileActor_Character_Tintin* character = GetWorld()->SpawnActor<ATileActor_Character_Tintin>(ATileActor_Character_Tintin::StaticClass(), position, rotation, params);
				ATileActor_Character_Milou* milou = GetWorld()->SpawnActor<ATileActor_Character_Milou>(ATileActor_Character_Milou::StaticClass(), position, rotation, params);

				character->SetActorLabel(FString::Printf(TEXT("Tintin")));
				milou->SetActorLabel(FString::Printf(TEXT("Milou")));
				character->AttachToActor(tile, FAttachmentTransformRules::KeepWorldTransform);
				milou->AttachToActor(tile, FAttachmentTransformRules::KeepWorldTransform);
				character->SetActorScale3D(tile->GetActorScale3D() / 2);
				milou->SetActorScale3D(tile->GetActorScale3D() / 2);
				character->_currentTile = tile;
				milou->_currentTile = tile;
				break;
			}
		}
	}
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




void AGridManager::MarkStepsOnGrid(ATile* CenterTile)
{
	check(CenterTile != nullptr);
	UE_LOG(LogTemp, Warning, TEXT("grid %d"),_gridTiles.Num());
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
	//Droite -> Gauche -> Haut -> Bas
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
		bool directionalCondition = direction.X == 1 ? adjTile->_rightLink : false;
		directionalCondition = direction.X == -1 ? adjTile ->_leftLink : directionalCondition;
		directionalCondition = direction.Y == 1 ? adjTile ->_upLink : directionalCondition;
		directionalCondition = direction.Y == -1 ? adjTile ->_downLink : directionalCondition;
		
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

TArray<ATile*> AGridManager::GetPath(ATile* endTile)
{
	TArray<ATile*> path;
	ATile* currentTile = endTile;
	path.Add(currentTile);
	while(currentTile->_step > 0)
	{
		currentTile = GetNextTileInPath(currentTile);
		path.Add(currentTile);
	}
	return path;
}

ATile* AGridManager::GetNextTileInPath(ATile* tile)
{
	if(tile->_row + 1 >= 0 && tile->_row + 1 < _gridTiles.Num() && _gridTiles[tile->_row + 1].Tiles[tile->_column]->_step == tile->_step - 1)
		return _gridTiles[tile->_row + 1].Tiles[tile->_column];
	if(tile->_row - 1 >= 0 && tile->_row - 1 < _gridTiles.Num() && _gridTiles[tile->_row - 1].Tiles[tile->_column]->_step == tile->_step - 1)
    	return _gridTiles[tile->_row - 1].Tiles[tile->_column];
	if(tile->_column + 1 >= 0 && tile->_column + 1 < _gridTiles[0].Tiles.Num() && _gridTiles[tile->_row].Tiles[tile->_column + 1]->_step == tile->_step - 1)
		return _gridTiles[tile->_row].Tiles[tile->_column + 1];
	if(tile->_column - 1 >= 0 && tile->_column- 1 < _gridTiles[0].Tiles.Num() && _gridTiles[tile->_row].Tiles[tile->_column - 1]->_step == tile->_step - 1)
		return _gridTiles[tile->_row].Tiles[tile->_column - 1];
	else return nullptr;
}


void AGridManager::BlueprintEditorTick(float DeltaTime)
{
	if (_initializeGrid) 
	{
		InitializeGrid();
		_initializeGrid = false;
	}
	
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
			ATile* SpawnedTile = GetWorld()->SpawnActor<ATile>(ATile::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
			SpawnedTile->SetActorScale3D(FVector(_tileWidth, _tileWidth, 1));
			SpawnedTile->SetActorLabel(FString::Printf(TEXT("Tile_%d_%d"), static_cast<int>(i), static_cast<int>(j)));
			SpawnedTile->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
			SpawnedTile->SetActorLocation(SpawnLocation);
			SpawnedTile->_row = i;
			SpawnedTile->_column = j;
			SpawnedTile->_walkableMat = _walkable_TileMaterial;
			SpawnedTile->_startPosMat = _startPos_TileMaterial;
			SpawnedTile->_endPosMat = _endPos_TileMaterial;
			SpawnedTile->_unwalkableMat = _unwalkable_TileMaterial;
			SpawnedTile->_HighlightedMat = _highlighted_TileMaterial;
			SpawnedTile->_HighlightedPathMat = _highlightedPath_TileMaterial;
			if (UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(_walkable_TileMaterial, SpawnedTile))
			{
				// Set the material on the mesh component (assuming it's a UStaticMeshComponent)
				if (UStaticMeshComponent* MeshComponent = SpawnedTile->FindComponentByClass<UStaticMeshComponent>())
				{
					MeshComponent->SetMaterial(0, DynamicMaterial);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("No Static Mesh"));
				}
			}
			else 
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed At Dynamic Material creation"));
			}


			if (SpawnedTile)
			{
				_gridTiles[i].Tiles.Add(SpawnedTile);
				//UE_LOG(LogTemp, Warning, TEXT("Tile %s spawned at (%f, %f, %f)"), *SpawnedTile->GetName(), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to spawn tile at (%f, %f, %f)"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
			}
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


