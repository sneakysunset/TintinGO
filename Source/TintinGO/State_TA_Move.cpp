#include "State_TA_Move.h"

#include "Tile.h"
#include "TileActor.h"

void UState_TA_Move::OnStateEnter()
{
	UState_TActor::OnStateEnter();
	//UE_LOG(LogTemp, Warning, TEXT("On State TC Move Enter"));
	_startPosition = _tileActor->GetCurrentTile()->GetActorLocation();
	if(!IsValid(_tileActor))
	{
		UE_LOG(LogTemp, Error, TEXT("Not Valid Actor for move"));
		return;
	}
	ATile* tile = _tileActor->GetCurrentTile();
	if(tile == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Valid tile for move"));
		return;
	}
	_endPosition = tile->GetTileActorPosition(_tileActor);
	UE_LOG(LogTemp, Warning, TEXT("actor %s tile %d %d , Destination = %f, %f"), *_tileActor->GetName(),tile->_row, tile->_column, _endPosition.X, _endPosition.Y)
}


void UState_TA_Move::OnStateTick(float DeltaTime)
{
	_tileActor->SetActorLocation(_startPosition + (_endPosition - _startPosition) * _interpolateValue);
	//UE_LOG(LogTemp, Warning, TEXT("%s interpolateValue = %f"), *_tileActor->GetName(), _interpolateValue);
	UState_TActor::OnStateTick(DeltaTime);
}

void UState_TA_Move::OnStateComplete()
{
	UState_TActor::OnStateComplete();
	_tileActor->AttachToActor(_tileActor->GetCurrentTile(), FAttachmentTransformRules::KeepWorldTransform);
	_tileActor->SetActorLocation(_endPosition);
}

