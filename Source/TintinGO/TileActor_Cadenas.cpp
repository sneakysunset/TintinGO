// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Cadenas.h"

ATileActor_Cadenas* ATileActor_Cadenas::SingletonInstance = nullptr;

void ATileActor_Cadenas::BeginPlay()
{
	Super::BeginPlay();
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	_staticMeshComponent = Components[0];
}

ATileActor_Cadenas* ATileActor_Cadenas::GetInstance() 
{
	return SingletonInstance;
}

ATileActor_Cadenas::ATileActor_Cadenas()
{
	SingletonInstance = this;
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor_Cadenas::UnlockCadenas() const
{
	_staticMeshComponent->SetVisibility(false);
}
