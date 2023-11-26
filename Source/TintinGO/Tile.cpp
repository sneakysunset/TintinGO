// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

#include "GridManager.h"
#include "TileActor_Character_Peruvien.h"
#include "TileActor_MilouBone.h"

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
	_step = -1;
}

void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if WITH_EDITOR
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}

#endif
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

void ATile::SetHighlighted(bool toHightlight) const
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

void ATile::SetHighlightedPath(bool toHightlight) const
{
	if(toHightlight)
	{
		_staticMeshComponent->SetMaterial(0, _HighlightedPathMat);
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

FVector ATile::GetTileActorPosition(ATileActor* tileActor)
{

	if(IsValid(tileActor) && !_tileActors.Contains(tileActor))
	{
		_tileActors.Add(tileActor);
	}
	
	FVector destination = GetActorLocation() + tileActor->GetActorScale().Z * 50 * FVector::UpVector;
	
	if(_tileActors.Num() == 1)
		return destination;
	
	for(int i = 0; i < _tileActors.Num(); i++)
	{
		FVector direction =  GetActorForwardVector() - destination;
		const float radAngle = FMath::DegreesToRadians(i / _tileActors.Num() * 360) ;
		FQuat rotation = FQuat(FVector::UpVector, radAngle);
		destination = rotation * direction * _positionCircleRadius;
	}
	
	return destination;
}

void ATile::AddTileActors()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (auto* Attached : AttachedActors)
	{
		Attached->Destroy();
	}

	_tileActors.Empty();

	for (int i = 0; i < _TileItems.Num(); i++)
	{
		FActorSpawnParameters params;
		FVector position = GetActorLocation();
		FRotator rotation = FRotator(0, 0, 0);
		ATileActor* tActor = nullptr;
		switch (_TileItems[i])
		{
		case ETileActorType::Bone:
			tActor = GetWorld()->SpawnActor<ATileActor_MilouBone>(_milouBoneBP->GeneratedClass, position, rotation, params);
			tActor->SetActorLabel(FString::Printf(TEXT("Item_Bone")));
			break;
		case ETileActorType::Clue:
			//tActor = GetWorld()->SpawnActor<ATileActor>(ATileActor::StaticClass(), position, rotation, params);
			//tActor->SetActorLabel(FString::Printf(TEXT("Item_Clue")));
			return;
		case ETileActorType::Peruvien:
			tActor = GetWorld()->SpawnActor<ATileActor_Character_Peruvien>(_peruvienBP->GeneratedClass, position, rotation, params);
			tActor->SetActorLabel(FString::Printf(TEXT("Enemy_Peruvien")));
			break;
		case ETileActorType::Condor:
			//tActor = GetWorld()->SpawnActor<ATileActor>(ATileActor::StaticClass(), position, rotation, params);
			//tActor->SetActorLabel(FString::Printf(TEXT("Enemy_Condor")));
			return;
		default:
			break;
		}
		tActor->SetActorLocation(GetTileActorPosition(tActor));
		tActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}





