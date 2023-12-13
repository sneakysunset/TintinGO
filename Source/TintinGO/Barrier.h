#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
class ATileActor;
#include "State_TActor.h"
#include "Barrier.generated.h"


UCLASS()
class TINTINGO_API UBarrier : public UObject
{
	GENERATED_BODY()
public:
	
	void OnBarrierIni(TSubclassOf<UState_TActor> newState);
	void OnTick(float DeltaTime);
	TArray<ATileActor*> _actors;
	bool _isBarriereCompleted;
};


