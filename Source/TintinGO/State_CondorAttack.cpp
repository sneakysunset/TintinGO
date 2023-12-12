// Fill out your copyright notice in the Description page of Project Settings.


#include "State_CondorAttack.h"

#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_TA_Move.h"
#include "Tile.h"

void UState_CondorAttack::OnStateEnter()
{
	UState::OnStateEnter();
	
	/*if (ATileActor_Character_Condor::GetInstance() != nullptr)
	{
		_condor = ATileActor_Character_Condor::GetInstance();
		AGridManager* _gridManager = AGridManager::GetInstance();
		_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	
		ATile* previousCondorTile =_condor->GetCurrentTile();
		previousCondorTile->_tileActors.Remove(_condor);

		switch (_condor->GetCurrentTile()->_tileType)
		{
		case ETileType::Nest1Position :
			_condor->SetNextTile(_gridManager->_endNest1Tile);
			_condor->isWaitLastRound = false;
			break;
		case ETileType::EndNest1Position :
			_condor->SetNextTile(_gridManager->_nest2Tile);
			break;
		case ETileType::Nest2Position :
			_condor->SetNextTile(_gridManager->_endNest2Tile);
			_condor->isWaitLastRound = false;
			break;
		case ETileType::EndNest2Position :
			_condor->SetNextTile(_gridManager->_nest1Tile);
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

		
		UE_LOG(LogTemp, Error, TEXT("Condor Next Tile : %p"), _condor->GetNextTile());
		_condor->SetCurrentTile(_condor->GetNextTile());
		_gridManager->ChangeTile(_barrier, previousCondorTile, _condor->GetCurrentTile());
		_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
	}
	else
	{
		_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
	}*/
}

void UState_CondorAttack::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);

	/*if (IsValid(ATileActor_Character_Condor::GetInstance()))
	{
		if(_barrier->_isBarriereCompleted == true)
		{
			switch (_condor->GetCurrentTile()->_tileType)
			{
			case ETileType::Nest1Position :
				_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
				break;
			case ETileType::EndNest1Position :
				_gameManager->StateChange(NewObject<UState_CondorAttack>(UState_CondorAttack::StaticClass()));
				break;
			case ETileType::Nest2Position :
				_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
				break;
			case ETileType::EndNest2Position :
				_gameManager->StateChange(NewObject<UState_CondorAttack>(UState_CondorAttack::StaticClass()));
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
		}*/
	
		//_barrier->OnTick(DeltaTime);
	//}
}

void UState_CondorAttack::OnStateExit()
{
	UState::OnStateExit();
}