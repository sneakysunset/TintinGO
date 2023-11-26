#include "State_TA_Move.h"

#include "Tile.h"
#include "TileActor_Character.h"

void UState_TA_Move::OnStateEnter()
{
	UState_TActor::OnStateEnter();
	//UE_LOG(LogTemp, Warning, TEXT("On State TC Move Enter"));
	if(!IsValid(_tileActor))
	{
		UE_LOG(LogTemp, Error, TEXT("Not Valid Actor for move"));
		return;
	}
	_startPosition = _tileActor->GetActorLocation();
	_endPosition = _tileActor->GetCurrentTile()->GetTileActorPosition(_tileActor);
}


void UState_TA_Move::OnStateTick(float DeltaTime)
{
	_tileActor->SetActorLocation(_startPosition + (_endPosition - _startPosition) * _interpolateValue);
	Super::OnStateTick(DeltaTime);
}

void UState_TA_Move::OnStateComplete()
{
	Super::OnStateComplete();
	_tileActor->SetActorLocation(_endPosition);
}

