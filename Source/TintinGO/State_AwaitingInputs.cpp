#include "State_AwaitingInputs.h"



void State_AwaitingInputs::OnStateEnter()
{
	UState::OnStateEnter();
}

void State_AwaitingInputs::OnStateTick()
{
	UState::OnStateTick();
}

void State_AwaitingInputs::OnStateExit(int32* currentStateIndex)
{
	UState::OnStateExit(currentStateIndex);
}

void State_AwaitingInputs::ReceiveLeftMouseClick(FVector mousePosition)
{

}