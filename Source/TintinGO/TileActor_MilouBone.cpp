// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_MilouBone.h"

#include "GameManager.h"
#include "MainGameMode.h"


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
}
