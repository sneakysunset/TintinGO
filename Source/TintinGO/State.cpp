#include "State.h"
#include "GameManager.h"

UState::UState()
{
	_gameManager = AGameManager::GetInstance();
}

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
