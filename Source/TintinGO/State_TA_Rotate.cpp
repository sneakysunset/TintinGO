#include "State_TA_Rotate.h"

#include "GameManager.h"
#include "GridManager.h"
#include "MainGameMode.h"
#include "TileActor_Character.h"
#include "TileActor_Character_Peruvien.h"

void UState_TA_Rotate::OnStateEnter()
{
	Super::OnStateEnter();
	_startRotation = _tileActor->GetActorRotation();
	_speed = _gameManager->_rotateSpeed;
	if(!IsValid(_tileActor))
	{
		UE_LOG(LogTemp, Error, TEXT("Not Valid Actor for rotate"));
		return;
	}
	const ATile* tile = _tileActor->GetCurrentTile();
	ATileActor_Character* character = Cast<ATileActor_Character>(_tileActor);
	const ATile* nextTile = character->GetNextTile();
	if(tile == nullptr)
	{
		//UE_LOG(LogTemp, Error, TEXT("Not Valid tile for rotate"));
		return;
	}
	EAngle angle = EAngle::Up;
	if(nextTile == nullptr)
	{
		ATileActor_Character_Peruvien* peruvien = Cast<ATileActor_Character_Peruvien>(character);
		if(peruvien->_currentPBehaviour == EPeruvienBehaviour::SearchingTintin)
		{
			angle = peruvien->_tintinAngle;
			peruvien->_currentPBehaviour = EPeruvienBehaviour::Returning;
		}
		else
		{
			angle = peruvien->_startingAngle;		
		}
	}
	else
	{
		if(nextTile->_row - tile->_row == -1)
			angle = EAngle::Down;
		else if(nextTile->_column - tile->_column == 1)
			angle = EAngle::Right;
		else if(nextTile->_column - tile->_column == -1)
			angle = EAngle::Left;
	}

	float angleValue = 0;
	switch(angle)
	{
		case EAngle::Right: angleValue = 180; break;
		case EAngle::Up: angleValue = 90; break;
		case EAngle::Left : angleValue = 0; break;
		case EAngle::Down : angleValue = 270; break;
	}
	character->angle = angle;
	_endRotation = FQuat::MakeFromEuler(FVector::UpVector * (angleValue + character->_baseAngleOffset)).Rotator();
}

void UState_TA_Rotate::OnStateTick(float DeltaTime)
{
	_tileActor->SetActorRotation(FQuat::Slerp(_startRotation.Quaternion(), _endRotation.Quaternion(), _interpolateValue));
	Super::OnStateTick(DeltaTime);
}

void UState_TA_Rotate::OnStateComplete()
{
	Super::OnStateComplete();
	_tileActor->SetActorRotation(_endRotation);
}
