// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_MilouBone.h"

#include "GameManager.h"
#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"


ATileActor_MilouBone::ATileActor_MilouBone()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor_MilouBone::OnEndTask()
{
	_gameManager->_milouBonesNumber++;
	if(_gameManager->OnBoneConsumed.IsBound())
		_gameManager->OnBoneConsumed.Execute(_gameManager->_milouBonesNumber, FColor::Emerald);
	Super::OnEndTask();
	UGameplayStatics::SpawnSoundAtLocation(this, S_BoneTrigger, GetActorLocation());
	Destroy();
}

void ATileActor_MilouBone::OnDestroyBone()
{
	Super::OnEndTask();
}

