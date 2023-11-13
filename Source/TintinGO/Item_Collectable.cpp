// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Collectable.h"

// Sets default values
AItem_Collectable::AItem_Collectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem_Collectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem_Collectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem_Collectable::OnTriggered()
{
	Super::OnTriggered();
}
