// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_MilouBone.h"

#include "GameManager.h"


ATileActor_MilouBone::ATileActor_MilouBone()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor_MilouBone::OnEndTask()
{
	AGameManager* gameManager = AGameManager::GetInstance();
	gameManager->_milouBonesNumber++;
	if(gameManager->OnBoneConsumed.IsBound())
		gameManager->OnBoneConsumed.Execute(gameManager->_milouBonesNumber, FColor::Emerald);
	Super::OnEndTask();
}
