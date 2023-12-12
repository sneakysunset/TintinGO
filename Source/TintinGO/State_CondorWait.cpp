// Fill out your copyright notice in the Description page of Project Settings.


#include "State_CondorWait.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "TileActor_Character_Condor.h"

void UState_CondorWait::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Condor Wait State Enter"));

	/*if (ATileActor_Character_Condor::GetInstance() != nullptr)
	{
		_condor = ATileActor_Character_Condor::GetInstance();
		_condor->isWaitLastRound = true;
	}

	_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));*/
}

void UState_CondorWait::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
}

void UState_CondorWait::OnStateExit()
{
	UState::OnStateExit();
}