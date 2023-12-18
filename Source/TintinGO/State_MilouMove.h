#pragma once
#include "State.h"
#include "TileActor_Character_Milou.h"
#include "Barrier.h"
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
	ATileActor_Character_Tintin* _tintin;
	UBarrier* _barrier;

	void PeruvienDetectionAllDirection() const;
	void PeruvienDetection(int32 x, int32 y, bool isLinkActive) const;
};
