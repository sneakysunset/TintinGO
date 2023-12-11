// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrier.h"

#include "State_TActor.h"
#include "State_TA_Neutral.h"
#include "State_TA_Move.h"
#include "TileActor.h"
#include "Tile.h"

void UBarrier::OnBarrierIni(TSubclassOf<UState_TActor> newState)
{
	for (int i = 0; i < _actors.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Barrier %s on Tile : %d %d"), *_actors[i]->GetName(), _actors[i]->GetCurrentTile()->_row,_actors[i]->GetCurrentTile()->_column);
		_actors[i]->ChangeState(NewObject<UState_TA_Move>(newState->StaticClass()));
	}
}

void UBarrier::OnTick(float DeltaTime)
{
	for (int i = 0; i < _actors.Num(); i++)
	{
		if(_actors[i] == nullptr || _actors[i]->_currentState_TA->_isStateComplete)
		{
			_actors[i]->ChangeState(NewObject<UState_TA_Neutral>(UState_TA_Neutral::StaticClass()));

			UE_LOG(LogTemp, Warning, TEXT("Barrier num %d %s on Tile : %d %d"), _actors.Num(), *_actors[i]->GetName(), _actors[i]->GetCurrentTile()->_row,_actors[i]->GetCurrentTile()->_column);
			_actors.RemoveAt(i);
			i--;
		}
	}
	if(_actors.Num() == 0)
	{
		_isBarriereCompleted = true;
	}
	
}
