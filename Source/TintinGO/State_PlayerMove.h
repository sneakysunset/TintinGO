#pragma once

#include "CoreMinimal.h"
#include "State_MilouMove.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_Character_Tintin.h"
#include "State_PlayerMove.generated.h"

UCLASS()
class TINTINGO_API UState_PlayerMove : public UState
{
	GENERATED_BODY()
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;
private:
	ATileActor_Character_Tintin* _tintin;
	ATileActor_Character_Milou* _milou;
	UBarrier* _barrier;
};
