#pragma once
#include "State.h"
#include "TileCharacter_Milou.h"

class ATileCharacter_Tintin;

class State_MilouMove : public State
{
public:
	State_MilouMove();


	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

private:
	ATileCharacter_Milou* _milou;
	float _interpolateValue;
};
