#pragma once
#include "State.h"
#include "TileActor_Character_Milou.h"

class ATileCharacter_Tintin;

class State_MilouMove : public State
{
public:
	State_MilouMove();


	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

private:
	ATileActor_Character_Milou* _milou;
	float _interpolateValue;
};
