#pragma once

#include "CoreMinimal.h"
#include "GridManager.h"
#include "State.h"


class TINTINGO_API State_AwaitingInputs : public UState
{
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick() override;
	virtual void OnStateExit(int32* currentStateIndex) override;
	void ReceiveLeftMouseClick(FVector mousePosition);

private:
	AGridManager* gridManager;
};
