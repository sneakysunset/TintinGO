#pragma once
#include "TileActor.h"
#include "State_TActor.h"
#include "State_TA_Rotate.generated.h"

class ATileActor_Character_Peruvien;

UCLASS()
class UState_TA_Rotate : public UState_TActor
{
	GENERATED_BODY()
public:
public:
	ATileActor* tActor;
	
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateComplete() override;

private:
	
	FRotator _startRotation;
	FRotator _endRotation;

	UPROPERTY()
	ATileActor_Character_Peruvien* _Peruvien;
};
