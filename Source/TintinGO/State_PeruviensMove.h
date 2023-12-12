// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Barrier.h"
#include "State.h"
#include "State_PeruviensMove.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API UState_PeruviensMove : public UState
{
	GENERATED_BODY()
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

	UPROPERTY()
	UBarrier* _barrier;
};
