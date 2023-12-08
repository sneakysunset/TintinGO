// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_MilouBone.h"

#include "GameManager.h"


ATileActor_MilouBone::ATileActor_MilouBone()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor_MilouBone::BeginPlay()
{
	ATileActor::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BEGIN PLAY BONE"));
}

void ATileActor_MilouBone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Tick"));
}

void ATileActor_MilouBone::OnEndTask()
{
	UE_LOG(LogTemp, Warning, TEXT("Milou Bone Triggered : %p"), _currentTile);
	AGameManager* gameManager = AGameManager::GetInstance();
	gameManager->_milouBonesNumber++;
	gameManager->OnBoneConsumed.Execute(gameManager->_milouBonesNumber, FColor::Emerald);
	//UE_LOG(LogTemp, Warning, TEXT("Milou bone task end"));
	//return;
	Super::OnEndTask();
}
