#include "State_PlayerMove.h"

#include "GameManager.h"
#include "State_TriggerItemsCharacters.h"


void State_PlayerMove::OnStateEnter()
{
	State_TActor_Move::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Player Move State Enter"));
	_tintin = ATileActor_Character_Tintin::GetInstance();
	_milou = ATileActor_Character_Milou::GetInstance();
	_interpolateValue = 0;
}

void State_PlayerMove::OnStateTick(float DeltaTime)
{
	State_TActor_Move::OnStateTick(DeltaTime);
	_interpolateValue += DeltaTime * _gameManager->speed;
	FVector startPos = _tintin->_currentTile->GetActorLocation();
	FVector const endPos = _tintin->_nextTile->GetActorLocation();
	FVector const lerpVector = startPos + (endPos - startPos) * _interpolateValue;
	_tintin->SetActorLocation(lerpVector);
	if(_milou->isBoundToTintin)
	{
		FVector mStartPos = _milou->_currentTile->GetActorLocation();
		FVector const mEndPos =	_milou->_nextTile->GetActorLocation();
		FVector const mLerpVector = mStartPos + (mEndPos - mStartPos) * _interpolateValue;
		_milou->SetActorLocation(mLerpVector);
	}
	if(_interpolateValue >= 1)
	{
		_gameManager->StateChange(new State_TriggerItemsCharacters());
	}
}

void State_PlayerMove::OnStateExit()
{
	State_TActor_Move::OnStateExit();
	_tintin->_currentTile = _tintin->_nextTile;
	if(_milou->isBoundToTintin) _milou->_currentTile =_milou->_nextTile;
}

