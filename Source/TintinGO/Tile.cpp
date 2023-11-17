// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Item.h"
#include "TileCharacter.h"

ATile::ATile() 
{
	PrimaryActorTick.bCanEverTick = true;
	_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Plane.Plane"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;
}

void ATile::Tick(float DeltaTime)
{
#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}

#endif
	Super::Tick(DeltaTime);

}

bool ATile::ShouldTickIfViewportsOnly() const
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

void ATile::BlueprintEditorTick(float DeltaTime)
{
	if (_walkable != _walkableChecker || _tileType != _tileTypeChecker) {
		if (_walkable) {
			switch (_tileType) {
			case ETileType::Neutral:
				_staticMeshComponent->SetMaterial(0, _walkableMat);
				break;
			case ETileType::StartingPosition:
				_staticMeshComponent->SetMaterial(0, _startPosMat);
				break;
			case ETileType::EndingPosition:
				_staticMeshComponent->SetMaterial(0, _endPosMat);
				break;

			}
		}
		else {
			_staticMeshComponent->SetMaterial(0, _unwalkableMat);
		}
		_walkableChecker = _walkable;
	}
}

void ATile::AddItem() 
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (auto* Attached : AttachedActors)
	{
		Attached->Destroy();
	}

	_items.Empty();


	for (int i = 0; i < _itemsToSpawn.Num(); i++)
	{
		FActorSpawnParameters SpawnParams;
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = FRotator(0, 0, 0);
		AItem* SpawnedItem = nullptr;
		switch (_itemsToSpawn[i]) 
		{
			case EItemType::BriefCase :
				SpawnedItem = GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				break;
			case EItemType::Milou:
				SpawnedItem = GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				break;
			case EItemType::Hadoc:
				SpawnedItem = GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
				break;
		}
		SpawnedItem->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		SpawnedItem->SetActorScale3D(GetActorScale3D() / 10);
		SpawnedItem->SetActorLabel(FString::Printf(TEXT("Item_%d_Of_Tile_%d_%d"), i, _row, _column));

		_items.Add(SpawnedItem);
	}
}




