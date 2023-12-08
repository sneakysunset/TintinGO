#include "State_PlayerMove.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_TA_Move.h"
#include "State_TriggerItemsCharacters.h"


void UState_PlayerMove::OnStateEnter()
{
	UState::OnStateEnter();
	AGridManager* gridManager = AGridManager::GetInstance();
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
		gridManager->ChangeTile(_barrier, previousMilouTile, _milou->GetCurrentTile());
	}
	gridManager->ChangeTile(_barrier, previousTintinTile, _tintin->GetCurrentTile());
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
}

void UState_PlayerMove::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		_gameManager->StateChange(NewObject<UState_TriggerItemsCharacters>(UState_TriggerItemsCharacters::StaticClass()));
	}
	_barrier->OnTick(DeltaTime);
}

void UState_PlayerMove::OnStateExit()
{
	UState::OnStateExit();
}



