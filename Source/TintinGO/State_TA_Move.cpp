#include "State_TA_Move.h"

#include "Tile.h"
#include "TileActor.h"

void UState_TA_Move::OnStateEnter()
{
	UState_TActor::OnStateEnter();
	//UE_LOG(LogTemp, Warning, TEXT("On State TC Move Enter"));
	_startPosition = _tileActor->GetActorLocation();
	if(!IsValid(_tileActor))
	{
		UE_LOG(LogTemp, Error, TEXT("Not Valid Actor for move"));
		return;
	}
	ATile* tile = _tileActor->GetCurrentTile();
	if(_tileActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Valid Actor for move"));
		return;
	}
	_endPosition = tile->GetTileActorPosition(_tileActor);
}


void UState_TA_Move::OnStateTick(float DeltaTime)
{
	_tileActor->SetActorLocation(_startPosition + (_endPosition - _startPosition) * _interpolateValue);
	UState_TActor::OnStateTick(DeltaTime);
}

void UState_TA_Move::OnStateComplete()
{
	UState_TActor::OnStateComplete();
	_tileActor->SetActorLocation(_endPosition);
}

