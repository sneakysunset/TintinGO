// Fill out your copyright notice in the Description page of Project Settings.


#include "State_PeruviensMove.h"

#include "GameManager.h"
#include "GlobalGameManager.h"
#include "GridManager.h"
#include "MainGameMode.h"
#include "State_AwaitingInputs.h"
#include "State_PeruviensRotate.h"
#include "State_TA_Move.h"
#include "TileActor_Character_Peruvien.h"
#include "Kismet/GameplayStatics.h"

void UState_PeruviensMove::OnStateEnter()
{
	Super::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("State Enter Peruvien move"));
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	TArray<ATile*> previousTiles;
	TArray<ATileActor_Character_Peruvien*> peruviens;
	ATile* tintinTile = ATileActor_Character_Tintin::GetInstance()->GetCurrentTile();
	for (auto peruvien : _gameManager->_peruviens)
	{
		if(peruvien->GetCurrentTile() == ATileActor_Character_Tintin::GetInstance()->GetCurrentTile())
		{
			_gameManager->StartGameOver();
			UGameplayStatics::SpawnSoundAtLocation(peruvien, peruvien->S_PeruvienDetectTintin, peruvien->GetActorLocation());
			//Cast<UGlobalGameManager>(UGameplayStatics::GetGameInstance(GetWorld()))->OnGameOver();
			return;
		}
		if(peruvien->Detection(tintinTile))
		{
			_gameManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
			peruvien->PeruvienTilePath.Empty();
			peruvien->PeruvienTilePath = _gameManager->GetPath(tintinTile, false);
			if(FMath::Abs(peruvien->GetCurrentTile()->_row + peruvien->GetCurrentTile()->_column - tintinTile->_row - tintinTile->_column) == 1)
			{
				peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
			}
			peruvien->_currentPBehaviour = EPeruvienBehaviour::FollowingTintin;
		}
		if(peruvien->GetNextTile() == nullptr || peruvien->GetNextTile() == peruvien->GetCurrentTile())
			continue;
		previousTiles.Add(peruvien->GetCurrentTile());
		peruviens.Add(peruvien);
		peruvien->SetCurrentTile(peruvien->GetNextTile());
	}
	for (int32 i = 0; i < peruviens.Num(); i++)
		_gameManager->ChangeTile(_barrier, previousTiles[i], peruviens[i]->GetCurrentTile());
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
	
	for (const auto peruvien : peruviens)
	{
		Cast<UState_TA_Move>(peruvien->_currentState_TA)->_speed = peruvien->_speed;
		Cast<UState_TA_Move>(peruvien->_currentState_TA)->_speed = peruvien->_speed;
		const int32 randomAudioFileIndex = FMath::RandRange(0, _gameManager->S_MoveSoundsArray.Num() - 1);
		if(peruvien->GetCurrentTile() == ATileActor_Character_Tintin::GetInstance()->GetCurrentTile())
		{
			UGameplayStatics::SpawnSoundAtLocation(peruvien, peruvien->S_PeruvienDetectTintin, peruvien->GetActorLocation());
		}
		UGameplayStatics::SpawnSoundAtLocation(peruvien, _gameManager->S_MoveSoundsArray[randomAudioFileIndex], peruvien->GetActorLocation());
		
	}
}

void UState_PeruviensMove::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		const auto tintin = ATileActor_Character_Tintin::GetInstance();
		
		for (auto peruvien : _gameManager->_peruviens)
		{
			if(peruvien->GetCurrentTile() == tintin->GetCurrentTile())
			{
				_gameManager->StartGameOver();
				//Cast<UGlobalGameManager>(UGameplayStatics::GetGameInstance(GetWorld()))->OnGameOver();
				return;
			}
			
			if(peruvien->PeruvienTilePath.Num() > 0)
			{
				peruvien->PeruvienTilePath.Pop();
				if(peruvien->PeruvienTilePath.Num() > 0)
				{
					peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
				}
				else if(peruvien->_currentPBehaviour == EPeruvienBehaviour::FollowingTintin || peruvien->_currentPBehaviour == EPeruvienBehaviour::SearchingTintin)
				{
					peruvien->SetNextTile(nullptr);
					peruvien->SetWidgetVisible(false);
				}
				else if(peruvien->GetCurrentTile() != peruvien->_startingTile)
				{
					if(peruvien->_currentPBehaviour == EPeruvienBehaviour::FollowingMilou)
					{
						UGameplayStatics::SpawnSoundAtLocation(peruvien, peruvien->S_ReachMilou, peruvien->GetActorLocation());
					}
					_gameManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
					peruvien->PeruvienTilePath = _gameManager->GetPath(peruvien->_startingTile, false);
					peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
					peruvien->_currentPBehaviour = EPeruvienBehaviour::Returning;
					peruvien->SetWidgetVisible(false);
				}
				else
				{
					peruvien->SetNextTile(nullptr);
					peruvien->_currentPBehaviour = EPeruvienBehaviour::Static;
					peruvien->SetWidgetVisible(false);
				}
			}
			else
			{
				if(peruvien->GetCurrentTile() != peruvien->_startingTile)
				{
					_gameManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
					peruvien->PeruvienTilePath = _gameManager->GetPath(peruvien->_startingTile, false);
					peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
					peruvien->_currentPBehaviour = EPeruvienBehaviour::Returning;
				}
				else peruvien->_currentPBehaviour = EPeruvienBehaviour::Static;
				peruvien->SetWidgetVisible(false);
			}
			
		}
		_gameManager->StateChange(NewObject<UState_PeruviensRotate>(UState_PeruviensRotate::StaticClass()));
	}
	_barrier->OnTick(DeltaTime);
}

void UState_PeruviensMove::OnStateExit()
{
	Super::OnStateExit();
}
