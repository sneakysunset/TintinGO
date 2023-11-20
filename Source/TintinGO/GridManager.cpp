#include "GridManager.h"
#include "Tile.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "TileCharacter_Tintin.h"

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
				ATileCharacter_Tintin* character = GetWorld()->SpawnActor<ATileCharacter_Tintin>(ATileCharacter_Tintin::StaticClass(), position, rotation, params);
				if(character != nullptr)
				{
					character->SetActorLabel(FString::Printf(TEXT("Tintin")));
				}
				character->AttachToActor(tile, FAttachmentTransformRules::KeepWorldTransform);
				character->SetActorScale3D(tile->GetActorScale3D() / 5);
				character->_currentTile = tile;
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
	const int32 x = FMath::CeilToInt32(worldCoordinates.X / _tileWidth / 100.0f);
	const int32 y = FMath::CeilToInt32(worldCoordinates.Y / _tileWidth / 100.0f);
	
	return _gridTiles[x].Tiles[y];
}


