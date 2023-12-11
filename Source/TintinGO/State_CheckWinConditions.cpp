#include "State_CheckWinConditions.h"
#include "GameManager.h"
#include "GridManager.h"
#include "State_AwaitingInputs.h"
#include "State_CondorChoice.h"
#include "TileActor_Character_Condor.h"

void UState_CheckWinConditions::OnStateEnter()
{
	UState::OnStateEnter();
	
	gridManager = AGridManager::GetInstance();
	_tintin = ATileActor_Character_Tintin::GetInstance();
	
	if (_tintin->GetCurrentTile() == gridManager->GetEndTile())
	{
		UE_LOG(LogTemp, Warning, TEXT("Win"));
		//_gameManager->StateChange(NewObject<UState_AwaitingInputs_Milou>(UState_AwaitingInputs_Milou::StaticClass()));
	}
	else
	{
		_gameManager->StateChange(NewObject<UState_CondorChoice>(UState_CondorChoice::StaticClass()));
	}
}
