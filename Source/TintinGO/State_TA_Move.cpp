﻿#include "State_TA_Move.h"

#include "Tile.h"
#include "TileActor.h"
#include "TileActor_Character_Peruvien.h"

void UState_TA_Move::OnStateEnter()
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

	_Peruvien = nullptr;
	if(_tileActor->IsA<ATileActor_Character_Peruvien>())
	{
		_Peruvien = Cast<ATileActor_Character_Peruvien>(_tileActor);
	}
}


void UState_TA_Move::OnStateTick(float DeltaTime)
{
	_tileActor->SetActorLocation(_startPosition + (_endPosition - _startPosition) * _interpolateValue);
	if(_Peruvien != nullptr)
	_Peruvien->AddSplinePoint();
	UState_TActor::OnStateTick(DeltaTime);
}

void UState_TA_Move::OnStateComplete()
{
	UState_TActor::OnStateComplete();
	_tileActor->AttachToActor(_tileActor->GetCurrentTile(), FAttachmentTransformRules::KeepWorldTransform);
	_tileActor->SetActorLocation(_endPosition);
}

