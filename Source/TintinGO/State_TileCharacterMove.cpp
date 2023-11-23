#include "State_TileCharacterMove.h"

#include "PlacableBody.h"

void State_TileCharacterMove::OnStateEnter()
{
	State::OnStateEnter();
	_interpolateValue = 0;
}

void State_TileCharacterMove::OnStateTick(float DeltaTime)
{
	State::OnStateTick(DeltaTime);
	_interpolateValue += DeltaTime;
}

void State_TileCharacterMove::OnStateExit()
{
	State::OnStateExit();
}
