// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Character.h"

#include "Barrier.h"
#include "State_TActor.h"
#include "State_TC_Move.h"
#include "Tile.h"

void ATileActor_Character::ChangeTile(UBarrier* barrier, ATile* previousTile)
{
	barrier->_actors.Add(this);
	
	for(auto body : previousTile->_placableBodies)
	{
		UState_TActor* state = NewObject<UState_TC_Move>(UState_TC_Move::StaticClass());
		if(!barrier->_actors.Contains(body))
		{
			body->ChangeState(state);
			barrier->_actors.Add(body);
		}
	}

	for(auto body : this->_currentTile->_placableBodies)
	{
		UState_TActor* state = NewObject<UState_TC_Move>(UState_TC_Move::StaticClass());
		if(!barrier->_actors.Contains(body))
		{
			body->ChangeState(state);
			barrier->_actors.Add(body);
		}
	}
}

