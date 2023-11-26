#include "State_TActor.h"
#include "TileActor.h"


void UState_TActor::OnStateEnter()
{
	Super::OnStateEnter();
	_isStateComplete = false;
	_interpolateValue = 0;
	_speed = _tileActor->_speed;
}

void UState_TActor::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);
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

