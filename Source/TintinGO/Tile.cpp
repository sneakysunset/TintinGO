// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

#include "GridManager.h"
#include "MainGameMode.h"
#include "TileActor_Character_Condor.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_Character_Peruvien.h"
#include "TileActor_Character_Tintin.h"
#include "TileActor_Character.h"
#include "TileActor_Clue.h"
#include "TileActor_MilouBone.h"

ATile::ATile() 
{
	PrimaryActorTick.bCanEverTick = true;
	
	_rightLink = false;
	_leftLink = false;
	_upLink = false;
	_downLink = false;
	_step = -1;
	/*static ConstructorHelpers::FObjectFinder<ATileActor_Character_Tintin> meshFinder(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/TileActor_Character_Tintin_BP.TileActor_Character_Tintin_BP'"));
	_tintinBP =  meshFinder.Object;
	static ConstructorHelpers::FObjectFinder<ATileActor_Character_Milou> meshFinder2(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/TileActor_Character_Milou_BP.TileActor_Character_Milou_BP'"));
	_milouBP =  meshFinder2.Object;*/


}

void ATile::BeginPlay()
{
	Super::BeginPlay();

	_gameManager = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	_currentBackgroundAlpha = 0;
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	if(Components.Num() > 0)
	{
		_staticMeshComponent = Components[0];
	}
	else
	{
		return;
	}

	for(int i = 0; i < Components.Num(); i++)
	{
		if(Components[i]->GetName() == "AdditionalCircle")
		{
			_additionalCircle = Components[i];
			_additionalCircle->SetVisibility(false);
			_startAdditionalCircleScale = _additionalCircle->GetComponentScale();
			_endAdditionalCircleScale = _startAdditionalCircleScale - _scaleChangeMagnitude * FVector::One();
		}
		else if(Components[i]->GetName() == "EnnemyCircle")
		{
			_ennemyCircleComponent = Components[i];
		}
		else if(Components[i]->GetName() == "directionalPlaneRight")
		{
			_ennemyCircleRight= Components[i];
		}
		else if(Components[i]->GetName() == "directionalPlaneLeft")
		{
			_ennemyCircleLeft = Components[i];
		}
		else if(Components[i]->GetName() == "directionalPlaneUp")
		{
			_ennemyCircleUp = Components[i];
		}
		else if(Components[i]->GetName() == "directionalPlaneDown")
		{
			_ennemyCircleDown = Components[i];
		}
	}
	
	AddTileActors();

	if(!_walkable)
	{
		SetActorHiddenInGame(true);
	}
	
	if(_tileType == ETileType::StartingPosition)
		AddTintin();

	if (_tileType == ETileType::EndingPosition)
		_gameManager->_endTile = this;
		
	if (_tileType == ETileType::NestPosition)
		_gameManager->_nests.Add(this);

	for (auto actor : _tileActors)
	{
		actor->SetActorLocation(GetTileActorPosition(actor));
	}
	
	SetHighlighted(false);
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

	if(IsValid(_additionalCircle) && _additionalCircle->IsVisible())
	{
		RefreshAdditionalTileScale(DeltaTime);
	}
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
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	if(Components.Num() > 0)
	{
		_staticMeshComponent = Components[0];
	}
	else
	{
		return;
	}
	if (_walkable) {
			
		switch (_tileType) {
		case ETileType::Neutral:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_walkableMat, _currentBackgroundAlpha));
			break;
		case ETileType::StartingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_startPosMat, _currentBackgroundAlpha));
			break;
		case ETileType::EndingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_endPosMat, _currentBackgroundAlpha));
			break;
		case ETileType::NestPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_nestMat, _currentBackgroundAlpha));
			break;
		}
	}
	else {
		_staticMeshComponent->SetMaterial(0, _unwalkableMat);
	}
}

void ATile::AddTintin()
{
	FActorSpawnParameters params;
	params.ObjectFlags |= RF_Transient;
	params.bNoFail = true;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FVector position = GetActorLocation();
	
	const FRotator rotation = FRotator(0, 0, 0);
	//if(!IsValid(_tintinBP) || !IsValid(_milouBP)) return;
	ATileActor_Character_Tintin* character = GetWorld()->SpawnActor<ATileActor_Character_Tintin>(_tintinBP, position, rotation, params);
	ATileActor_Character_Milou* milou = GetWorld()->SpawnActor<ATileActor_Character_Milou>(_milouBP, position, rotation, params);
	character->SetUpRotation(_tintinAngle);
	milou->SetUpRotation(_tintinAngle);
#if WITH_EDITOR
	character->SetActorLabel(FString::Printf(TEXT("Tintin")));
	milou->SetActorLabel(FString::Printf(TEXT("Milou")));
#endif
	character->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	milou->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	milou->SetCurrentTile(this);
	character->SetCurrentTile(this);
	character->SetActorLocation(GetTileActorPosition(character));
	milou->SetActorLocation(GetTileActorPosition(milou));
}

void ATile::AddCondor()
{

}

void ATile::SetHighlighted(bool toHightlight)
{
	if(!_walkable) return;
	if(toHightlight)
	{
		_staticMeshComponent->SetMaterial(0, DynamicMat(_HighlightedMat, _currentBackgroundAlpha));
	}
	else
	{
		switch (_tileType)
		{
		case ETileType::Neutral:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_walkableMat, _currentBackgroundAlpha));
			break;
		case ETileType::StartingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_startPosMat, _currentBackgroundAlpha));
			break;
		case ETileType::EndingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_endPosMat, _currentBackgroundAlpha));
			break;
		case ETileType::NestPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_nestMat, _currentBackgroundAlpha));
			break;
		default:
			break;
		}
	}
}

void ATile::SetTilesInBoneRangeMat(bool toBone)
{
	if(toBone)
	{
		_staticMeshComponent->SetMaterial(0, DynamicMat(_InBoneRangeMat, _currentBackgroundAlpha));
		_additionalCircle->SetVisibility(true);

	}
	else
	{
		_additionalCircle->SetVisibility(false);

		switch (_tileType)
		{
		case ETileType::Neutral:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_walkableMat, _currentBackgroundAlpha));
			break;
		case ETileType::StartingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_startPosMat, _currentBackgroundAlpha));
			break;
		case ETileType::EndingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_endPosMat, _currentBackgroundAlpha));
			break;
		case ETileType::NestPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_nestMat, _currentBackgroundAlpha));
			break;
		default:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_walkableMat, _currentBackgroundAlpha));
			break;
		}
	}
}

void ATile::SetHighlightedPath(bool toHightlight) 
{
	if(toHightlight)
	{
		_staticMeshComponent->SetMaterial(0, DynamicMat(_HighlightedPathMat, _currentBackgroundAlpha));
	}
	else
	{
		_staticMeshComponent->SetMaterial(0, DynamicMat(_InBoneRangeMat, _currentBackgroundAlpha));
	}
}

FVector ATile::GetTileActorPosition(ATileActor* tileActor)
{
	if(IsValid(tileActor) && !_tileActors.Contains(tileActor))
	{
		_tileActors.Add(tileActor);
	}
	
	FVector destination = GetActorLocation() /*+ tileActor->GetActorScale().Z * 50 * FVector::UpVector*/;

	if(_tileActors.Num() == 1)
		return destination;
	
	for(int i = 0; i < _tileActors.Num(); i++)
	{
		if(_tileActors[i] == tileActor)
		{
			float Angle = FMath::DegreesToRadians(static_cast<float>(i) / static_cast<float>(_tileActors.Num()) * 360);
			// Calculate the position of the element around the circle
			destination = FVector(
				destination.X + 35 * FMath::Cos(Angle),
				destination.Y + 35 * FMath::Sin(Angle),
				destination.Z
			);
			break;
		}
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
	ATileActor_Clue* clueCasted = nullptr;
	ATileActor_Character_Peruvien* peruvienCasted = nullptr;
	FActorSpawnParameters params;
	params.bNoFail = true;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	params.ObjectFlags |= RF_Transient;
	FVector position = GetActorLocation();
	FRotator rotation = FRotator(0, 0, 0);
	
	for (int i = 0; i < _TileItems.Num(); i++)
	{
		ATileActor* tActor = nullptr;
		switch (_TileItems[i].actorType)
		{
		case ETileActorType::Bone:
			tActor = GetWorld()->SpawnActor<ATileActor_MilouBone>(_milouBoneBP, position, rotation, params);
#if WITH_EDITOR
			tActor->SetActorLabel(FString::Printf(TEXT("Item_Bone")));
#endif
			break;
		case ETileActorType::Clue:
			if(_TileItems[i].clueIndex != _gameManager->_clueNumber) continue;
			tActor = GetWorld()->SpawnActor<ATileActor_Clue>(_clueBP, position, rotation, params);
			clueCasted = Cast<ATileActor_Clue>(tActor);
			clueCasted->clueNumber = _TileItems[i].clueIndex;
			//clueCasted->SetActorHiddenInGame(true);
			break;
		case ETileActorType::Peruvien:
			tActor = GetWorld()->SpawnActor<ATileActor_Character_Peruvien>(_peruvienBP, position, rotation, params);
			peruvienCasted = Cast<ATileActor_Character_Peruvien>(tActor);
			_gameManager->_peruviens.Add(peruvienCasted);
			peruvienCasted->_startingTile = this;
			peruvienCasted->SetUpRotation(_TileItems[i].angle);
			peruvienCasted->_startingAngle = peruvienCasted->angle;

#if WITH_EDITOR
			tActor->SetActorLabel(FString::Printf(TEXT("Enemy_Peruvien")));
#endif
			break;
		case ETileActorType::Condor:
			ATileActor_Character_Condor* condor = GetWorld()->SpawnActor<ATileActor_Character_Condor>(_condorBP, position, rotation, params);
			_gameManager->_condors.Add(condor);
			tActor = condor;
			condor->SetUpRotation(_nestDirection);
#if WITH_EDITOR
			condor->SetActorLabel(FString::Printf(TEXT("Condor")));
#endif
		}

		_tileActors.Add(tActor);
		
		tActor->SetActorLocation(GetTileActorPosition(tActor));
		tActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		tActor->SetCurrentTile(this);
		//_tileActors.Add(tActor);
	}
}

void ATile::SpawnMilouBone()
{
	FActorSpawnParameters params;
	params.bNoFail = true;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FVector position = GetActorLocation() + FVector(0, 2, 0);
	const FRotator rotation = FRotator(0, 0, 0);
	ATileActor_Character_Milou::GetInstance()->_milouBoneToDrop = GetWorld()->SpawnActor<ATileActor_MilouBone>(_milouBoneBP, position, rotation, params);
	ATileActor_Character_Milou::GetInstance()->_milouBoneToDrop->SetCurrentTile(this);
}

UMaterialInstanceDynamic* ATile::DynamicMat(UMaterialInterface* mat, int backgroundAlpha) const
{
	UMaterialInstanceDynamic* dynamicMaterial = UMaterialInstanceDynamic::Create(mat , nullptr);
	dynamicMaterial->SetScalarParameterValue(FName("BackgroundAlpha"), backgroundAlpha);
	
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

	if(!IsValid(_gridManager))
	{
		UE_LOG(LogTemp, Error, TEXT("gridManager is null" ));
		return;
	}
	const ATile* leftTile = _gridManager->GetTile(_row, _column - 1);
	const ATile* rightTile = _gridManager->GetTile(_row, _column + 1);
	const ATile* upTile = _gridManager->GetTile(_row + 1, _column);
	const ATile* downTile = _gridManager->GetTile(_row - 1, _column);

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
	_gridManager = nullptr;
}

void ATile::RefreshTileBackgroundRenderer(int alpha)
{
	_currentBackgroundAlpha = _currentBackgroundAlpha = alpha;
	
	switch (_tileType)
	{
		case ETileType::Neutral:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_walkableMat, alpha));
			break;
		case ETileType::StartingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_startPosMat, alpha));
			break;
		case ETileType::EndingPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_endPosMat, alpha));
			break;
		case ETileType::NestPosition:
			_staticMeshComponent->SetMaterial(0, DynamicMat(_nestMat, alpha));
			break;
		default:
			break;
	}
}

void ATile::RefreshAdditionalTileScale(float DeltaSeconds)
{
	_interpolateValue += DeltaSeconds * _additionalCircleSpeed;
	if(_interpolateValue >= 1) _interpolateValue = 0;
	_additionalCircle->SetWorldScale3D(FMath::Lerp(_startAdditionalCircleScale, _endAdditionalCircleScale, _additionalCircleCurve->FloatCurve.Eval(_interpolateValue)));
}

void ATile::SetEnnemyDirection(bool toVisible, EAngle direction, bool onlyCircle) const
{
	if(toVisible)
	{
		_ennemyCircleComponent->SetVisibility(true);
		if(!onlyCircle)
		{
			switch(direction)
			{
				case EAngle::Up:
					_ennemyCircleUp->SetVisibility(true);
					break;
				case EAngle::Down:
					_ennemyCircleDown->SetVisibility(true);
					break;
				case EAngle::Right:
					_ennemyCircleRight->SetVisibility(true);
					break;
				case EAngle::Left:
					_ennemyCircleLeft->SetVisibility(true);
					break;
			}
		}
	}
	else
	{
		_ennemyCircleComponent->SetVisibility(false);
		_ennemyCircleUp->SetVisibility(false);
		_ennemyCircleDown->SetVisibility(false);
		_ennemyCircleRight->SetVisibility(false);
		_ennemyCircleLeft->SetVisibility(false);
	}

}

