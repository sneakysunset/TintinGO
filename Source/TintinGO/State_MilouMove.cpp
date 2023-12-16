#include "State_MilouMove.h"

#include "Barrier.h"
#include "GameManager.h"
#include "MainGameMode.h"
#include "State_AwaitingInputs.h"
#include "State_MilouRotate.h"
#include "State_TA_Move.h"
#include "TileActor_Character_Peruvien.h"
#include "Kismet/GameplayStatics.h"

void UState_MilouMove::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Milou Move State Enter"));
	
	_milou = ATileActor_Character_Milou::GetInstance();

	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	
	ATile* previousMilouTile =_milou->GetCurrentTile();

	previousMilouTile->_tileActors.Remove(_milou);
	_milou->SetCurrentTile(_milou->MilouTilePath.Last());
	_milou->MilouTilePath.Pop(true);
	previousMilouTile->SetHighlighted(false);
	
	_gameManager->ChangeTile(_barrier, previousMilouTile, _milou->GetCurrentTile());
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
	Cast<UState_TA_Move>(_milou->_currentState_TA)->_actorSpeed = _milou->_boneSpeed;
	Cast<UState_TA_Move>(_milou->_currentState_TA)->_speed = _milou->_boneSpeed;
	
	const int32 milourandomAudioFileIndex = FMath::RandRange(0, _gameManager->S_MoveSoundsArray.Num() - 1);
		
	UGameplayStatics::SpawnSoundAtLocation(_milou, _gameManager->S_MoveSoundsArray[milourandomAudioFileIndex], _milou->GetActorLocation());
}

void UState_MilouMove::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		if(_milou->MilouTilePath.Num() > 0)
		{
			//PeruvienDetectionAllDirection();
			for (const auto peruvien : _gameManager->_peruviens)
			{
				if(peruvien->Detection(_milou->GetCurrentTile()))
				{
					_gameManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
					TArray<ATile*> tempList = _gameManager->GetPath(_milou->GetCurrentTile(), false);
					peruvien->PeruvienTilePath = _milou->MilouTilePath;
					for (int32 i = 0; i < tempList.Num(); i++)
					{
						peruvien->PeruvienTilePath.Add(tempList[i]);
					}
					peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
					peruvien->_currentPBehaviour = EPeruvienBehaviour::FollowingMilou;
					peruvien->SetWidgetVisible(true);
					peruvien->SetSplinePoints();
				}
			}
			_gameManager->StateChange(NewObject<UState_MilouRotate>(UState_MilouRotate::StaticClass()));			
		}
		else
		{
			//PeruvienDetectionAllDirection();
			for (const auto peruvien : _gameManager->_peruviens)
			{
				if(peruvien->Detection(_milou->GetCurrentTile()))
				{
					if(_milou->MilouTilePath.Num() != 0)
					{
						peruvien->PeruvienTilePath = _milou->MilouTilePath;
						peruvien->PeruvienTilePath.Pop();
						peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
						peruvien->_currentPBehaviour = EPeruvienBehaviour::FollowingMilou;
						peruvien->SetWidgetVisible(true);
					}
					else if(peruvien->GetCurrentTile() != _milou->GetCurrentTile())
					{
						_gameManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
						peruvien->PeruvienTilePath = _gameManager->GetPath(_milou->GetCurrentTile(), false);
						peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
						peruvien->_currentPBehaviour = EPeruvienBehaviour::FollowingMilou;
						peruvien->SetWidgetVisible(true);
					}
					else if(peruvien->_currentPBehaviour == EPeruvienBehaviour::FollowingMilou)
					{
						peruvien->PeruvienTilePath.Empty();
						peruvien->SetNextTile(nullptr);
						peruvien->_currentPBehaviour = EPeruvienBehaviour::Returning;
					}
				}
				
			}
			_milou->GetCurrentTile()->SetHighlighted(false);
			_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
		}
	}
	_barrier->OnTick(DeltaTime);
}

void UState_MilouMove::OnStateExit()
{
	UState::OnStateExit();
}