// Fill out your copyright notice in the Description page of Project Settings.


#include "State_AwaitingInputs.h"
State_AwaitingInputs::State_AwaitingInputs()
{
}

State_AwaitingInputs::~State_AwaitingInputs()
{
}

void State_AwaitingInputs::OnStateEnter()
{
	State::OnStateEnter();
}

void State_AwaitingInputs::OnStateTick()
{
	State::OnStateTick();
}

void State_AwaitingInputs::OnStateExit(int32* currentStateIndex)
{
	State::OnStateExit(currentStateIndex);
}