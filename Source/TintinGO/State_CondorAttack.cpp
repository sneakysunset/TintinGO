// Fill out your copyright notice in the Description page of Project Settings.


#include "State_CondorAttack.h"

#include "GameManager.h"
#include "GridManager.h"
#include "State_AwaitingInputs.h"
#include "State_CondorDropCharacters.h"
#include "State_TA_Move.h"
#include "Tile.h"

void UState_CondorAttack::OnStateEnter()
{
	UState::OnStateEnter();

	_gridManager = AGridManager::GetInstance();
	
	for (auto condor : _gridManager->_condors)
	{
		condor->isWaitLastRound = false;
		ATile* currentTile = condor->GetCurrentTile();
		ATile* previousCondorTile = nullptr;
		_barrier = NewObject<UBarrier>(UBarrier::StaticClass());

		switch (currentTile->_nestDirection)
		{
			case ENestDirection::Left :
				for (int i = currentTile->_column - 1; i >= 0; --i)
				{
					if(_gridManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors.Num() > 0)
					{
						for (auto actor : _gridManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}

						if (condor->_characters.Num() > 0)
						{
							previousCondorTile = currentTile;
							condor->SetNextTile(_gridManager->_gridTiles[currentTile->_row].Tiles[i]);
							condor->SetCurrentTile(condor->GetNextTile());
							break;
						}
					}
					else if (i == 0)
					{
						for (auto actor : _gridManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}
						
						previousCondorTile = currentTile;
						condor->SetNextTile(_gridManager->_gridTiles[currentTile->_row].Tiles[i]);
						condor->SetCurrentTile(condor->GetNextTile());
						break;
					}
				}
			break;
			case ENestDirection::Right :
				for (int i = currentTile->_column + 1; i < _gridManager->_gridTiles[0].Tiles.Num(); ++i)
				{
					if(_gridManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors.Num() > 0)
					{
						for (ATileActor* actor : _gridManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}

						if (condor->_characters.Num() > 0)
						{
							_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
							previousCondorTile = currentTile;
							condor->SetNextTile(_gridManager->_gridTiles[currentTile->_row].Tiles[i]);
							condor->SetCurrentTile(condor->GetNextTile());
							break;
						}
					}
					else if (i == _gridManager->_gridTiles[0].Tiles.Num() - 1)
					{
						for (ATileActor* actor : _gridManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}

						_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
						previousCondorTile = currentTile;
						condor->SetNextTile(_gridManager->_gridTiles[currentTile->_row].Tiles[i]);
						condor->SetCurrentTile(condor->GetNextTile());
						break;
					}
				}
				break;
			case ENestDirection::Top :
				for (int i = currentTile->_row + 1; i > _gridManager->_gridTiles.Num(); ++i)
				{
					if(_gridManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors.Num() > 0)
					{
						for (ATileActor* actor : _gridManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}
						
						if (condor->_characters.Num() > 0)
						{
							_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
							previousCondorTile = currentTile;
							condor->SetNextTile(_gridManager->_gridTiles[i].Tiles[currentTile->_column]);
							condor->SetCurrentTile(condor->GetNextTile());
							break;
						}
					}
					else if (i == _gridManager->_gridTiles.Num() - 1)
					{
						for (ATileActor* actor : _gridManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}
						
						_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
						previousCondorTile = currentTile;
						condor->SetNextTile(_gridManager->_gridTiles[i].Tiles[currentTile->_column]);
						condor->SetCurrentTile(condor->GetNextTile());
						break;
					}
				}
				break;
			case ENestDirection::Down :
				for (int i = currentTile->_row - 1; i >= 0; --i)
				{
					if(_gridManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors.Num() > 0)
					{
						for (ATileActor* actor : _gridManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}
						
						if (condor->_characters.Num() > 0)
						{
							_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
							previousCondorTile = currentTile;
							condor->SetNextTile(_gridManager->_gridTiles[i].Tiles[currentTile->_column]);
							condor->SetCurrentTile(condor->GetNextTile());
							break;
						}
					}
					else if (i == 0)
					{
						for (ATileActor* actor : _gridManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}
						
						_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
						previousCondorTile = currentTile;
						condor->SetNextTile(_gridManager->_gridTiles[i].Tiles[currentTile->_column]);
						condor->SetCurrentTile(condor->GetNextTile());
						break;
					}
				}
				break;
			default:
				break;
		}

		_gridManager->ChangeTile(_barrier, previousCondorTile, condor->GetCurrentTile());
		_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
	}
}

void UState_CondorAttack::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);

	if(_barrier->_isBarriereCompleted)
	{
		_gameManager->StateChange(NewObject<UState_CondorDropCharacters>(UState_CondorDropCharacters::StaticClass()));
	}
	 
	_barrier->OnTick(DeltaTime);
}

void UState_CondorAttack::OnStateExit()
{
	UState::OnStateExit();
}