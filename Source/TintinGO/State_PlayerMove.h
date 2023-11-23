#pragma once

#include "State.h"
#include "CoreMinimal.h"
#include "State_TileCharacterMove.h"
#include "TileCharacter_Milou.h"
#include "TileCharacter_Tintin.h"


class TINTINGO_API State_PlayerMove : public State_TileCharacterMove
{
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

private:
	ATileCharacter_Tintin* _tintin = nullptr;
	ATileCharacter_Milou* _milou = nullptr;
};
