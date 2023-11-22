#pragma once

#include "CoreMinimal.h"
#include "ClickInputManager.h"
#include "GridManager.h"
#include "State.h"


class TINTINGO_API State_AwaitingInputs : public State
{
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;
	void ReceiveLeftMouseClick();

private:
	AGridManager* gridManager;
	ATile* _hitTile;
	bool isTileAccessible;
};
