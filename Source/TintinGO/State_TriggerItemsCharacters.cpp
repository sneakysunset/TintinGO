#include "State_TriggerItemsCharacters.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_CheckWinConditions.h"


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

	if (_tileActors.Num() > 0)
	{
		for(int i = _tileActors.Num() - 1; i >= 0; i--)
		{
			if(_tileActors[i]->_isTaskOver)
			{
				_tileActors[i]->OnEndTask();
				_tileActors.RemoveAt(i);
			}
		}
	}

	_gameManager->StateChange(NewObject<UState_CheckWinConditions>(UState_CheckWinConditions::StaticClass()));
}

void UState_TriggerItemsCharacters::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
}

void UState_TriggerItemsCharacters::OnStateExit()
{
	UState::OnStateExit();
}
