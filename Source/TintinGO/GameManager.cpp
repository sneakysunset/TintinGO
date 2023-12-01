#include "GameManager.h"
#include "State.h"
#include "State_AwaitingInputs.h"


AGameManager* AGameManager::SingletonInstance = nullptr;

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
	_milouBoneThrowRange = 2;
	_milouBonesNumber = 0;
	_currentStateType = NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass());
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	SingletonInstance = this;
	//if(!IsValid(_currentStateType))
		_currentStateType = NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass());
	_currentStateType->OnStateEnter();
}

void AGameManager::Destroyed()
{
	Super::Destroyed();
	SingletonInstance = nullptr;
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
	if(IsValid(this) && IsValid(_currentStateType))
	{
		_currentStateType->OnStateTick(DeltaTime);
	}
}

void AGameManager::StateChange(UState* newState)
{
	_currentStateType->OnStateExit();
	_currentStateType = newState;
	_currentStateType->OnStateEnter();
}

AGameManager* AGameManager::GetInstance() 
{
	return SingletonInstance;
}


