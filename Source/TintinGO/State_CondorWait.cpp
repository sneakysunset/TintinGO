// Fill out your copyright notice in the Description page of Project Settings.


#include "State_CondorWait.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "TileActor_Character_Condor.h"

void UState_CondorWait::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Condor Wait State Enter"));

	_gridManager = AGridManager::GetInstance();
	
	for (auto condor : _gridManager->_condors)
	{
		condor->_characters.Empty();
		condor->isWaitLastRound = true;
	}
	
	_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
}

void UState_CondorWait::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
}

void UState_CondorWait::OnStateExit()
{
	UState::OnStateExit();

	//UE_LOG(LogTemp, Warning, TEXT("Condor Wait State Exit"));
}


