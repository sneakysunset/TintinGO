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

AGameManager::~AGameManager()
{
	OnClickD.Clear();
	OnMilouBoneClick.Clear();
	OnBoneConsumed.Clear();
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	SingletonInstance = this;
	_currentStateType = NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass());
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
	if(IsValid(this) && IsValid(_currentStateType) && _currentStateType != nullptr)
	{
		//UE_LOG(LogTemp, Error, TEXT("%s"), *_currentStateType->GetName())
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


