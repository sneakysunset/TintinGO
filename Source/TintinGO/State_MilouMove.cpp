#include "State_MilouMove.h"

#include "Barrier.h"
#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_TC_Move.h"

void UState_MilouMove::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Milou Move State Enter"));
	
	_milou = ATileActor_Character_Milou::GetInstance();

	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	
	ATile* previousMilouTile =_milou->GetCurrentTile();

	previousMilouTile->_placableBodies.Remove(_milou);
	_milou->SetCurrentTile(_milou->MilouTilePath.Last());
	_milou->MilouTilePath.Pop(true);
	previousMilouTile->SetHighlightedPath(false);
	
	_milou->ChangeTile(_barrier, previousMilouTile);
	_barrier->OnBarrierIni(UState_TC_Move::StaticClass());
}

void UState_MilouMove::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		if(_milou->MilouTilePath.Num() > 0)
		{
			_gameManager->StateChange(NewObject<UState_MilouMove>(StaticClass()));			
		}
		else
		{
			_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
		}
	}
	_barrier->OnTick(DeltaTime);
}

void UState_MilouMove::OnStateExit()
{
	UState::OnStateExit();
}
