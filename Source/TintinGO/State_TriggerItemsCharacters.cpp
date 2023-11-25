#include "State_TriggerItemsCharacters.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"


UState_TriggerItemsCharacters::UState_TriggerItemsCharacters()
{
}

void UState_TriggerItemsCharacters::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Trigger Items / Characters State Enter"));
	_tintin = ATileActor_Character_Tintin::GetInstance();
	for(int i = 0; i < _tintin->GetCurrentTile()->_placableBodies.Num(); i++)
	{
		_tintin->GetCurrentTile()->_placableBodies[i]->TriggerBody();
		_tileActors.Add(_tintin->GetCurrentTile()->_placableBodies[i]);
	}
}

void UState_TriggerItemsCharacters::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	for(int i = 0; i < _tileActors.Num(); i++)
	{
		if(_tileActors[i]->_isTaskOver)
		{
			_tileActors[i]->OnEndTask();
			_tileActors.RemoveAt(i);
			i--;
		}
	}

	if(_tileActors.Num() == 0)
	{
		_gameManager->StateChange(NewObject<UState>(UState_AwaitingInputs::StaticClass()));
	}
}

void UState_TriggerItemsCharacters::OnStateExit()
{
	UState::OnStateExit();
}
