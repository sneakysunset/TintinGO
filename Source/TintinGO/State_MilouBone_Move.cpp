// Fill out your copyright notice in the Description page of Project Settings.

#include "State_MilouBone_Move.h"
#include "Tile.h"
#include "TileActor.h"

void UState_MilouBone_Move::OnStateEnter()
{
	UState_TActor::OnStateEnter();
	if(_actorSpeed != 0)
	{
		_speed = _actorSpeed;
	}
	_startPosition = _tileActor->GetActorLocation();
	if(!IsValid(_tileActor))
	{
		return;
	}
	ATile* tile = _tileActor->GetCurrentTile();
	if(tile == nullptr)
	{
		//UE_LOG(LogTemp, Error, TEXT("Not Valid tile for move"));
		return;
	}
	_endPosition = tile->GetTileActorPosition(_tileActor);
}


void UState_MilouBone_Move::OnStateTick(float DeltaTime)
{
	_tileActor->SetActorLocation(_startPosition + (((FVector::UpVector * sin(_interpolateValue * 3.15)) * 5) + (_endPosition - _startPosition)) * _interpolateValue);
	UState_TActor::OnStateTick(DeltaTime);
}

void UState_MilouBone_Move::OnStateComplete()
{
	UState_TActor::OnStateComplete();
	_tileActor->AttachToActor(_tileActor->GetCurrentTile(), FAttachmentTransformRules::KeepWorldTransform);
	_tileActor->SetActorLocation(_endPosition);
}
