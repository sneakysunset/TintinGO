#include "State_CondorChoice.h"

#include "MainGameMode.h"
#include "State_AwaitingInputs.h"
#include "State_CondorAttack.h"
#include "State_CondorWait.h"

void UState_CondorChoice::OnStateEnter()
{
	UState::OnStateEnter();
	if(_gameManager->DebugStateChange)
	UE_LOG(LogTemp, Warning, TEXT("Condor Choice State Enter"));

	// Set condor's behaviour for current round
	for (auto condor : _gameManager->_condors)
	{
		for (int i = 0; i < _gameManager->_nests.Num(); ++i)
		{
			if (condor->GetCurrentTile() == _gameManager->_nests[i])
			{
				condor->currentNestNb = i;
				break;
			}
		}
		
		if (condor->isWaitLastRound)
		{
			_gameManager->StateChange(NewObject<UState_CondorAttack>(UState_CondorAttack::StaticClass()));
			return;
		}
	}
	
	_gameManager->StateChange(NewObject<UState_CondorWait>(UState_CondorWait::StaticClass()));
}

void UState_CondorChoice::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
}

void UState_CondorChoice::OnStateExit()
{
	UState::OnStateExit();
}