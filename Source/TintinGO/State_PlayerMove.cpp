#include "State_PlayerMove.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_TA_Move.h"
#include "State_TriggerItemsCharacters.h"


void UState_PlayerMove::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Player Move State Enter"));
	
	_tintin = ATileActor_Character_Tintin::GetInstance();
	_milou = ATileActor_Character_Milou::GetInstance();
	
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	
	ATile* previousTintinTile =_tintin->GetCurrentTile();
	ATile* previousMilouTile =_milou->GetCurrentTile();
	
	previousTintinTile->_tileActors.Remove(_tintin);
	_tintin->SetCurrentTile(_tintin->GetNextTile());
	
	if(_milou->isBoundToTintin)
	{
		if(previousMilouTile->_tileActors.Contains(_milou))
			previousMilouTile->_tileActors.Remove(_milou);
		_milou->SetCurrentTile(_milou->GetNextTile());
		_milou->ChangeTile(_barrier, previousMilouTile);
	}
	_tintin->ChangeTile(_barrier, previousTintinTile);
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
}

void UState_PlayerMove::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
	}
	_barrier->OnTick(DeltaTime);
}

void UState_PlayerMove::OnStateExit()
{
	UState::OnStateExit();
}



