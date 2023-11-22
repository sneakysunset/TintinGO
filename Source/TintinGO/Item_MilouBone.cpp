// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_MilouBone.h"

#include "TileCharacter_Tintin.h"

AItem_MilouBone::AItem_MilouBone()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;
}

void AItem_MilouBone::TriggerBody()
{
	Super::TriggerBody();
	ATileCharacter_Tintin::GetInstance()->currentMilouBonesNb++;
}
