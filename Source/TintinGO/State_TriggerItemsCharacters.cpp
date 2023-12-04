#include "State_TriggerItemsCharacters.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"


void UState_TriggerItemsCharacters::OnStateEnter()
{
	UState::OnStateEnter();
	_tintin = ATileActor_Character_Tintin::GetInstance();
	UE_LOG(LogTemp, Warning, TEXT("Trigger Items / Characters State Enter %d, %d"), _tintin->GetCurrentTile()->_row, _tintin->GetCurrentTile()->_column);
	for(int i = 0; i < _tintin->GetCurrentTile()->_tileActors.Num(); i++)
	{
		_tileActors.Add(_tintin->GetCurrentTile()->_tileActors[i]);
		_tintin->GetCurrentTile()->_tileActors[i]->TriggerBody();
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
		_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
	}
}

void UState_TriggerItemsCharacters::OnStateExit()
{
	UState::OnStateExit();
}
