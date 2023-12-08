#include "State_CheckWinConditions.h"
#include "GameManager.h"
#include "GridManager.h"
#include "State_AwaitingInputs.h"
#include "State_CondorAttack.h"
#include "State_CondorWait.h"
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
		//_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
		if (ATileActor_Character_Condor::GetInstance() != nullptr)
		{
			if (ATileActor_Character_Condor::GetInstance()->isWaitLastRound == true)
			{
				UE_LOG(LogTemp, Warning, TEXT("UState_CondorAttack"));
				_gameManager->StateChange(NewObject<UState_CondorAttack>(UState_CondorAttack::StaticClass()));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("UState_CondorWait"));
				_gameManager->StateChange(NewObject<UState_CondorWait>(UState_CondorWait::StaticClass()));
			}
		}
		else
		{
			_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
		}
		
	}
}
