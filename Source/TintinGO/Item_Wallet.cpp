// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Wallet.h"

AItem_Wallet::AItem_Wallet()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;
}