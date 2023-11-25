#pragma once

#include "State.h"
#include "CoreMinimal.h"
#include "TileActor_Character_Tintin.h"
#include "State_TriggerItemsCharacters.generated.h"

UCLASS()
class UState_TriggerItemsCharacters : public UState
{
	GENERATED_BODY()
public:
	UState_TriggerItemsCharacters();
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

private:
	ATileActor_Character_Tintin* _tintin;
	TArray<ATileActor*> _tileActors;
};
