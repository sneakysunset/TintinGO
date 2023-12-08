// Fill out your copyright notice in the Description page of Project Settings.


#include "State_PeruviensMove.h"

#include "GameManager.h"
#include "GridManager.h"
#include "State_AwaitingInputs.h"
#include "State_TA_Move.h"
#include "TileActor_Character_Peruvien.h"

void UState_PeruviensMove::OnStateEnter()
{
	Super::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("State Enter Peruvien move"));
	AGridManager* gridManager = AGridManager::GetInstance();
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	TArray<ATile*> previousTiles;
	TArray<ATileActor_Character_Peruvien*> peruviens;
	for (auto peruvien : gridManager->_peruviens)
	{
		if(peruvien->GetNextTile() == nullptr || peruvien->GetNextTile() == peruvien->GetCurrentTile())
			continue;
		previousTiles.Add(peruvien->GetCurrentTile());
		peruviens.Add(peruvien);
		peruvien->SetCurrentTile(peruvien->GetNextTile());
	}
	for (int32 i = 0; i < peruviens.Num(); i++)
		gridManager->ChangeTile(_barrier, previousTiles[i], peruviens[i]->GetCurrentTile());
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
}

void UState_PeruviensMove::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		AGridManager* gridManager = AGridManager::GetInstance();
		for (auto peruvien : gridManager->_peruviens)
		{
			if(peruvien->PeruvienTilePath.Num() > 0)
			{
				peruvien->PeruvienTilePath.Pop();
				if(peruvien->PeruvienTilePath.Num() > 0)
				{
					peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
				}
				else if(peruvien->GetCurrentTile() != peruvien->_startingTile)
				{
					gridManager->MarkStepsOnGrid(peruvien->GetCurrentTile());
					peruvien->PeruvienTilePath = gridManager->GetPath(peruvien->_startingTile, false);
					peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
				}
				else
				{
					peruvien->SetNextTile(nullptr);
				}
			}
			
		}
		_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
	}
	_barrier->OnTick(DeltaTime);
}

void UState_PeruviensMove::OnStateExit()
{
	Super::OnStateExit();
}
