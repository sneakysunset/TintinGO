#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "State.generated.h"


class AGameManager;

UCLASS()
class TINTINGO_API UState : public UObject
{
	GENERATED_BODY()

public:
	UState();
	~UState();

	virtual void OnStateEnter();
	virtual void OnStateTick();
	virtual void OnStateExit(int32* currentStateIndex);
	bool isEnabled = false;

protected:
	AGameManager* _gameManager ;
};
