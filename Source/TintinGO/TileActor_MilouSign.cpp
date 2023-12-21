// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_MilouSign.h"

#include "MainGameMode.h"
#include "TileActor_Cadenas.h"

ATileActor_MilouSign::ATileActor_MilouSign()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor_MilouSign::BeginPlay()
{
	Super::BeginPlay();
	_startHeight = GetActorLocation().Z;
	_endHeight = _startHeight + _heightToGoUp;
}

void ATileActor_MilouSign::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MilouSignAnimation(DeltaSeconds);
}

void ATileActor_MilouSign::MilouSignAnimation(float DeltaSeconds)
{
	_interpolateValue += _animationSpeed * DeltaSeconds;
	if(_interpolateValue >= 1) _interpolateValue = 0;
	const FVector position = FVector(GetActorLocation().X, GetActorLocation().Y, FMath::Lerp(_startHeight, _endHeight, _animCurve->FloatCurve.Eval(_interpolateValue)));
	SetActorLocation(position);
}