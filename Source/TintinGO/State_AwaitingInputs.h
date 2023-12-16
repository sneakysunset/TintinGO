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
	UFUNCTION()
	virtual void OnStateEnter() override;

	UFUNCTION()
	virtual void OnStateTick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnStateExit() override;

	UFUNCTION()
	void ProcessMousePositionInput();

	UFUNCTION()
	virtual void ProcessPlayerInputs();
	
	UFUNCTION()
	virtual void ReceiveLeftMouseClick();
	
	UFUNCTION()
	virtual void ReceiveMiloClickDelegate();

	UFUNCTION()
	virtual void DisableTiles();
	
protected:
	UPROPERTY()
	ATile* _hitTile;

	UPROPERTY()
	ATileActor_Character_Milou* _milou;

	UPROPERTY()
	ATileActor_Character_Tintin* _tintin;

	UPROPERTY()
	APlayerController* pc;

	UPROPERTY()
	bool isTileAccessible;
};
