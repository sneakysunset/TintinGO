// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Character_Milou.h"

ATileActor_Character_Milou* ATileActor_Character_Milou::SingletonInstance = nullptr;

ATileActor_Character_Milou* ATileActor_Character_Milou::GetInstance() 
{
	return SingletonInstance;
}

ATileActor_Character_Milou::ATileActor_Character_Milou()
{
	PrimaryActorTick.bCanEverTick = true;
	SingletonInstance = this;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;

	_currentTile = nullptr;
}
