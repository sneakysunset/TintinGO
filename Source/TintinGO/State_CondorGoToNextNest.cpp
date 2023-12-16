// Fill out your copyright notice in the Description page of Project Settings.

#include "State_CondorGoToNextNest.h"
#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_MilouRotate.h"
#include "State_TA_Move.h"

void UState_CondorGoToNextNest::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Condor Wait State Enter"));
	for (auto condor : _gameManager->_condors)
	{
		condor->_characters.Empty();
		_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
		ATile* previousCondorTile = condor->GetCurrentTile();
		condor->SetNextTile(_gameManager->_nests[(condor->currentNestNb + 1) %_gameManager->_nests.Num()]);
		condor->SetCurrentTile(condor->GetNextTile());
		_gameManager->ChangeTile(_barrier, previousCondorTile, condor->GetCurrentTile());
		_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
		Cast<UState_TA_Move>(condor->_currentState_TA)->_actorSpeed = condor->_speed;
		Cast<UState_TA_Move>(condor->_currentState_TA)->_speed = condor->_speed;
	}
}

void UState_CondorGoToNextNest::OnStateTick(float DeltaTime)
{
	if(_barrier->_isBarriereCompleted)
	{
		_gameManager->StateChange(NewObject<UState_MilouRotate>(UState_MilouRotate::StaticClass()));
	}

	_barrier->OnTick(DeltaTime);
	UState::OnStateTick(DeltaTime);
}

void UState_CondorGoToNextNest::OnStateExit()
{
	UState::OnStateExit();
}