#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "State.generated.h"

class AMainGameMode;

UCLASS()
class TINTINGO_API UState : public UObject
{
GENERATED_BODY()
	
public:
	virtual void OnStateEnter();
	virtual void OnStateTick(float DeltaTime);
	virtual void OnStateExit();
	UPROPERTY()
	AMainGameMode* _gameManager ;

protected:
};


