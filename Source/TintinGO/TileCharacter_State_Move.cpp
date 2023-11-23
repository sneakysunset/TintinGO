#include "TileCharacter_State_Move.h"

void TileCharacter_State_Move::OnStateEnter()
{
	TileCharacter_State::OnStateEnter();
	_currentPosition = _tileCharacter->GetActorLocation();
}

void TileCharacter_State_Move::OnStateTick(float DeltaTime)
{
	TileCharacter_State::OnStateTick(DeltaTime);
}

void TileCharacter_State_Move::OnStateExit()
{
	TileCharacter_State::OnStateExit();
}
