// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_MilouBone.h"

#include "GameManager.h"


void ATileActor_MilouBone::OnEndTask()
{
	AGameManager* gameManager = AGameManager::GetInstance();
	gameManager->_milouBonesNumber++;
	gameManager->OnBoneConsumed.Execute(gameManager->_milouBonesNumber, FColor::Emerald);
	Super::OnEndTask();
}
