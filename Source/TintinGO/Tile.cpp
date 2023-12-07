// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

#include "GridManager.h"
#include "TileActor_Character_Peruvien.h"
#include "TileActor_MilouBone.h"

ATile::ATile() 
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Plane.Plane"));
	
	_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);
	_staticMeshComponent->SupportsDefaultCollision();

	RootComponent = _staticMeshComponent;
	
	_rightLink = false;
	_leftLink = false;
	_upLink = false;
	_downLink = false;
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
	
	if (_walkable) {
			
		switch (_tileType) {
		case ETileType::Neutral:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_walkableMat));
			break;
		case ETileType::StartingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_startPosMat));
			break;
		case ETileType::EndingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_endPosMat));
			break;
		}
	}
	else {
		_staticMeshComponent->SetMaterial(0, _unwalkableMat);
	}
}

void ATile::SetHighlighted(bool toHightlight) const
{
	if(toHightlight)
	{
		_staticMeshComponent->SetMaterial(0, DynamicMat(_HighlightedMat));
	}
	else
	{
		switch (_tileType)
		{
		case ETileType::Neutral:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_walkableMat));
			break;
		case ETileType::StartingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_startPosMat));
			break;
		case ETileType::EndingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_endPosMat));
			break;
		}
	}
}

void ATile::SetHighlightedPath(bool toHightlight) const
{
	if(toHightlight)
	{
		_staticMeshComponent->SetMaterial(0, DynamicMat(_HighlightedPathMat));
	}
	else
	{
		switch (_tileType)
		{
		case ETileType::Neutral:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_walkableMat));
			break;
		case ETileType::StartingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_startPosMat));
			break;
		case ETileType::EndingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_endPosMat));
			break;
		default:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_walkableMat));
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

	return destination;
	
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
			tActor->SetCurrentTile(this);
			break;
		case ETileActorType::Clue:
			//tActor = GetWorld()->SpawnActor<ATileActor>(ATileActor::StaticClass(), position, rotation, params);
			//tActor->SetActorLabel(FString::Printf(TEXT("Item_Clue")));
			return;
		case ETileActorType::Peruvien:
			tActor = GetWorld()->SpawnActor<ATileActor_Character_Peruvien>(_peruvienBP->GeneratedClass, position, rotation, params);
			tActor->SetActorLabel(FString::Printf(TEXT("Enemy_Peruvien")));
			tActor->SetCurrentTile(this);
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
		
		_tileActors.Add(tActor);
	}
}

UMaterialInstanceDynamic* ATile::DynamicMat(UMaterialInterface* mat) const
{
	UMaterialInstanceDynamic* dynamicMaterial = UMaterialInstanceDynamic::Create(mat , nullptr);

	if(_leftLink == true)
		dynamicMaterial->SetScalarParameterValue(FName("Left"), 1);
	else
		dynamicMaterial->SetScalarParameterValue(FName("Left"), 0);

	if(_upLink == true)
		dynamicMaterial->SetScalarParameterValue(FName("Top"), 1);
	else
		dynamicMaterial->SetScalarParameterValue(FName("Top"), 0);

	if(_rightLink == true)
		dynamicMaterial->SetScalarParameterValue(FName("Right"), 1);
	else
		dynamicMaterial->SetScalarParameterValue(FName("Right"), 0);

	if(_downLink == true)
		dynamicMaterial->SetScalarParameterValue(FName("Bot"), 1);
	else
		dynamicMaterial->SetScalarParameterValue(FName("Bot"), 0);
	
	return dynamicMaterial;
}

void ATile::RefreshLinks()
{
	ATile* leftTile = _gridManager->GetTile(_row, _column - 1);
	ATile* rightTile = _gridManager->GetTile(_row, _column + 1);
	ATile* upTile = _gridManager->GetTile(_row + 1, _column);
	ATile* downTile = _gridManager->GetTile(_row - 1, _column);

	if(leftTile == nullptr || !leftTile->_walkable || !leftTile->_rightLink)
	{
		_leftLink = false;
	}

	if(rightTile == nullptr || !rightTile->_walkable || !rightTile->_leftLink)
	{
		_rightLink = false;
	}

	if(upTile == nullptr || !upTile->_walkable || !upTile->_downLink)
	{
		_upLink = false;
	}

	if(downTile == nullptr || !downTile->_walkable || !downTile->_upLink)
	{
		_downLink = false;
	}
}




