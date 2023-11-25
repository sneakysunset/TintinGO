// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_TActor.h"
#include "UObject/Object.h"
#include "Barrier.generated.h"
class ATileActor;

UCLASS()
class TINTINGO_API UBarrier : public UObject
{
	GENERATED_BODY()
public:
	
	void OnBarrierIni(TSubclassOf<UState_TActor> newState);
	void OnTick(float DeltaTime);
	TArray<ATileActor*> _actors;
	bool _isBarriereCompleted;
};


