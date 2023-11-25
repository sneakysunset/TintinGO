#pragma once

#include "CoreMinimal.h"
#include "UObject/Class.h"
#include "State.generated.h"

class AGameManager;

UCLASS()
class TINTINGO_API UState : public UObject
{
GENERATED_BODY()
	
public:
	UState();

	virtual void OnStateEnter();
	virtual void OnStateTick(float DeltaTime);
	virtual void OnStateExit();

protected:
	AGameManager* _gameManager ;
};


