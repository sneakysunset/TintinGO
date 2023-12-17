// Fill out your copyright notice in the Description page of Project Settings.


#include "State_RefreshMilouItems.h"

#include "Barrier.h"
#include "State_AwaitingInputs.h"
#include "State_TA_Move.h"

void UState_RefreshMilouItems::OnStateEnter()
{
	Super::OnStateEnter();
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	_milou = ATileActor_Character_Milou::GetInstance();
	
	for(auto actor : _milou->GetCurrentTile()->_tileActors)
	{
		_barrier->_actors.Add(actor);
	}
	
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
}

void UState_RefreshMilouItems::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);

	if(_barrier->_isBarriereCompleted)
	{
		_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
	}
	
	_barrier->OnTick(DeltaTime);
}