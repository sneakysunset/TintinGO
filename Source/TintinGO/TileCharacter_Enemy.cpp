// Fill out your copyright notice in the Description page of Project Settings.


#include "TileCharacter_Enemy.h"

ATileCharacter_Enemy::ATileCharacter_Enemy()
{
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Cone.Cone"));
    _staticMeshComponent->SetStaticMesh(meshFinder.Object);

    RootComponent = _staticMeshComponent;
}