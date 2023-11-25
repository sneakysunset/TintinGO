// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "State_TActor.generated.h"
class ATile;
class ATileActor;

UCLASS()
class TINTINGO_API UState_TActor : public UState
{
	GENERATED_BODY()
public:
	ATileActor* _tileActor;
	bool _isStateComplete;
};
