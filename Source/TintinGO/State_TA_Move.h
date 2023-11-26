#pragma once
#include "Barrier.h"
#include "State_TActor.h"
#include "State_TA_Move.generated.h"

UCLASS()
class UState_TA_Move : public UState_TActor
{
	GENERATED_BODY()
public:
	ATileActor* tActor;
	
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateComplete() override;

private:
	
	FVector _startPosition;
	FVector _endPosition;
};
