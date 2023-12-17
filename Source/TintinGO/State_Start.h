// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUI.h"
#include "State.h"
#include "Curves/CurveFloat.h"
#include "State_Start.generated.h"


UCLASS()
class TINTINGO_API UState_Start : public UState
{
	GENERATED_BODY()
public:
	virtual void OnStateEnter() override;

	virtual void OnStateTick(float DeltaTime) override;

	UPROPERTY()
	float _speed;

	UPROPERTY()
	UCurveFloat* _curve;

	UPROPERTY()
	UCoreUI* _widget;

private:
	UPROPERTY()
	float _interpolateValue;

	UPROPERTY()
	float _startAlpha;

	UPROPERTY()
	float _endAlpha;
};
