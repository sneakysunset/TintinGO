// Fill out your copyright notice in the Description page of Project Settings.


#include "State_PlayerRotate.h"

#include "GameManager.h"
#include "State_PlayerMove.h"
#include "Tile.h"
#include "TileActor_Character_Tintin.h"

void UState_PlayerRotate::OnStateEnter()
{
	Super::OnStateEnter();

	UE_LOG(LogTemp, Warning, TEXT("State Enter Player Rotate"));
	_tintin = ATileActor_Character_Tintin::GetInstance();
	_milou = ATileActor_Character_Milou::GetInstance();
	const ATile* tile = _tintin->GetCurrentTile();
	const ATile* nextTile = _tintin->GetNextTile();
	_startRotation = _tintin->GetActorRotation();
	_milouStartRotation = _milou->GetActorRotation();

	EAngle angle = EAngle::Up;
	if(nextTile->_row - tile->_row == -1)
		angle = EAngle::Down;
	else if(nextTile->_column - tile->_column == 1)
		angle = EAngle::Right;
	else if(nextTile->_column - tile->_column == -1)
		angle = EAngle::Left;
	
	if(angle != _tintin->angle)
	{
		float angleValue = 0;
		switch(angle)
		{
		case EAngle::Right: angleValue = 180; break;
		case EAngle::Up: angleValue = 90; break;
		case EAngle::Left : angleValue = 0; break;
		case EAngle::Down : angleValue = 270; break;
		}
		
		_tintin->angle = angle;
		if(_milou->isBoundToTintin) _milou->angle = angle;
		_endRotation = FQuat::MakeFromEuler(FVector::UpVector * (angleValue + _tintin->_baseAngleOffset)).Rotator();
		_milouEndRotation = FQuat::MakeFromEuler(FVector::UpVector * (angleValue + _milou->_baseAngleOffset)).Rotator();
	}
	else
	{
		_gameManager->StateChange(NewObject<UState_PlayerMove>(UState_PlayerMove::StaticClass()));
	}
}

void UState_PlayerRotate::OnStateTick(float DeltaTime)
{
	_interpolateValue += DeltaTime * _gameManager->_rotateSpeed;

	_tintin->SetActorRotation(FQuat::Slerp(_startRotation.Quaternion(), _endRotation.Quaternion(), _interpolateValue));
	if(_milou->isBoundToTintin)
		_milou->SetActorRotation(FQuat::Slerp(_milouStartRotation.Quaternion(), _milouEndRotation.Quaternion(), _interpolateValue));
	Super::OnStateTick(DeltaTime);
	if(_interpolateValue >= 1)
	{
		_tintin->SetActorRotation(_endRotation);
		if(_milou->isBoundToTintin)
			_milou->SetActorRotation(_milouEndRotation);
		_gameManager->StateChange(NewObject<UState_PlayerMove>(UState_PlayerMove::StaticClass()));
	}
}

void UState_PlayerRotate::OnStateExit()
{
	Super::OnStateExit();
}
