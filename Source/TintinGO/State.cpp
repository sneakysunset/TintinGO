#include "State.h"
#include "GameManager.h"

State::State()
{
	_gameManager = AGameManager::GetInstance();
}



State::~State()
{
}

void State::OnStateEnter()
{

}

void State::OnStateTick(float DeltaTime)
{

}

void State::OnStateExit()
{
	//_gameManager->_currentStateType = _targetStateType;
}


void State::ReceiveLeftMouseClick(FVector mousePosition)
{

}