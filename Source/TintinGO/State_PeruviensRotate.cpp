	// Fill out your copyright notice in the Description page of Project Settings.


#include "State_PeruviensRotate.h"

#include "GameManager.h"
#include "GridManager.h"
#include "State_AwaitingInputs.h"
#include "State_CondorChoice.h"
#include "State_TA_Rotate.h"
#include "TileActor_Character_Peruvien.h"

void UState_PeruviensRotate::OnStateEnter()
{
	Super::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("State Enter Peruvien Rotate"));
	AGridManager* gridManager = AGridManager::GetInstance();
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	ATile* tintinTile = ATileActor_Character_Tintin::GetInstance()->GetCurrentTile();
	for (auto peruvien : gridManager->_peruviens)
	{
		if(peruvien->Detection(tintinTile))
		{
			gridManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
			peruvien->PeruvienTilePath = gridManager->GetPath(tintinTile, false);
			peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
			peruvien->_currentPBehaviour = EPeruvienBehaviour::FollowingTintin;
		}
		else if(peruvien->_currentPBehaviour == EPeruvienBehaviour::FollowingTintin)
		{
			peruvien->_currentPBehaviour = EPeruvienBehaviour::SearchingTintin;
			peruvien->_tintinAngle = ATileActor_Character_Tintin::GetInstance()->angle;
		}

		if(peruvien->_currentPBehaviour == EPeruvienBehaviour::SearchingTintin && peruvien->PeruvienTilePath.Num() == 0)
		{
			_barrier->_actors.Add(peruvien);
			continue;
		}
		
		if(peruvien->GetNextTile() == nullptr || peruvien->GetNextTile() == peruvien->GetCurrentTile())
		{
			if(peruvien->_currentPBehaviour == EPeruvienBehaviour::Static && peruvien->angle != peruvien ->_startingAngle)
				_barrier->_actors.Add(peruvien);
			continue;
		}

		_barrier->_actors.Add(peruvien);
	}

	_barrier->OnBarrierIni(UState_TA_Rotate::StaticClass());
}

void UState_PeruviensRotate::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		ATile* tintinTile = ATileActor_Character_Tintin::GetInstance()->GetCurrentTile();
		AGridManager* gridManager = AGridManager::GetInstance();
		for(auto peruvien : gridManager->_peruviens)
		{
			if(peruvien->Detection(tintinTile))
			{
				gridManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
				peruvien->PeruvienTilePath = gridManager->GetPath(tintinTile, false);
				peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
				peruvien->_currentPBehaviour = EPeruvienBehaviour::FollowingTintin;
			}
		}
		_gameManager->StateChange(NewObject<UState_CondorChoice>(UState_CondorChoice::StaticClass()));
	}
	_barrier->OnTick(DeltaTime);
}

void UState_PeruviensRotate::OnStateExit()
{
	Super::OnStateExit();
}
