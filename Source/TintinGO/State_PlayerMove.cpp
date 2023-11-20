#include "State_PlayerMove.h"

#include "GameManager.h"
#include "TileCharacter_Tintin.h"


State_PlayerMove::State_PlayerMove()
{
	State::State();
	_tintin = ATileCharacter_Tintin::GetInstance();
	_interpolateValue = 0;
}

void State_PlayerMove::OnStateEnter()
{
	State::OnStateEnter();
	_interpolateValue = 0;
}

void State_PlayerMove::OnStateTick(float DeltaTime)
{
	State::OnStateTick(DeltaTime);
	_interpolateValue += DeltaTime * _tintin->speed;
	FVector const startPos = _tintin->_currentTile->GetActorLocation();
	FVector const endPos = _gameManager->_playerTargetTile->GetActorLocation();
	FVector const lerpVector = startPos + (endPos - startPos) * _interpolateValue;
	_tintin->SetActorLocation(lerpVector);
}

void State_PlayerMove::OnStateExit()
{
	State::OnStateExit();
}

