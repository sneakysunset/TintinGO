#include "State_TriggerItemsCharacters.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"


State_TriggerItemsCharacters::State_TriggerItemsCharacters()
{
}

void State_TriggerItemsCharacters::OnStateEnter()
{
	State::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Trigger Items / Characters State Enter"));
	_tintin = ATileActor_Character_Tintin::GetInstance();
	for(int i = 0; i < _tintin->_currentTile->_placableBodies.Num(); i++)
	{
		_tintin->_currentTile->_placableBodies[i]->TriggerBody();
		_tileActors.Add(_tintin->_currentTile->_placableBodies[i]);
	}
}

void State_TriggerItemsCharacters::OnStateTick(float DeltaTime)
{
	State::OnStateTick(DeltaTime);
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
		_gameManager->StateChange(new State_AwaitingInputs());
	}
}

void State_TriggerItemsCharacters::OnStateExit()
{
	State::OnStateExit();
}
