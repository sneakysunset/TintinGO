// Fill out your copyright notice in the Description page of Project Settings.


#include "State_CondorChoice.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_CondorAttack.h"
#include "State_CondorWait.h"

void UState_CondorChoice::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Condor Choice State Enter"));

	_gridManager = AGridManager::GetInstance();

	for (auto condor : _gridManager->_condors)
	{
		for (int i = 0; i < _gridManager->_nests.Num(); ++i)
		{
			if (condor->GetCurrentTile() == _gridManager->_nests[i])
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