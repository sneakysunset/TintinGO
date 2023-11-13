// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"

State::State()
{
}

State::~State()
{
}

void State::OnStateEnter()
{

}

void State::OnStateTick()
{

}

void State::OnStateExit(int32* currentStateIndex)
{
	*currentStateIndex ++;
}
