#pragma once

#include "CoreMinimal.h"
#include "GridManager.h"
#include "State.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_Character_Tintin.h"
#include "State_AwaitingInputs.generated.h"

UCLASS()
class TINTINGO_API UState_AwaitingInputs : public UState
{
GENERATED_BODY()
	
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;
	void ProcessMousePositionInput();
	
	virtual void ProcessPlayerInputs();
	UFUNCTION()
	virtual void ReceiveLeftMouseClick();
	UFUNCTION()
	virtual void ReceiveMiloClickDelegate();
	virtual void DisableTiles(bool disablePath, bool disablePlayerTarget);
protected:
	AGridManager* gridManager;
	ATile* _hitTile;
	ATileActor_Character_Milou* _milou;
	ATileActor_Character_Tintin* _tintin;
	APlayerController* pc;
	bool isTileAccessible;
};
