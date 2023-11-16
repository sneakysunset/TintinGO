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

	_itemsList.Empty();

	for (int i = 0; i < _itemsType.Num(); i++)
	{
		FActorSpawnParameters params;
		FVector position = GetActorLocation();
		FRotator rotation = FRotator(0, 0, 0);
		AItem* spawnedItem = nullptr;

		_itemsList.Add(spawnedItem);
		FString name = "";

		switch (_itemsType[i])
		{
			case EItemType::Stone:
				spawnedItem = GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), position, rotation, params);
				spawnedItem->SetActorLabel(FString::Printf(TEXT("Stone_%d"), i));
				name = "Stone";
				break;
			case EItemType::Wallet:
				spawnedItem = GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), position, rotation, params);
				spawnedItem->SetActorLabel(FString::Printf(TEXT("Wallet_%d"), i));
				name = "Wallet";
				break;
			default:
				break;
		}
		if (spawnedItem)
		{
			spawnedItem->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
			spawnedItem->SetActorScale3D(GetActorScale3D() / 10);
			_itemsList.Add(spawnedItem);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Character Spawned Not Valid"));
		}
	}
}
void ATile::AddCharacter() 
{
	for (size_t i = 0; i < _ennemies.Num(); i++)
	{
		FActorSpawnParameters SpawnParams;
		FVector position = FVector(_row, _column, 50);
		FRotator rotation = FRotator(0, 0, 0);
		ATileCharacter* chara = nullptr;
		switch (_ennemies[i])
		{
			case ECharacterType::Neutral:
				chara = GetWorld()->SpawnActor<ATileCharacter>(ATileCharacter::StaticClass(), position, rotation, SpawnParams);
				break;
			case ECharacterType::Ennemy1:
				break;
			case ECharacterType::Ennemy2:
				break;
			default:
				break;
		}
		if (chara)
		{
			chara->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
			_ennemiesList.Add(chara);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Character Spawned Not Valid"));
		}
	}

}




