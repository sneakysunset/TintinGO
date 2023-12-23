#include "State_MilouRotate.h"

#include "State_AwaitingInputs.h"
#include "State_MilouMove.h"
#include "Tile.h"
#include "TileActor_Character_Milou.h"

void UState_MilouRotate::OnStateEnter()
{
	Super::OnStateEnter();
	if(_gameManager->DebugStateChange)
	UE_LOG(LogTemp, Warning, TEXT("State Enter Milou Rotate"));
	_milou = ATileActor_Character_Milou::GetInstance();
	if(_milou->isBoundToTintin || _milou->MilouTilePath.Num() == 0)
	{
		_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
		return;
	}
	const ATile* tile = _milou->GetCurrentTile();
	const ATile* nextTile = _milou->GetNextTile();
	_startRotation = _milou->GetActorRotation();
	EAngle angle = EAngle::Up;
	if(_milou->MilouTilePath.Last()->_row - tile->_row == -1)
		angle = EAngle::Down;
	else if(_milou->MilouTilePath.Last()->_column - tile->_column == 1)
		angle = EAngle::Right;
	else if(_milou->MilouTilePath.Last()->_column - tile->_column == -1)
		angle = EAngle::Left;
	
	if(angle != _milou->angle)
	{
		float angleValue = 0;
		switch(angle)
		{
		case EAngle::Right: angleValue = 180; break;
		case EAngle::Up: angleValue = 90; break;
		case EAngle::Left : angleValue = 0; break;
		case EAngle::Down : angleValue = 270; break;
		}

		_milou->angle = angle;
		_endRotation = FQuat::MakeFromEuler(FVector::UpVector * (angleValue + _milou->_baseAngleOffset)).Rotator();
	}
	else
	{
		_gameManager->StateChange(NewObject<UState_MilouMove>(UState_MilouMove::StaticClass()));
	}
}

void UState_MilouRotate::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);
	_interpolateValue += DeltaTime * _gameManager->_rotateSpeed;

	_milou->SetActorRotation(FQuat::Slerp(_startRotation.Quaternion(), _endRotation.Quaternion(), _interpolateValue));
	Super::OnStateTick(DeltaTime);
	if(_interpolateValue >= 1)
	{
		_milou->SetActorRotation(_endRotation);
		_gameManager->StateChange(NewObject<UState_MilouMove>(UState_MilouMove::StaticClass()));
	}
}

void UState_MilouRotate::OnStateExit()
{
	Super::OnStateExit();
}
