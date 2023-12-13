#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "State_TActor.generated.h"

class ATileActor;

UCLASS()
class TINTINGO_API UState_TActor : public UState
{
	GENERATED_BODY()
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void SetTileActor(ATileActor* tileActor) {
		_tileActor = tileActor;
	}
	virtual ATileActor* GetTileActor() {
		return _tileActor;
	}
	bool _isStateComplete;
	float _speed;

protected:
	UPROPERTY()
	ATileActor* _tileActor;
	float _interpolateValue;
	virtual void OnStateComplete();
	
};
