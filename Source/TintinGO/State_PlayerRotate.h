// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "TileActor_Character_Tintin.h"
#include "State_PlayerRotate.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API UState_PlayerRotate : public UState
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
	FRotator _milouStartRotation;

	UPROPERTY()
	FRotator _milouEndRotation;
	
	UPROPERTY()
	ATileActor_Character_Tintin* _tintin;

	UPROPERTY()
	ATileActor_Character_Milou* _milou;

	UPROPERTY()
	float _interpolateValue;
};
