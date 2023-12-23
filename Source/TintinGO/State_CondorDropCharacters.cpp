#include "State_CondorDropCharacters.h"

#include "GridManager.h"
#include "State_CondorGoToNextNest.h"
#include "State_TA_Move.h"
#include "TileActor_Character_Condor.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_Character_Peruvien.h"
#include "TileActor_Character_Tintin.h"
#include "Kismet/GameplayStatics.h"


void UState_CondorDropCharacters::OnStateEnter()
{
	UState::OnStateEnter();
	if(_gameManager->DebugStateChange)
	UE_LOG(LogTemp, Warning, TEXT("Condor Wait State Enter"));

	ATile* targetTile;
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());

	// Set targe tile of condor's movement path when condor grabs a character (Milou, enemy, Tintin)
	for (auto condor : _gameManager->_condors)
	{
		const ATile* nextNestTile = _gameManager->_nests[(condor->currentNestNb + 1) % _gameManager->_nests.Num()];

		if (condor->_characters.Num() > 0)
		{
			ATile* previousTile = condor->GetCurrentTile();

			switch (nextNestTile->_nestDirection)
			{

				case EAngle::Left :
				{
					targetTile = _gameManager->GetTile(nextNestTile->_row, nextNestTile->_column - 1);
					condor->SetNextTile(targetTile );
					condor->SetCurrentTile(condor->GetNextTile());
					_gameManager->ChangeTile(_barrier, previousTile, condor->GetCurrentTile());
					
					for (auto Character : condor->_characters)
					{
						if(Character->IsA<ATileActor_Character_Milou>())
						{
							ATileActor_Character_Milou* milou = Cast<ATileActor_Character_Milou>(Character);
							if(!milou->isBoundToTintin)
								milou->_previousCondorTile = milou->GetCurrentTile();
						}
						Character->SetNextTile(targetTile);
						Character->SetCurrentTile(Character->GetNextTile());
						_gameManager->ChangeTile(_barrier, previousTile, Character->GetCurrentTile());
					}
					break;
				}
				
				case EAngle::Right :
				{
					targetTile = _gameManager->GetTile(nextNestTile->_row, nextNestTile->_column + 1);
					condor->SetNextTile(targetTile );
					condor->SetCurrentTile(condor->GetNextTile());
					_gameManager->ChangeTile(_barrier, previousTile, condor->GetCurrentTile());
						
					for (auto Character : condor->_characters)
					{
						if(Character->IsA<ATileActor_Character_Milou>())
						{
							ATileActor_Character_Milou* milou = Cast<ATileActor_Character_Milou>(Character);
							if(!milou->isBoundToTintin)
								milou->_previousCondorTile = milou->GetCurrentTile();
						}
						Character->SetNextTile(targetTile);
						Character->SetCurrentTile(Character->GetNextTile());
						_gameManager->ChangeTile(_barrier, previousTile, Character->GetCurrentTile());
					}
					break;
				}
				
				case EAngle::Up :
				{
					targetTile = _gameManager->GetTile(nextNestTile->_row + 1, nextNestTile->_column);
					condor->SetNextTile(targetTile);
					condor->SetCurrentTile(condor->GetNextTile());
					_gameManager->ChangeTile(_barrier, previousTile, condor->GetCurrentTile());
							
					for (auto Character : condor->_characters)
					{
						if(Character->IsA<ATileActor_Character_Milou>())
						{
							ATileActor_Character_Milou* milou = Cast<ATileActor_Character_Milou>(Character);
							if(!milou->isBoundToTintin)
								milou->_previousCondorTile = milou->GetCurrentTile();
						}
						Character->SetNextTile(targetTile);
						Character->SetCurrentTile(Character->GetNextTile());
						_gameManager->ChangeTile(_barrier, previousTile, Character->GetCurrentTile());
					}
					break;
				}
				
				case EAngle::Down :
				{
					targetTile = _gameManager->GetTile(nextNestTile->_row - 1, nextNestTile->_column);
					condor->SetNextTile(targetTile);
					condor->SetCurrentTile(condor->GetNextTile());
					_gameManager->ChangeTile(_barrier, previousTile, condor->GetCurrentTile());
								
					for (auto Character : condor->_characters)
					{
						if(Character->IsA<ATileActor_Character_Milou>())
						{
							ATileActor_Character_Milou* milou = Cast<ATileActor_Character_Milou>(Character);
							if(!milou->isBoundToTintin)
								milou->_previousCondorTile = milou->GetCurrentTile();
						}
						
						Character->SetNextTile(targetTile);
						Character->SetCurrentTile(Character->GetNextTile());
						_gameManager->ChangeTile(_barrier, previousTile, Character->GetCurrentTile());
					}
					break;
				}
				default:
					break;
			}

			_barrier->OnBarrierIni(UState_TA_Move::StaticClass());

			
			const float distance =  FMath::Abs(previousTile->_row - condor->GetNextTile()->_row) + FMath::Abs(previousTile->_column - condor->GetNextTile()->_column);
			for (auto Character : condor->_characters)
			{
				if(Character->IsA<ATileActor_Character_Tintin>())
				{
					UGameplayStatics::SpawnSoundAtLocation(condor, condor->S_CondorPickUpTintin, condor->GetActorLocation());
					for (auto peruvien : _gameManager->_peruviens)
					{
						ATile* tintinTile = ATileActor_Character_Tintin::GetInstance()->GetCurrentTile();
						if(peruvien->GetCurrentTile() == tintinTile)
						{
							_gameManager->StartGameOver();
							UGameplayStatics::SpawnSoundAtLocation(peruvien, peruvien->S_PeruvienDetectTintin, peruvien->GetActorLocation());
							return;
						}
						if(peruvien->Detection(tintinTile))
						{
							_gameManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
							peruvien->PeruvienTilePath = _gameManager->GetPath(tintinTile, false);
							peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
							peruvien->_currentPBehaviour = EPeruvienBehaviour::FollowingTintin;
							peruvien->SetWidgetVisible(true);
							peruvien->AddSplinePoint();
						}
					}
				}
				else if(Character->IsA<ATileActor_Character_Milou>())
				{
					UGameplayStatics::SpawnSoundAtLocation(condor, condor->S_CondorPickUpMilou, condor->GetActorLocation());
				}
				else if(Character->IsA<ATileActor_Character_Peruvien>())
				{
					UGameplayStatics::SpawnSoundAtLocation(condor, condor->S_CondorPickUpEnnemy, condor->GetActorLocation());
					ATileActor_Character_Peruvien* peruvien = Cast<ATileActor_Character_Peruvien>(Character);
					ATile* tintinTile = ATileActor_Character_Tintin::GetInstance()->GetCurrentTile();
					if(peruvien->GetCurrentTile() == tintinTile)
					{
						_gameManager->StartGameOver();
						UGameplayStatics::SpawnSoundAtLocation(peruvien, peruvien->S_PeruvienDetectTintin, peruvien->GetActorLocation());
						return;
					}
					if(peruvien->Detection(tintinTile))
					{
						_gameManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
						peruvien->PeruvienTilePath = _gameManager->GetPath(tintinTile, false);
						peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
						peruvien->_currentPBehaviour = EPeruvienBehaviour::FollowingTintin;
						peruvien->SetWidgetVisible(true);
						peruvien->AddSplinePoint();
					}
				}
				
				Cast<UState_TA_Move>(Character->_currentState_TA)->_actorSpeed = condor->_speed / distance;
				Cast<UState_TA_Move>(Character->_currentState_TA)->_speed = condor->_speed / distance;
			}
			Cast<UState_TA_Move>(condor->_currentState_TA)->_actorSpeed = condor->_speed / distance;
			Cast<UState_TA_Move>(condor->_currentState_TA)->_speed = condor->_speed / distance;
			FVector TargetDirection = condor->GetNextTile()->GetActorLocation() - condor->GetActorLocation();
			const FRotator TargetRotation = TargetDirection.Rotation();
			condor->_startRotation = condor->GetActorRotation().Quaternion();
			condor->_endRotation = TargetRotation.Quaternion();
			rotateInterpolationValue = 0;
		}
	}
	if(_barrier->_actors.Num() == 0)
	{
		_gameManager->StateChange(NewObject<UState_CondorGoToNextNest>(UState_CondorGoToNextNest::StaticClass()));
	}
}

void UState_CondorDropCharacters::OnStateTick(float DeltaTime)
{
	// Set condor's orientation
	for(auto condor : _gameManager->_condors)
	{
		FQuat rot =  FQuat::Slerp(condor->_startRotation, condor->_endRotation, rotateInterpolationValue);
		condor->SetActorRotation(rot);
		rotateInterpolationValue +=DeltaTime * condor->_rotateSpeed;
		rotateInterpolationValue =  FMath::Clamp(rotateInterpolationValue, 0, 1);
	}
	
	if(IsValid(_barrier))
	{
		if (_barrier->_isBarriereCompleted)
		{
			for (auto condor : _gameManager->_condors)
			{
				// Update Milou and enemy behaviours
				for (auto character : condor->_characters)
				{
					if(character->IsA<ATileActor_Character_Peruvien>())
					{
						ATileActor_Character_Peruvien* peruvien = Cast<ATileActor_Character_Peruvien>(character);

						_gameManager->SetTilesPeruvienColor(true, peruvien->angle,peruvien->GetCurrentTile());
						_gameManager->MarkStepsOnGrid(character->GetCurrentTile());
						peruvien->PeruvienTilePath = _gameManager->GetPath(peruvien->_startingTile, false);
						peruvien->_currentPBehaviour = EPeruvienBehaviour::Returning;
						peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
					}
					else if(character->IsA<ATileActor_Character_Milou>())
					{
						ATileActor_Character_Milou* milou = Cast<ATileActor_Character_Milou>(character);
						if(!milou->isBoundToTintin)
						{
							_gameManager->MarkStepsOnGrid(character->GetCurrentTile());
							milou->MilouTilePath = _gameManager->GetPath(milou->_previousCondorTile, true);
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