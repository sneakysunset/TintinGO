// Fill out your copyright notice in the Description page of Project Settings.


#include "State_CondorDropCharacters.h"

#include "GridManager.h"
#include "GameManager.h"
#include "State_CondorGoToNextNest.h"
#include "State_TA_Move.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_Character_Peruvien.h"


void UState_CondorDropCharacters::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Condor Wait State Enter"));

	ATile* targetTile;
	ATile* previousTile;
	_gridManager = AGridManager::GetInstance();
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	for (auto condor : _gridManager->_condors)
	{
		const ATile* nextNestTile = _gridManager->_nests[(condor->currentNestNb + 1) % _gridManager->_nests.Num()];

		if (condor->_characters.Num() > 0)
		{
			switch (nextNestTile->_nestDirection)
			{
				case ENestDirection::Left :
					targetTile = _gridManager->GetTile(nextNestTile->_row, nextNestTile->_column - 1);
					previousTile = condor->GetCurrentTile();
					condor->SetNextTile(targetTile );
					condor->SetCurrentTile(condor->GetNextTile());
					_gridManager->ChangeTile(_barrier, previousTile, condor->GetCurrentTile());
					
					for (auto Character : condor->_characters)
					{
						if(Character->IsA<ATileActor_Character_Milou>())
						{
							ATileActor_Character_Milou* milou = Cast<ATileActor_Character_Milou>(Character);
							if(!milou->isBoundToTintin)
								milou->_previousCondorTile = milou->GetCurrentTile();
						}
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
						if(Character->IsA<ATileActor_Character_Milou>())
						{
							ATileActor_Character_Milou* milou = Cast<ATileActor_Character_Milou>(Character);
							if(!milou->isBoundToTintin)
								milou->_previousCondorTile = milou->GetCurrentTile();
						}
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
						if(Character->IsA<ATileActor_Character_Milou>())
						{
							ATileActor_Character_Milou* milou = Cast<ATileActor_Character_Milou>(Character);
							if(!milou->isBoundToTintin)
								milou->_previousCondorTile = milou->GetCurrentTile();
						}
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
						if(Character->IsA<ATileActor_Character_Milou>())
						{
							ATileActor_Character_Milou* milou = Cast<ATileActor_Character_Milou>(Character);
							if(!milou->isBoundToTintin)
								milou->_previousCondorTile = milou->GetCurrentTile();
						}
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
	if(_barrier->_actors.Num() == 0)
	{
		_gameManager->StateChange(NewObject<UState_CondorGoToNextNest>(UState_CondorGoToNextNest::StaticClass()));
	}
}

void UState_CondorDropCharacters::OnStateTick(float DeltaTime)
{
	if(IsValid(_barrier))
	{
		if (_barrier->_isBarriereCompleted)
		{
			for (auto condor : _gridManager->_condors)
			{
				for (auto character : condor->_characters)
				{
					if(character->IsA<ATileActor_Character_Peruvien>())
					{
						ATileActor_Character_Peruvien* peruvien = Cast<ATileActor_Character_Peruvien>(character);
						_gridManager->MarkStepsOnGrid(character->GetCurrentTile());
						peruvien->PeruvienTilePath = _gridManager->GetPath(peruvien->_startingTile, false);
						peruvien->_currentPBehaviour = EPeruvienBehaviour::Returning;
						peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
					}
					else if(character->IsA<ATileActor_Character_Milou>())
					{
						ATileActor_Character_Milou* milou = Cast<ATileActor_Character_Milou>(character);
						if(!milou->isBoundToTintin)
						{
							_gridManager->MarkStepsOnGrid(character->GetCurrentTile());
							milou->MilouTilePath = _gridManager->GetPath(milou->_previousCondorTile, true);
						}
					}
				}
			}
			_gameManager->StateChange(NewObject<UState_CondorGoToNextNest>(UState_CondorGoToNextNest::StaticClass()));
		}

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