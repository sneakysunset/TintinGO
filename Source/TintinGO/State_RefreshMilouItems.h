// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "State_RefreshMilouItems.generated.h"

UCLASS()
class TINTINGO_API UState_RefreshMilouItems : public UState
{
	GENERATED_BODY()

protected:
	virtual void OnStateEnter() override;

	virtual void OnStateTick(float DeltaTime) override;

	UPROPERTY()
	UBarrier* _barrier;

	UPROPERTY()
	ATileActor_Character_Milou* _milou;
};
