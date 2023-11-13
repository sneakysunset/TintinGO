// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"


class TINTINGO_API State_AwaitingInputs : public State
{
public:
	State_AwaitingInputs();
	//State_AwaitingInputs(AGameManager* gameManager);
	~State_AwaitingInputs();
	virtual void OnStateEnter() override;
	virtual void OnStateTick() override;
	virtual void OnStateExit(int32* currentStateIndex) override;
};
