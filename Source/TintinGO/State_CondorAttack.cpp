// Fill out your copyright notice in the Description page of Project Settings.


#include "State_CondorAttack.h"

#include "GameManager.h"
#include "GridManager.h"
#include "MainGameMode.h"
#include "State_AwaitingInputs.h"
#include "State_CondorDropCharacters.h"
#include "State_TA_Move.h"
#include "Tile.h"
#include "TileActor_Character_Condor.h"
#include "TileActor_Character_Peruvien.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UState_CondorAttack::OnStateEnter()
{
	UState::OnStateEnter();
	if(_gameManager->DebugStateChange)
		UE_LOG(LogTemp, Warning, TEXT("Condor Attack State Enter"));


	for(const auto condor : _gameManager->_condors)
	{
		if(condor->isWaitLastRound)
		{
			ATile* currentTile = condor->GetCurrentTile();

			switch (currentTile->_nestDirection)
			{
				case EAngle::Left :
					for (int i = currentTile->_column; i >= 0; i--)
					{
						_gameManager->_gridTiles[currentTile->_row].Tiles[i]->RefreshTileBackgroundRenderer(0);
					}
					break;
				case EAngle::Right :
					for (int i = currentTile->_column; i < _gameManager->_gridTiles[0].Tiles.Num(); i++)
					{
						_gameManager->_gridTiles[currentTile->_row].Tiles[i]->RefreshTileBackgroundRenderer(0);
					}
					break;
				case EAngle::Up :
					for (int i = currentTile->_row; i > _gameManager->_gridTiles.Num(); i++)
					{
						_gameManager->_gridTiles[i].Tiles[currentTile->_column]->RefreshTileBackgroundRenderer(0);
					}
					break;
				case EAngle::Down :
					for (int i = currentTile->_row; i >= 0; i--)
					{
						_gameManager->_gridTiles[i].Tiles[currentTile->_column]->RefreshTileBackgroundRenderer(0);
					}
					break;
				default:
				break;
			}
		}
	}
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	for (const auto condor : _gameManager->_condors)
	{
		condor->isWaitLastRound = false;
		ATile* currentTile = condor->GetCurrentTile();
		ATile* previousCondorTile = nullptr;


		switch (currentTile->_nestDirection)
		{
			case EAngle::Left :
				for (int i = currentTile->_column - 1; i >= 0; --i)
				{
					if(_gameManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors.Num() > 0)
					{
						for (auto actor : _gameManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}

						if (condor->_characters.Num() > 0)
						{
							previousCondorTile = currentTile;
							condor->SetNextTile(_gameManager->_gridTiles[currentTile->_row].Tiles[i]);
							condor->SetCurrentTile(condor->GetNextTile());
							break;
						}
					}
					else if (i == 0)
					{
						for (auto actor : _gameManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}
						
						previousCondorTile = currentTile;
						condor->SetNextTile(_gameManager->_gridTiles[currentTile->_row].Tiles[i]);
						condor->SetCurrentTile(condor->GetNextTile());
						break;
					}
				}
			break;
			case EAngle::Right :
				for (int i = currentTile->_column; i < _gameManager->_gridTiles[currentTile->_row].Tiles.Num(); i++)
				{
					if(_gameManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors.Num() > 0)
					{
						for (int j = 0; j < _gameManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors.Num(); j ++)
						{
							if(_gameManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors[j]->IsA<ATileActor_Character>() && !_gameManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors[j]->IsA<ATileActor_Character_Condor>())
							{
								condor->_characters.Add(Cast<ATileActor_Character>(_gameManager->_gridTiles[currentTile->_row].Tiles[i]->_tileActors[j]));
							}
						}

						if (condor->_characters.Num() > 0)
						{
							previousCondorTile = currentTile;
							condor->SetNextTile(_gameManager->_gridTiles[currentTile->_row].Tiles[i]);
							condor->SetCurrentTile(condor->GetNextTile());
							break;
						}
					}

					if(i == _gameManager->_gridTiles[currentTile->_row].Tiles.Num() - 1)
					{
						previousCondorTile = currentTile;
						condor->SetNextTile(_gameManager->_gridTiles[currentTile->_row].Tiles[i]);
						condor->SetCurrentTile(condor->GetNextTile());
					}
				}

				break;
			case EAngle::Up :
				for (int i = currentTile->_row + 1; i > _gameManager->_gridTiles.Num(); ++i)
				{
					if(_gameManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors.Num() > 0)
					{
						for (ATileActor* actor : _gameManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors)
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
							condor->SetNextTile(_gameManager->_gridTiles[i].Tiles[currentTile->_column]);
							condor->SetCurrentTile(condor->GetNextTile());
							break;
						}
					}
					else if (i == _gameManager->_gridTiles.Num() - 1)
					{
						for (ATileActor* actor : _gameManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}
						
						_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
						previousCondorTile = currentTile;
						condor->SetNextTile(_gameManager->_gridTiles[i].Tiles[currentTile->_column]);
						condor->SetCurrentTile(condor->GetNextTile());
						break;
					}
				}
				break;
			case EAngle::Down :
				for (int i = currentTile->_row - 1; i >= 0; --i)
				{
					if(_gameManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors.Num() > 0)
					{
						for (ATileActor* actor : _gameManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors)
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
							condor->SetNextTile(_gameManager->_gridTiles[i].Tiles[currentTile->_column]);
							condor->SetCurrentTile(condor->GetNextTile());
							break;
						}
					}
					else if (i == 0)
					{
						for (ATileActor* actor : _gameManager->_gridTiles[i].Tiles[currentTile->_column]->_tileActors)
						{
							if(IsValid(Cast<ATileActor_Character>(actor)))
							{
								condor->_characters.Add(Cast<ATileActor_Character>(actor));
							}
						}
						
						_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
						previousCondorTile = currentTile;
						condor->SetNextTile(_gameManager->_gridTiles[i].Tiles[currentTile->_column]);
						condor->SetCurrentTile(condor->GetNextTile());
						break;
					}
				}
				break;
			default:
				break;
		}
		FVector TargetDirection = condor->GetNextTile()->GetActorLocation() - condor->GetActorLocation();
		const FRotator TargetRotation = TargetDirection.Rotation();
		condor->_startRotation = condor->GetActorRotation().Quaternion();
		condor->_endRotation = TargetRotation.Quaternion();
		_gameManager->ChangeTile(_barrier, previousCondorTile, condor->GetCurrentTile());
		_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
		const float distance =  FMath::Abs(previousCondorTile->_row - condor->GetNextTile()->_row) + FMath::Abs(previousCondorTile->_column - condor->GetNextTile()->_column);
		Cast<UState_TA_Move>(condor->_currentState_TA)->_actorSpeed = condor->_speed / distance;
		Cast<UState_TA_Move>(condor->_currentState_TA)->_speed = condor->_speed / distance;
		rotateInterpolationValue = 0;
		UGameplayStatics::SpawnSoundAtLocation(condor, condor->S_CondorAttack, condor->GetActorLocation());
	}
}

void UState_CondorAttack::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);

	for(auto condor : _gameManager->_condors)
	{
		FQuat rot =  FQuat::Slerp(condor->_startRotation, condor->_endRotation, rotateInterpolationValue);
		condor->SetActorRotation(rot);
		rotateInterpolationValue +=DeltaTime * condor->_rotateSpeed;
		rotateInterpolationValue =  FMath::Clamp(rotateInterpolationValue, 0, 1);
		for(auto character : condor->_characters)
		{
			if(character->IsA<ATileActor_Character_Peruvien>())
			{
				auto peruvien = Cast<ATileActor_Character_Peruvien>(character);
				_gameManager->SetTilesPeruvienColor(false, peruvien->angle,peruvien->GetCurrentTile());
			}
		}
	}
	
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