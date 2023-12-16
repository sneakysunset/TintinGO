// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Character_Milou.h"

#include "GameManager.h"
#include "MainGameMode.h"

ATileActor_Character_Milou* ATileActor_Character_Milou::SingletonInstance = nullptr;

ATileActor_Character_Milou* ATileActor_Character_Milou::GetInstance() 
{
	return SingletonInstance;
}

void ATileActor_Character_Milou::BeginPlay()
{
	Super::BeginPlay();
	SetUpRotation(_gameManager->_tintinAngle);
}

ATileActor_Character_Milou::ATileActor_Character_Milou()
{
	SingletonInstance = this;
	PrimaryActorTick.bCanEverTick = true;

	isBoundToTintin = true;
}
