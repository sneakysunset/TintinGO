#pragma once

#include "State_TActor_Move.h"
#include "CoreMinimal.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_Character_Tintin.h"


class TINTINGO_API State_PlayerMove : public State_TActor_Move
{
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

private:
	ATileActor_Character_Tintin* _tintin = nullptr;
	ATileActor_Character_Milou* _milou = nullptr;
	float _interpolateValue;
};
