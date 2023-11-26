#include "TileActor.h"

#include "State_TA_Neutral.h"




void ATileActor::OnEndTask()
{
	//this->Destroy();
}

void ATileActor::TriggerBody()
{
	_isTaskOver = true;
}

void ATileActor::ChangeState(UState_TActor* newState)
{
	newState->_tileActor = this;
	_currentState_TA->OnStateExit();
	_currentState_TA = newState;
	_currentState_TA->OnStateEnter();
}

void ATileActor::BeginPlay()
{
	Super::BeginPlay();
	_currentState_TA = NewObject<UState_TA_Neutral>(UState_TA_Neutral::StaticClass());
}

void ATileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_currentState_TA->OnStateTick(DeltaTime);
}

