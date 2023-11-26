#pragma once
#include "State.h"
#include "TileActor_Character_Milou.h"
#include "State_MilouMove.generated.h"

class ATileCharacter_Tintin;

UCLASS()
class UState_MilouMove : public UState
{
GENERATED_BODY()
	
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

private:
	ATileActor_Character_Milou* _milou;
	UBarrier* _barrier;
};
