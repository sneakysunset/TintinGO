#pragma once

#include "State.h"
#include "CoreMinimal.h"
#include "TileActor_Character_Tintin.h"

class State_TriggerItemsCharacters : public State
{
public:
	State_TriggerItemsCharacters();
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

private:
	ATileActor_Character_Tintin* _tintin;
	TArray<ATileActor*> _tileActors;
};
