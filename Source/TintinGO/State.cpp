#include "State.h"


void UState::OnStateEnter()
{
}

void UState::OnStateTick(float DeltaTime)
{

}

void UState::OnStateExit()
{
	this->ConditionalBeginDestroy();
}
