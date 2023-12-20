// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "State_MilouRotate.generated.h"

class ATileActor_Character_Milou;

UCLASS()
class TINTINGO_API UState_MilouRotate : public UState
{
	GENERATED_BODY()
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

private:
	UPROPERTY()
	FRotator _startRotation;

	UPROPERTY()
	FRotator _endRotation;

	UPROPERTY()
	ATileActor_Character_Milou* _milou;

	UPROPERTY()
	float _interpolateValue;
};
