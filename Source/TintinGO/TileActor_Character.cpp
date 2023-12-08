// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Character.h"

void ATileActor_Character::BeginPlay()
{
	Super::BeginPlay();
	angle = EAngle::Right;
}
