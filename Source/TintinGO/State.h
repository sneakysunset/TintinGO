#pragma once

#include "CoreMinimal.h"

class AGameManager;

class TINTINGO_API State
{
public:
	State();
virtual	~State();

	virtual void OnStateEnter();
	virtual void OnStateTick(float DeltaTime);
	virtual void OnStateExit();

protected:
	//EStateType _targetStateType;
	AGameManager* _gameManager ;
};
