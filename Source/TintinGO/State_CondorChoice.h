// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridManager.h"
#include "State.h"
#include "State_CondorChoice.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API UState_CondorChoice : public UState
{
	GENERATED_BODY()

public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;
};
