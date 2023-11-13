// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class TINTINGO_API State
{
public:
	State();
	~State();

	virtual void OnStateEnter();
	virtual void OnStateTick();
	virtual void OnStateExit(int32* currentStateIndex);
	bool isEnabled = false;
};
