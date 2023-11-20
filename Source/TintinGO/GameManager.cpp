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
	SingletonInstance = this;
	
	_states.Add(EStateType::AwaitingInputs ,new State_AwaitingInputs());
	_states.Add(EStateType::PlayerMove,new State_PlayerMove());
	_currentStateType = EStateType::AwaitingInputs;
	_states[_currentStateType]->OnStateEnter();
}

void AGameManager::Tick(float DeltaTime)
{
	_states[_currentStateType]->OnStateTick(DeltaTime);
}

void AGameManager::StateChange(EStateType newState)
{
	_states[_currentStateType]->OnStateExit();
	_currentStateType = newState;
	_states[newState]->OnStateEnter();
}

AGameManager* AGameManager::GetInstance() 
{
	return SingletonInstance;
}


