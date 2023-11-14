#include "State.h"
#include "GameManager.h"

UState::UState()
{
	_gameManager = AGameManager::GetInstance();
}



UState::~UState()
{
}

void UState::OnStateEnter()
{

}

void UState::OnStateTick()
{

}

void UState::OnStateExit(int32* currentStateIndex)
{
	*currentStateIndex ++;
}
