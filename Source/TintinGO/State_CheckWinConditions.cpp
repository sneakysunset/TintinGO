#include "Math/UnrealMathUtility.h"
#include "State_CheckWinConditions.h"
#include "GameManager.h"
#include "GridManager.h"
#include "State_AwaitingInputs.h"

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
		UE_LOG(LogTemp, Warning, TEXT("%d, %d"), _tintin->GetCurrentTile()->_row, gridManager->GetEndTile()->_row);
		_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
	}
}
