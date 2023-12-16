#include "State_PlayerMove.h"

#include "GameManager.h"
#include "GlobalGameManager.h"
#include "State_AwaitingInputs.h"
#include "State_TA_Move.h"
#include "State_TriggerItemsCharacters.h"
#include "GlobalGameManager.h"
#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"

void UState_PlayerMove::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Player Move State Enter"));
	
	_tintin = ATileActor_Character_Tintin::GetInstance();
	_milou = ATileActor_Character_Milou::GetInstance();
	
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	
	ATile* previousTintinTile =_tintin->GetCurrentTile();
	ATile* previousMilouTile =_milou->GetCurrentTile();
	
	//previousTintinTile->_tileActors.Remove(_tintin);
	_tintin->SetCurrentTile(_tintin->GetNextTile());
	
	if(_milou->isBoundToTintin)
	{
		_milou->SetCurrentTile(_milou->GetNextTile());
		_gameManager->ChangeTile(_barrier, previousMilouTile, _milou->GetCurrentTile());
	}
	_gameManager->ChangeTile(_barrier, previousTintinTile, _tintin->GetCurrentTile());
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
	if(_milou->isBoundToTintin)
	{
		Cast<UState_TA_Move>(_milou->_currentState_TA)->_actorSpeed = _milou->_speed;
		Cast<UState_TA_Move>(_milou->_currentState_TA)->_speed = _milou->_speed;
	}
	Cast<UState_TA_Move>(_tintin->_currentState_TA)->_actorSpeed = _tintin->_speed;
	Cast<UState_TA_Move>(_tintin->_currentState_TA)->_speed = _tintin->_speed;
}

void UState_PlayerMove::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		if(_tintin->GetCurrentTile()->_tileType == ETileType::EndingPosition && _gameManager->_clueNumber == 0)
		{
			_gameManager->OnWin();
		}

		if(_tintin->GetCurrentTile() == _milou->GetCurrentTile())
		{
			_milou->isBoundToTintin;
			
		}
		
		_gameManager->StateChange(NewObject<UState_TriggerItemsCharacters>(UState_TriggerItemsCharacters::StaticClass()));
	}
	_barrier->OnTick(DeltaTime);
}

void UState_PlayerMove::OnStateExit()
{
	UState::OnStateExit();
}



