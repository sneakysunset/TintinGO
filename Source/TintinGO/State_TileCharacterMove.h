#pragma once

#include"State.h"

class State_TileCharacterMove : public State
{
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

protected:
	float _interpolateValue;
	FVector _startPosition;
	FVector _endPosition;

};
