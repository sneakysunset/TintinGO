// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrier.h"

#include "State_TActor.h"
#include "State_TA_Neutral.h"
#include "State_TA_Move.h"
#include "TileActor.h"
#include "Tile.h"

//Change state of every actor to the specified state in the parameters.
void UBarrier::OnBarrierIni(TSubclassOf<UState_TActor> newState)
{
	for (int i = 0; i < _actors.Num(); i++)
	{
		_actors[i]->ChangeState(NewObject<UState_TActor>(this ,newState));
	}
}

void UBarrier::OnTick(float DeltaTime)
{
	for (int i = 0; i < _actors.Num(); i++)
	{
		if(_actors[i] == nullptr || _actors[i]->_currentState_TA->_isStateComplete)
		{
			_actors[i]->ChangeState(NewObject<UState_TA_Neutral>(UState_TA_Neutral::StaticClass()));
			_actors.RemoveAt(i);
			i--;
		}
	}
	if(_actors.Num() == 0)
	{
		_isBarriereCompleted = true;
	}
}
