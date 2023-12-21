#include "State_TriggerItemsCharacters.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_CheckWinConditions.h"
#include "State_PeruviensMove.h"
#include "State_RefreshTileItems.h"


void UState_TriggerItemsCharacters::OnStateEnter()
{
	UState::OnStateEnter();
	_tintin = ATileActor_Character_Tintin::GetInstance();
	if(_gameManager->DebugStateChange)
		UE_LOG(LogTemp, Warning, TEXT("Trigger Items / Characters State Enter"));
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
	//_gameManager->StateChange(NewObject<UState_CheckWinConditions>(UState_CheckWinConditions::StaticClass()));
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
		_gameManager->StateChange(NewObject<UState_RefreshTileItems>(UState_RefreshTileItems::StaticClass()));
	}
}

void UState_TriggerItemsCharacters::OnStateExit()
{
	UState::OnStateExit();
}
