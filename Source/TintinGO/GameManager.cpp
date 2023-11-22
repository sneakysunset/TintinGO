#include "GameManager.h"
#include "State.h"
#include "State_AwaitingInputs.h"
#include "State_PlayerMove.h"
#include "State_TriggerItemsCharacters.h"


AGameManager* AGameManager::SingletonInstance = nullptr;

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	SingletonInstance = this;
	
	_currentStateType = new State_AwaitingInputs();
	_currentStateType->OnStateEnter();
}

void AGameManager::ReceiveMilouUIClick()
{
	if(OnMilouBoneClick.IsBound())
	{
		OnMilouBoneClick.Execute();
	}
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_currentStateType->OnStateTick(DeltaTime);
}

void AGameManager::StateChange(State* newState)
{
	_currentStateType->OnStateExit();
	_currentStateType = newState;
	_currentStateType->OnStateEnter();
}

AGameManager* AGameManager::GetInstance() 
{
	return SingletonInstance;
}


