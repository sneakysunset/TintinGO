// Fill out your copyright notice in the Description page of Project Settings.


#include "State_RefreshTileItems.h"

#include "Barrier.h"
#include "MainGameMode.h"
#include "State_PeruviensMove.h"
#include "State_TA_Move.h"
#include "Tile.h"
#include "TileActor_Character_Tintin.h"

void UState_RefreshTileItems::OnStateEnter()
{
	Super::OnStateEnter();

	if(_gameManager->DebugStateChange)
		UE_LOG(LogTemp, Warning, TEXT("Refresh Tintin Tile Items State Enter"));
	
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	_tintin = ATileActor_Character_Tintin::GetInstance();
	
	for(auto actor : _tintin->GetCurrentTile()->_tileActors)
	{
		_barrier->_actors.Add(actor);
	}
	
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
}

void UState_RefreshTileItems::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);

	if(_barrier->_isBarriereCompleted)
	{
		_gameManager->StateChange(NewObject<UState_PeruviensMove>(UState_PeruviensMove::StaticClass()));
	}
	
	_barrier->OnTick(DeltaTime);
}
