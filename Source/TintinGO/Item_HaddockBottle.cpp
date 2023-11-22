// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_HaddockBottle.h"

#include "TileCharacter_Tintin.h"

AItem_HaddockBottle::AItem_HaddockBottle()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;
}

void AItem_HaddockBottle::TriggerBody()
{
	Super::TriggerBody();
	ATileCharacter_Tintin::GetInstance()->currentHaddockBottleNb++;
}
