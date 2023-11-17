#pragma once

#include "CoreMinimal.h"

class AGameManager;

class TINTINGO_API State
{
public:
	State();
virtual	~State();

	virtual void OnStateEnter();
	virtual void OnStateTick();
	virtual void OnStateExit();
	virtual void ReceiveLeftMouseClick(FVector mousePosition);

protected:
	//EStateType _targetStateType;
	AGameManager* _gameManager ;
};
