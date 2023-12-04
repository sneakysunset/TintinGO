#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "Tile.h"
#include "TileActor_Character_Tintin.h"
#include "State_CheckWinConditions.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API UState_CheckWinConditions : public UState
{
	GENERATED_BODY()
	
public:
	virtual void OnStateEnter() override;
	
protected:
	AGridManager* gridManager;
	ATile* _hitTile;
	ATileActor_Character_Tintin* _tintin;
};
