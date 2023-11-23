#include "State_MilouMove.h"
#include "GameManager.h"
#include "State_AwaitingInputs.h"

State_MilouMove::State_MilouMove()
{
	
}

void State_MilouMove::OnStateEnter()
{
	State::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Milou Move State Enter"));
	_milou = ATileActor_Character_Milou::GetInstance();
	_milou->isBoundToTintin = false;
	_milou->_nextTile = _milou->MilouTilePath.Last();
	_milou->MilouTilePath[0]->SetHighlightedPath(true);
	_interpolateValue = 0;
}

void State_MilouMove::OnStateTick(float DeltaTime)
{
	State::OnStateTick(DeltaTime);
	_interpolateValue += DeltaTime * _gameManager->speed;

	FVector mStartPos = _milou->_currentTile->GetActorLocation();
	FVector const mEndPos = _milou->_nextTile->GetActorLocation();
	FVector const mLerpVector = mStartPos + (mEndPos - mStartPos) * _interpolateValue;
	_milou->SetActorLocation(mLerpVector);


	if(_interpolateValue >= 1)
	{
		_milou->_currentTile = _milou->MilouTilePath.Last();
		_milou->MilouTilePath.Last()->SetHighlightedPath(false);
		_milou->MilouTilePath.RemoveAt(_milou->MilouTilePath.Num() - 1);
		if(_milou->MilouTilePath.Num() > 0)
			_gameManager->StateChange(new State_MilouMove());
		else _gameManager->StateChange(new State_AwaitingInputs());
	}
}

void State_MilouMove::OnStateExit()
{
	State::OnStateExit();
}
