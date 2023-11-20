// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Stone.h"

AItem_Stone::AItem_Stone()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;
}