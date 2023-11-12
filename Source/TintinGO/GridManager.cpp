// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "GridManager.h"

AGridManager::AGridManager()
{
	PrimaryActorTick.bCanEverTick = true;
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
		for (ATile* tile : row)
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
		_gridTiles.Add(TArray<ATile*>());
		for (size_t j = 0; j < _columns; j++)
		{
			ATile* tile = NewObject<ATile>(this);
			FActorSpawnParameters SpawnParams;
			FVector SpawnLocation = FVector(i * 100 * _tileWidth, j * 100 * _tileWidth , 0);
			FRotator SpawnRotation = FRotator(0, 0, 0);
			ATile* SpawnedTile = GetWorld()->SpawnActor<ATile>(tile->GetClass(), SpawnLocation, SpawnRotation, SpawnParams);
			SpawnedTile->SetActorScale3D(FVector(_tileWidth, _tileWidth, 1));
			SpawnedTile->SetActorLabel(FString::Printf(TEXT("Tile_%d_%d"), i, j));
			tile->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
			SpawnedTile->_row = i;
			SpawnedTile->_column = j;
			SpawnedTile->_walkableMat = _walkable_TileMaterial;
			SpawnedTile->_startPosMat = _startPos_TileMaterial;
			SpawnedTile->_endPosMat = _endPos_TileMaterial;
			SpawnedTile->_unwalkableMat = _unwalkable_TileMaterial;
			UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(_walkable_TileMaterial, SpawnedTile);
			if (DynamicMaterial)
			{
				// Set the material on the mesh component (assuming it's a UStaticMeshComponent)
				UStaticMeshComponent* MeshComponent = SpawnedTile->FindComponentByClass<UStaticMeshComponent>();
				if (MeshComponent)
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
				_gridTiles[i].Add(SpawnedTile);
				//UE_LOG(LogTemp, Warning, TEXT("Tile %s spawned at (%f, %f, %f)"), *SpawnedTile->GetName(), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to spawn tile at (%f, %f, %f)"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);
			}
		}
	}
}

void AGridManager::OccupyCell(int32 Row, int32 Col)
{

}

void AGridManager::ReleaseCell(int32 Row, int32 Col)
{

}



