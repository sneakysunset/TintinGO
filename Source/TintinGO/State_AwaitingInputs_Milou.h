// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_AwaitingInputs.h"
#include "State_AwaitingInputs_Milou.generated.h"


UCLASS()
class TINTINGO_API UState_AwaitingInputs_Milou : public UState_AwaitingInputs
{
	GENERATED_BODY()
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void ProcessPlayerInputs() override;
	virtual void ReceiveLeftMouseClick() override;
	virtual void ReceiveMiloClickDelegate() override;
	virtual void OnStateExit() override;
	virtual void DisableTiles() override;
};
