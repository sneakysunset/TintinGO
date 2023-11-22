// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Item.h"
#include "Item_MilouBone.h"
#include "Item_HaddockBottle.h"
#include "TileCharacter.h"
#include "TileCharacter_Enemy.h"

ATile::ATile() 
{
	PrimaryActorTick.bCanEverTick = true;
	_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Plane.Plane"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);
	_staticMeshComponent->SupportsDefaultCollision();
	RootComponent = _staticMeshComponent;
	_rightLink = true;
	_leftLink = true;
	_upLink = true;
	_downLink = true;
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


void ATile::SetHighlighted(bool toHightlight)
{
	if(toHightlight)
	{
		_staticMeshComponent->SetMaterial(0, _HighlightedMat);
	}
	else
	{
		switch (_tileType)
		{
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
}

	void ATile::AddPlacableBodies()
	{
		TArray<AActor*> AttachedActors;
		GetAttachedActors(AttachedActors);
		for (auto* Attached : AttachedActors)
		{
			Attached->Destroy();
		}

		ItemsList.Empty();
		TileCharacterList.Empty();

		for (int i = 0; i < _placableBodies.Num(); i++)
		{
			FActorSpawnParameters params;
			FVector position = GetActorLocation();
			FRotator rotation = FRotator(0, 0, 0);
			AItem* item = nullptr;
			ATileCharacter* character = nullptr;

			switch (_placableBodies[i])
			{
			case EPlacableBodyType::Enemy:
				character = GetWorld()->SpawnActor<ATileCharacter_Enemy>(ATileCharacter_Enemy::StaticClass(), position, rotation, params);
				character->SetActorLabel(FString::Printf(TEXT("Enemy")));
				break;
			case EPlacableBodyType::MilouBone:
				item = GetWorld()->SpawnActor<AItem_MilouBone>(AItem_MilouBone::StaticClass(), position, rotation, params);
				item->SetActorLabel(FString::Printf(TEXT("MilouBone")));
				break;
			case EPlacableBodyType::HaddockBottle:
				item = GetWorld()->SpawnActor<AItem_HaddockBottle>(AItem_HaddockBottle::StaticClass(), position, rotation, params);
				item->SetActorLabel(FString::Printf(TEXT("HaddockBottle")));
				break;
			default:
				break;
			}
			if (item)
			{
				item->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				item->SetActorScale3D(GetActorScale3D() / 5);
				ItemsList.Add(item);
			}
			if (character)
			{
				character->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				character->SetActorScale3D(GetActorScale3D() / 5);
				TileCharacterList.Add(character);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Character Spawned Not Valid"));
			}
		}
	}




