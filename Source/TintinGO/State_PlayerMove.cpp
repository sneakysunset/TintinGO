#include "State_PlayerMove.h"

#include "GameManager.h"
#include "State_TriggerItemsCharacters.h"
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
	UE_LOG(LogTemp, Warning, TEXT("Player Move State Enter"));
	_tintin = ATileCharacter_Tintin::GetInstance();
	_interpolateValue = 0;
}

void State_PlayerMove::OnStateTick(float DeltaTime)
{
	State::OnStateTick(DeltaTime);
	_interpolateValue += DeltaTime * _gameManager->speed;
	FVector startPos = _tintin->_currentTile->GetActorLocation();
	FVector const endPos = _gameManager->_playerTargetTile->GetActorLocation();
	FVector const lerpVector = startPos + (endPos - startPos) * _interpolateValue;
	_tintin->SetActorLocation(lerpVector);
	if(_interpolateValue >= 1)
	{
		_gameManager->StateChange(new State_TriggerItemsCharacters());
	}
}

void State_PlayerMove::OnStateExit()
{
	State::OnStateExit();
	_tintin->_currentTile = _gameManager->_playerTargetTile;
}

