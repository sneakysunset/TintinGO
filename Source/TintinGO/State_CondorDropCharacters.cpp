// Fill out your copyright notice in the Description page of Project Settings.


#include "State_CondorDropCharacters.h"

#include "GridManager.h"
#include "GameManager.h"
#include "State_CondorGoToNextNest.h"
#include "State_TA_Move.h"

void UState_CondorDropCharacters::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Condor Wait State Enter"));

	ATile* nextNestTile = nullptr;
	ATile* targetTile = nullptr;
	ATile* previousTile = nullptr;
	_gridManager = AGridManager::GetInstance();
	
	for (auto condor : _gridManager->_condors)
	{
		nextNestTile = _gridManager->_nests[(condor->currentNestNb + 1) %_gridManager->_nests.Num()];

		if (condor->_characters.Num() > 0)
		{
			switch (nextNestTile->_nestDirection)
			{
				case ENestDirection::Left :
					_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
					targetTile = _gridManager->GetTile(nextNestTile->_row, nextNestTile->_column - 1);
					previousTile = condor->GetCurrentTile();
					condor->SetNextTile(targetTile );
					condor->SetCurrentTile(condor->GetNextTile());
					_gridManager->ChangeTile(_barrier, previousTile, condor->GetCurrentTile());
					
					for (auto Character : condor->_characters)
					{
						_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
						Character->SetNextTile(targetTile);
						Character->SetCurrentTile(Character->GetNextTile());
						_gridManager->ChangeTile(_barrier, previousTile, Character->GetCurrentTile());
					}

					_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
					break;
				
				case ENestDirection::Right :
					targetTile = _gridManager->GetTile(nextNestTile->_row, nextNestTile->_column + 1);
					_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
					previousTile = condor->GetCurrentTile();
					condor->SetNextTile(targetTile );
					condor->SetCurrentTile(condor->GetNextTile());
					_gridManager->ChangeTile(_barrier, previousTile, condor->GetCurrentTile());
						
					for (auto Character : condor->_characters)
					{
						_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
						Character->SetNextTile(targetTile);
						Character->SetCurrentTile(Character->GetNextTile());
						_gridManager->ChangeTile(_barrier, previousTile, Character->GetCurrentTile());
					}

					_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
					break;
				
				case ENestDirection::Top :
					targetTile = _gridManager->GetTile(nextNestTile->_row + 1, nextNestTile->_column);
					_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
					previousTile = condor->GetCurrentTile();
					condor->SetNextTile(targetTile);
					condor->SetCurrentTile(condor->GetNextTile());
					_gridManager->ChangeTile(_barrier, previousTile, condor->GetCurrentTile());
							
					for (auto Character : condor->_characters)
					{
						_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
						Character->SetNextTile(targetTile);
						Character->SetCurrentTile(Character->GetNextTile());
						_gridManager->ChangeTile(_barrier, previousTile, Character->GetCurrentTile());
					}

					_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
					break;
				
				case ENestDirection::Down :
					targetTile = _gridManager->GetTile(nextNestTile->_row - 1, nextNestTile->_column);
					_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
					previousTile = condor->GetCurrentTile();
					condor->SetNextTile(targetTile);
					condor->SetCurrentTile(condor->GetNextTile());
					_gridManager->ChangeTile(_barrier, previousTile, condor->GetCurrentTile());
								
					for (auto Character : condor->_characters)
					{
						_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
						Character->SetNextTile(targetTile);
						Character->SetCurrentTile(Character->GetNextTile());
						_gridManager->ChangeTile(_barrier, previousTile, Character->GetCurrentTile());
					}

					_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
					break;
				
				default:
					break;
			}
		}
	}
}

void UState_CondorDropCharacters::OnStateTick(float DeltaTime)
{
	if(IsValid(_barrier))
	{
		if (_barrier->_isBarriereCompleted) 
			_gameManager->StateChange(NewObject<UState_CondorGoToNextNest>(UState_CondorGoToNextNest::StaticClass()));

		_barrier->OnTick(DeltaTime);
	}
	else
	{
		_gameManager->StateChange(NewObject<UState_CondorGoToNextNest>(UState_CondorGoToNextNest::StaticClass()));
	}
	
	UState::OnStateTick(DeltaTime);
}

void UState_CondorDropCharacters::OnStateExit()
{
	UState::OnStateExit();
}