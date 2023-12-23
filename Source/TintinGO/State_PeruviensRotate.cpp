	// Fill out your copyright notice in the Description page of Project Settings.


#include "State_PeruviensRotate.h"

#include "MainGameMode.h"
#include "State_AwaitingInputs.h"
#include "State_CondorChoice.h"
#include "State_TA_Rotate.h"
#include "TileActor_Character_Peruvien.h"

void UState_PeruviensRotate::OnStateEnter()
{
	Super::OnStateEnter();
	if(_gameManager->DebugStateChange)
	UE_LOG(LogTemp, Warning, TEXT("State Enter Peruvien Rotate"));
	
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	ATile* tintinTile = ATileActor_Character_Tintin::GetInstance()->GetCurrentTile();
	for (auto peruvien : _gameManager->_peruviens)
	{

		
		//DETECTION AVANT ROTATION
		if(peruvien->Detection(tintinTile))
		{
			_gameManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
			peruvien->PeruvienTilePath = _gameManager->GetPath(tintinTile, false);
			peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
			peruvien->_currentPBehaviour = EPeruvienBehaviour::FollowingTintin;
			peruvien->SetWidgetVisible(true);
			peruvien->AddSplinePoint();
		}
		//ADD TINTIN DIRECTION TILE TO PATH IF NO TINTIN DETECTION
		else if(peruvien->_currentPBehaviour == EPeruvienBehaviour::FollowingTintin)
		{
			peruvien->_currentPBehaviour = EPeruvienBehaviour::SearchingTintin;
			const ATile* lastTile = peruvien->PeruvienTilePath[0];
			const EAngle tintinAngle = ATileActor_Character_Tintin::GetInstance()->angle;
			peruvien->PeruvienTilePath.Insert(_gameManager->GetForwardTile(lastTile, tintinAngle), 0);
			peruvien->AddSplinePoint();
		}

		/*if(peruvien->_currentPBehaviour == EPeruvienBehaviour::SearchingTintin && peruvien->PeruvienTilePath.Num() == 0)
		{
			_barrier->_actors.Add(peruvien);
			continue;
		}*/

		//RESET ANGLE ON STARTING TILE
		if(peruvien->GetNextTile() == nullptr || peruvien->GetNextTile() == peruvien->GetCurrentTile())
		{
			if(peruvien->_currentPBehaviour == EPeruvienBehaviour::Static && peruvien->angle != peruvien ->_startingAngle)
			{
				_barrier->_actors.Add(peruvien);
			}
			continue;
		}
		_gameManager->SetTilesPeruvienColor(false, peruvien->angle, peruvien->GetCurrentTile());

		_barrier->_actors.Add(peruvien);
	}

	if(_barrier->_actors.Num() == 0)
	{
		_gameManager->StateChange(NewObject<UState_CondorChoice>(UState_CondorChoice::StaticClass()));
	}
	_barrier->OnBarrierIni(UState_TA_Rotate::StaticClass());
}

void UState_PeruviensRotate::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		ATile* tintinTile = ATileActor_Character_Tintin::GetInstance()->GetCurrentTile();
		for(auto peruvien : _gameManager->_peruviens)
		{
			//DETECTION AFTER ROTATE
			_gameManager->SetTilesPeruvienColor(true, peruvien->angle, peruvien->GetCurrentTile());
			if(peruvien->Detection(tintinTile))
			{
				_gameManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
				peruvien->PeruvienTilePath = _gameManager->GetPath(tintinTile, false);
				peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
				peruvien->_currentPBehaviour = EPeruvienBehaviour::FollowingTintin;
				peruvien->SetWidgetVisible(true);
				peruvien->AddSplinePoint();
			}
			else if(peruvien->PeruvienTilePath.Num() > 0)
			{
				peruvien->AddSplinePoint();
			}
		}
		_gameManager->StateChange(NewObject<UState_CondorChoice>(UState_CondorChoice::StaticClass()));
	}
	_barrier->OnTick(DeltaTime);
}

void UState_PeruviensRotate::OnStateExit()
{
	for(auto peruvien : _gameManager->_peruviens)
	{
		if(peruvien->_currentPBehaviour == EPeruvienBehaviour::FollowingTintin || peruvien->_currentPBehaviour == EPeruvienBehaviour::SearchingTintin)
		{
			if(!_gameManager->_pursuitPeruviens.Contains(peruvien))
			{
				_gameManager->_pursuitPeruviens.Add(peruvien);
				_gameManager->ChangeMusic();
			}
		}
		else
		{
			if(_gameManager->_pursuitPeruviens.Contains(peruvien))
			{
				_gameManager->_pursuitPeruviens.Remove(peruvien);
				_gameManager->ChangeMusic();
			}
		}
	}
	Super::OnStateExit();
}
