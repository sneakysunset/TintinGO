// Fill out your copyright notice in the Description page of Project Settings.

#include "State_CondorGoToNextNest.h"
#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_MilouRotate.h"
#include "State_TA_Move.h"
#include "TileActor_Character_Condor.h"

void UState_CondorGoToNextNest::OnStateEnter()
{
	UState::OnStateEnter();
	if(_gameManager->DebugStateChange)
	UE_LOG(LogTemp, Warning, TEXT("Condor Wait State Enter"));
	for (const auto condor : _gameManager->_condors)
	{
		condor->_characters.Empty();
		_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
		ATile* previousCondorTile = condor->GetCurrentTile();
		condor->SetNextTile(_gameManager->_nests[(condor->currentNestNb + 1) %_gameManager->_nests.Num()]);
		condor->SetCurrentTile(condor->GetNextTile());
		_gameManager->ChangeTile(_barrier, previousCondorTile, condor->GetCurrentTile());
		_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
		const float distance =  FMath::Abs(previousCondorTile->_row - condor->GetNextTile()->_row) + FMath::Abs(previousCondorTile->_column - condor->GetNextTile()->_column);
		Cast<UState_TA_Move>(condor->_currentState_TA)->_actorSpeed = condor->_speed / distance;
		Cast<UState_TA_Move>(condor->_currentState_TA)->_speed = condor->_speed / distance;
		FVector TargetDirection = condor->GetNextTile()->GetActorLocation() - condor->GetActorLocation();
		FRotator TargetRotation = TargetDirection.Rotation();
		TargetRotation.Roll = 0;
		TargetRotation.Pitch = 0;
		condor->_startRotation = condor->GetActorRotation().Quaternion();
		condor->_endRotation = TargetRotation.Quaternion();
		rotateInterpolationValue = 0;
	}
}

void UState_CondorGoToNextNest::OnStateTick(float DeltaTime)
{
	if(!_barrier->_isBarriereCompleted)
	{
		for(auto condor : _gameManager->_condors)
		{
			FQuat rot =  FQuat::Slerp(condor->_startRotation, condor->_endRotation, rotateInterpolationValue);
			FRotator rotR = rot.Rotator();
			condor->SetActorRotation(rot);
			rotateInterpolationValue +=DeltaTime * condor->_rotateSpeed;
			rotateInterpolationValue =  FMath::Clamp(rotateInterpolationValue, 0, 1);
		}
	}
	
	if(_barrier->_isBarriereCompleted)
	{
		if(!hasBarrierCompleted)
		{
			for (auto condor : _gameManager->_condors)
			{
				rotateInterpolationValue = 0;
				condor->_startRotation = condor->GetActorRotation().Quaternion();
				condor->_endRotation = condor->GetTargetRotation(condor->GetCurrentTile()->_nestDirection).Quaternion();
			}
			hasBarrierCompleted = true;
		}
		else
		{
			for(auto condor : _gameManager->_condors)
			{
				FQuat rot =  FQuat::Slerp(condor->_startRotation, condor->_endRotation, rotateInterpolationValue);
				FRotator rotR = rot.Rotator();
				condor->SetActorRotation(rot);
				rotateInterpolationValue +=DeltaTime * condor->_rotateSpeed;
				rotateInterpolationValue =  FMath::Clamp(rotateInterpolationValue, 0, 1);
			}
		}
		if(hasBarrierCompleted && rotateInterpolationValue >= 1)
		{
			_gameManager->StateChange(NewObject<UState_MilouRotate>(UState_MilouRotate::StaticClass()));
		}
	}

	_barrier->OnTick(DeltaTime);
	UState::OnStateTick(DeltaTime);
}

void UState_CondorGoToNextNest::OnStateExit()
{
	for (auto condor : _gameManager->_condors)
	{
		condor->SetUpRotation(condor->GetCurrentTile()->_nestDirection);
	}
	UState::OnStateExit();
}