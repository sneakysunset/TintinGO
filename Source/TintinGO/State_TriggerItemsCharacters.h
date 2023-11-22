#pragma once

#include "State.h"
#include "CoreMinimal.h"
#include "Item.h"
#include "TileCharacter_Tintin.h"

class State_TriggerItemsCharacters : public State
{
public:
	State_TriggerItemsCharacters();
	virtual void OnStateEnter();
	virtual void OnStateTick(float DeltaTime);
	virtual void OnStateExit();

private:
	ATileCharacter_Tintin* _tintin;
	TArray<AItem*> items;
	TArray<ATileCharacter*> characters;
};
