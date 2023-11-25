#pragma once
#include "Barrier.h"
#include "State_TActor.h"
#include "State_TC_Move.generated.h"

UCLASS()
class UState_TC_Move : public UState_TActor
{
	GENERATED_BODY()
public:
	ATileActor* tActor;
	
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;

private:
	FVector _startPosition;
	FVector _endPosition;
	float _interpolateValue;
};
