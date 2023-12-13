#include "State_TActor.h"

#include "GameManager.h"
#include "TileActor.h"

void UState_TActor::OnStateEnter()
{
	UState::OnStateEnter();
	_isStateComplete = false;
	_interpolateValue = 0;
	_speed = AGameManager::GetInstance()->_inTileMoveSpeed;
}

void UState_TActor::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	_interpolateValue += DeltaTime * _speed;

	if(_interpolateValue >= 1 && !_isStateComplete)
	{
		OnStateComplete();
	}
}

void UState_TActor::OnStateComplete()
{
	_isStateComplete = true;
}

