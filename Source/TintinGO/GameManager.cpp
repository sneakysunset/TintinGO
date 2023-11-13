// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "State.h"
#include "State_AwaitingInputs.h"
#include "State_PlayerMove.h"


AGameManager* AGameManager::SingletonInstance = nullptr;

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	SingletonInstance = this;

	_states.Add(new State_AwaitingInputs());
	_states.Add(new State_PlayerMove());
	_currentStateIndex = 0;
	_states[_currentStateIndex]->OnStateEnter();
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_states[_currentStateIndex]->OnStateTick();
}

void AGameManager::StateChange()
{
	_states[_currentStateIndex]->OnStateExit(&_currentStateIndex);
	_states[_currentStateIndex]->OnStateEnter();
}

AGameManager* AGameManager::GetInstance() 
{
	return SingletonInstance;
}
