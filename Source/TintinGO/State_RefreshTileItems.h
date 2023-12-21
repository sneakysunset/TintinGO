// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "State_RefreshTileItems.generated.h"

class UBarrier;

class ATileActor_Character_Tintin;
/**
 * 
 */
UCLASS()
class TINTINGO_API UState_RefreshTileItems : public UState
{
	GENERATED_BODY()

	virtual void OnStateEnter() override;

	virtual void OnStateTick(float DeltaTime) override;

	UPROPERTY()
	UBarrier* _barrier;

	UPROPERTY()
	ATileActor_Character_Tintin* _tintin;
};
