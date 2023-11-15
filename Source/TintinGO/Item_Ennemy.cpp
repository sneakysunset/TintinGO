// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Ennemy.h"

// Sets default values
AItem_Ennemy::AItem_Ennemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem_Ennemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem_Ennemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem_Ennemy::KillMoveBehaviour()
{

}

void AItem_Ennemy::RotateBehaviour()
{

}

