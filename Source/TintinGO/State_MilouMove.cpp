#include "State_MilouMove.h"

#include "Barrier.h"
#include "GameManager.h"
#include "State_AwaitingInputs.h"
#include "State_MilouRotate.h"
#include "State_TA_Move.h"
#include "TileActor_Character_Peruvien.h"

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
	previousMilouTile->SetHighlightedPath(false);
	
	AGridManager::GetInstance()->ChangeTile(_barrier, previousMilouTile, _milou->GetCurrentTile());
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
	Cast<UState_TA_Move>(_milou->_currentState_TA)->_actorSpeed = _milou->_boneSpeed;
	Cast<UState_TA_Move>(_milou->_currentState_TA)->_speed = _milou->_boneSpeed;
}

void UState_MilouMove::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		AGridManager* gridManager = AGridManager::GetInstance();

		if(_milou->MilouTilePath.Num() > 0)
		{
			//PeruvienDetectionAllDirection();
			for (const auto peruvien : gridManager->_peruviens)
			{
				if(peruvien->Detection(_milou->GetCurrentTile()))
				{
					gridManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
					TArray<ATile*> tempList = gridManager->GetPath(_milou->GetCurrentTile(), false);
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
			for (const auto peruvien : gridManager->_peruviens)
			{
				if(peruvien->Detection(_milou->GetCurrentTile()))
				{
					gridManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
					TArray<ATile*> tempList = gridManager->GetPath(_milou->GetCurrentTile(), false);
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
			_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
		}
	}
	_barrier->OnTick(DeltaTime);
}

void UState_MilouMove::OnStateExit()
{
	if (_milou->GetCurrentTile()->milouBoneToDrop)
	{
		_milou->GetCurrentTile()->milouBoneToDrop->OnDestroyBone();
	}
	
	UState::OnStateExit();
}