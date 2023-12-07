// Fill out your copyright notice in the Description page of Project Settings.


#include "State_CondorAttack.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_TA_Move.h"
#include "Tile.h"

void UState_CondorAttack::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("CondorAttack State Enter"));
	_condor = ATileActor_Character_Condor::GetInstance();
	_gridManager = AGridManager::GetInstance();
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	
	ATile* previousCondorTile =_condor->GetCurrentTile();
	
	previousCondorTile->_tileActors.Remove(_condor);

	switch (_condor->GetCurrentTile()->_tileType)
	{
		case ETileType::Nest1Position :
			_condor->SetNextTile(_gridManager->_endNest1Tile);
			UE_LOG(LogTemp, Warning, TEXT("Nest1Position"));
			_condor->isWaitLastRound = false;
			break;
		case ETileType::EndNest1Position :
			_condor->SetNextTile(_gridManager->_nest2Tile);
			UE_LOG(LogTemp, Warning, TEXT("EndNest1Position"));
			break;
		case ETileType::Nest2Position :
			_condor->SetNextTile(_gridManager->_endNest2Tile);
			UE_LOG(LogTemp, Warning, TEXT("Nest2Position"));
			_condor->isWaitLastRound = false;
			break;
		case ETileType::EndNest2Position :
			_condor->SetNextTile(_gridManager->_nest1Tile);
			UE_LOG(LogTemp, Warning, TEXT("EndNest2Position"));
			break;
		case ETileType::Neutral :
			break;
		case ETileType::StartingPosition :
			break;
		case ETileType::EndingPosition :
			break;
		default:
			break;
	}
	
	_condor->SetCurrentTile(_condor->GetNextTile());

	_condor->ChangeTile(_barrier, previousCondorTile);
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
}

void UState_CondorAttack::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	
	if(_barrier->_isBarriereCompleted == true)
	{
		switch (_condor->GetCurrentTile()->_tileType)
		{
			case ETileType::Nest1Position :
				_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
				UE_LOG(LogTemp, Warning, TEXT("ETileType::Nest1Position"));
				break;
			case ETileType::EndNest1Position :
				_gameManager->StateChange(NewObject<UState_CondorAttack>(UState_CondorAttack::StaticClass()));
				UE_LOG(LogTemp, Warning, TEXT("ETileType::EndNest1Position"));
				break;
			case ETileType::Nest2Position :
				_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
				UE_LOG(LogTemp, Warning, TEXT("ETileType::Nest2Position"));
				break;
			case ETileType::EndNest2Position :
				_gameManager->StateChange(NewObject<UState_CondorAttack>(UState_CondorAttack::StaticClass()));
				UE_LOG(LogTemp, Warning, TEXT("ETileType::EndNest2Position"));
				break;
			case ETileType::Neutral :
				UE_LOG(LogTemp, Warning, TEXT("ETileType::Neutral"));
				break;
			case ETileType::StartingPosition :
				UE_LOG(LogTemp, Warning, TEXT("ETileType::StartingPosition"));
				break;
			case ETileType::EndingPosition :
				UE_LOG(LogTemp, Warning, TEXT("ETileType::EndingPosition"));
				break;
			default:
				break;
		}
	}
	
	_barrier->OnTick(DeltaTime);
}

void UState_CondorAttack::OnStateExit()
{
	UState::OnStateExit();
}