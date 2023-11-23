#pragma once
#include "TileCharacter_State.h"

class TileCharacter_State_Move : public TileCharacter_State
{
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

private:
	FVector _currentPosition;
	FVector _targetPosition;
};
