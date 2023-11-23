#pragma once

#include "CoreMinimal.h"
#include "GridManager.h"
#include "State.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_Character_Tintin.h"


class TINTINGO_API State_AwaitingInputs : public State
{
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;
	void ProcessMousePositionInput();
	void ProcessPlayerInputs(ATile* hitTile);
	void ProcessMiloInputs(ATile* hitTile);
	void ReceiveLeftMouseClick();
	void ReceiveMiloClickDelegate();
	void DisableTiles(bool disablePath, bool disablePlayerTarget);
private:
	AGridManager* gridManager;
	ATile* _hitTile;
	ATileActor_Character_Milou* _milou;
	ATileActor_Character_Tintin* _tintin;
	bool isTileAccessible;
	bool isTintinInput;
};
