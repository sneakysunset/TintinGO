// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Barrier.h"
#include "State.h"
#include "GridManager.h"
#include "State_CondorAttack.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API UState_CondorAttack : public UState
{
	GENERATED_BODY()

public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;
private:
	UPROPERTY()
	UBarrier* _barrier;

	UPROPERTY()
	float rotateInterpolationValue;
};
