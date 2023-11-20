#pragma once

#include "State.h"
#include "CoreMinimal.h"


class TINTINGO_API State_PlayerMove : public State
{
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick() override;
	virtual void OnStateExit() override;
};
