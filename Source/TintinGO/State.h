#pragma once

#include "GameManager.h"
#include "CoreMinimal.h"

class TINTINGO_API State
{
public:
	State();
	//State(AGameManager* gameManager);
	~State();

	virtual void OnStateEnter();
	virtual void OnStateTick();
	virtual void OnStateExit(int32* currentStateIndex);
	bool isEnabled = false;

//protected:
	//AGameManager* _gameManager ;
};
