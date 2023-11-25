#include "State_TC_Move.h"

#include "GameManager.h"
#include "Tile.h"
#include "TileActor_Character.h"

void UState_TC_Move::OnStateEnter()
{
	UState_TActor::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("On State TC Move Enter"));
	_isStateComplete = false;
	_startPosition = _tileActor->GetActorLocation();
	_endPosition = _tileActor->GetCurrentTile()->GetTileActorPosition(_tileActor);
	_interpolateValue = 0;
}


void UState_TC_Move::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);
	_interpolateValue += DeltaTime * _gameManager->speed;
	_tileActor->SetActorLocation(_startPosition + (_endPosition - _startPosition) * _interpolateValue);
	if(_interpolateValue >= 1 && !_isStateComplete)
	{
		UE_LOG(LogTemp, Warning, TEXT("On State TC is complete"));
		_isStateComplete = true;
		_tileActor->SetActorLocation(_endPosition);
	}
}
