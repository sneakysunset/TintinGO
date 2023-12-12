// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

#include "GameManager.h"
#include "GridManager.h"
#include "TileActor_Character_Condor.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_Character_Peruvien.h"
#include "TileActor_Character_Tintin.h"
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
}

void ATile::BeginPlay()
{
	Super::BeginPlay();

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
	
	AddTileActors();

	if(!_walkable)
	{
		SetActorHiddenInGame(true);
	}
	
	if(_tileType == ETileType::StartingPosition)
		AddTintin();

	if (_tileType == ETileType::EndingPosition)
		AGridManager::GetInstance()->_endTile = this;

	/*if (_tileType == ETileType::Nest1Position)
		AddCondor();
	else
	{
		ATileActor_Character_Condor::SingletonInstance = nullptr;
	}*/

	/*if (_tileType == ETileType::EndNest1Position)
		AGridManager::GetInstance()->_endNest1Tile = this;

	if (_tileType == ETileType::Nest2Position)
		AGridManager::GetInstance()->_nest2Tile = this;

	if (_tileType == ETileType::EndNest2Position)
		AGridManager::GetInstance()->_endNest2Tile = this;*/
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

void ATile::AddTintin()
{
	FActorSpawnParameters params;
	params.bNoFail = true;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	const FVector position = GetActorLocation();
	const FRotator rotation = FRotator(0, 0, 0);
	ATileActor_Character_Tintin* character = GetWorld()->SpawnActor<ATileActor_Character_Tintin>(_tintinBP->GeneratedClass, position, rotation, params);
	ATileActor_Character_Milou* milou = GetWorld()->SpawnActor<ATileActor_Character_Milou>(_milouBP->GeneratedClass, position, rotation, params);

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
	FActorSpawnParameters params;
	params.bNoFail = true;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector position =  GetActorLocation();
	FRotator rotation = FRotator(0, 0, 0);
	ATileActor_Character_Condor* condor = GetWorld()->SpawnActor<ATileActor_Character_Condor>(_condorBP->GeneratedClass, position, rotation, params);

	condor->SetActorLabel(FString::Printf(TEXT("Condor")));
	condor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	condor->SetCurrentTile(this);
	condor->SetActorLocation(condor->GetCurrentTile()->GetTileActorPosition(condor));
	//ATileActor_Character_Condor::SingletonInstance = condor;
	//AGridManager::GetInstance()->_nest1Tile = this;
	UE_LOG(LogTemp, Warning, TEXT("ATileActor_Character_Condor != null"));
}

void ATile::SetHighlighted(bool toHightlight)
{
	if(!_walkable) return;
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
		default: ;
		}
	}
}

void ATile::SetTilesInBoneRangeMat(bool toBone)
{
	if(toBone)
	{
		_staticMeshComponent->SetMaterial(0, DynamicMat(_InBoneRangeMat));
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
		default: ;
		}
	}
}

void ATile::SetHighlightedPath(bool toHightlight) 
{
	if(toHightlight)
	{
		_staticMeshComponent->SetMaterial(0, DynamicMat(_HighlightedPathMat));
	}
	else
	{
		_staticMeshComponent->SetMaterial(0, DynamicMat(_InBoneRangeMat));
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
				destination.X + 20 * FMath::Cos(Angle),
				destination.Y + 20 * FMath::Sin(Angle),
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
	_gridManager = AGridManager::GetInstance();
	GetAttachedActors(AttachedActors);
	for (auto* Attached : AttachedActors)
	{
		Attached->Destroy();
	}

	_tileActors.Empty();
	ATileActor_Clue* clueCasted = nullptr;
	ATileActor_Character_Peruvien* peruvienCasted = nullptr;
	AGameManager* gameManager = AGameManager::GetInstance();
	for (int i = 0; i < _TileItems.Num(); i++)
	{
		FActorSpawnParameters params;
		FVector position = GetActorLocation();
		FRotator rotation = FRotator(0, 0, 0);
		ATileActor* tActor = nullptr;
		switch (_TileItems[i].actorType)
		{
		case ETileActorType::Bone:
			tActor = GetWorld()->SpawnActor<ATileActor_MilouBone>(_milouBoneBP->GeneratedClass, position, rotation, params);
#if WITH_EDITOR
			tActor->SetActorLabel(FString::Printf(TEXT("Item_Bone")));
#endif
			break;
		case ETileActorType::Clue:
			tActor = GetWorld()->SpawnActor<ATileActor_Clue>(_clueBP->GeneratedClass, position, rotation, params);
			clueCasted = Cast<ATileActor_Clue>(tActor);
			gameManager->_clueNumber++;
			clueCasted->clueNumber = _TileItems[i].clueIndex;
			break;
		case ETileActorType::Peruvien:
			tActor = GetWorld()->SpawnActor<ATileActor_Character_Peruvien>(_peruvienBP->GeneratedClass, position, rotation, params);
			peruvienCasted = Cast<ATileActor_Character_Peruvien>(tActor);
			_gridManager->_peruviens.Add(peruvienCasted);
			peruvienCasted->_startingTile = this;
			peruvienCasted->SetUpRotation(_TileItems[i].angle);
			peruvienCasted->_startingAngle = peruvienCasted->angle;

#if WITH_EDITOR
			tActor->SetActorLabel(FString::Printf(TEXT("Enemy_Peruvien")));
#endif
			break;
		case ETileActorType::Condor:
			tActor = GetWorld()->SpawnActor<ATileActor_Character_Condor>(_condorBP->GeneratedClass, position, rotation, params);
			_gridManager->_condors.Add(Cast<ATileActor_Character_Condor>(tActor));
			//tActor->SetActorLabel(FString::Printf(TEXT("Enemy_Condor")));
			return;
		default:
			break;
		}

		_tileActors.Add(tActor);
		
		tActor->SetActorLocation(GetTileActorPosition(tActor));
		tActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		tActor->SetCurrentTile(this);
		//_tileActors.Add(tActor);
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





