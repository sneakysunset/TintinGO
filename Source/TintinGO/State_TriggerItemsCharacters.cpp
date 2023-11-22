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
	_tintin = ATileCharacter_Tintin::GetInstance();
	for(int i = 0; i < _tintin->_currentTile->ItemsList.Num(); i++)
	{
		_tintin->_currentTile->ItemsList[i]->TriggerBody();
		items.Add(_tintin->_currentTile->ItemsList[i]);
	}
	for(int i = 0; i < _tintin->_currentTile->TileCharacterList.Num(); i++)
	{
		_tintin->_currentTile->TileCharacterList[i]->TriggerBody();
		characters.Add(_tintin->_currentTile->TileCharacterList[i]);
	}
}

void State_TriggerItemsCharacters::OnStateTick(float DeltaTime)
{
	State::OnStateTick(DeltaTime);
	for(int i = 0; i < items.Num(); i++)
	{
		if(items[i]->isTaskOver)
		{
			items[i]->OnEndTask();
			items.RemoveAt(i);
			i--;
		}
	}
	for(int i = 0; i < characters.Num(); i++)
	{
		if(characters[i]->isTaskOver)
		{
			characters[i]->OnEndTask();
			characters.RemoveAt(i);
			i--;
		}
	}

	if(characters.Num() + items.Num() == 0)
	{
		_gameManager->StateChange(new State_AwaitingInputs());
	}
}

void State_TriggerItemsCharacters::OnStateExit()
{
	State::OnStateExit();
}
