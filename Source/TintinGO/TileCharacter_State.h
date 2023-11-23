#pragma once
#include "TileCharacter.h"

class TileCharacter_State
{
public:
	TileCharacter_State(ATileCharacter* tileCharacter);
	virtual void OnStateEnter();
	virtual void OnStateTick(float DeltaTime);
	virtual void OnStateExit();

protected:
	AGameManager* _gameManager ;
	ATileCharacter* _tileCharacter;
};
