#include "State_MilouMove.h"

#include "Barrier.h"
#include "GameManager.h"
#include "State_AwaitingInputs.h"
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
}

void UState_MilouMove::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		if(_milou->MilouTilePath.Num() > 0)
		{
			PeruvienDetectionAllDirection();
			_gameManager->StateChange(NewObject<UState_MilouMove>(StaticClass()));			
		}
		else
		{
			_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
		}
	}
	_barrier->OnTick(DeltaTime);
}

void UState_MilouMove::OnStateExit()
{
	UState::OnStateExit();
}

void UState_MilouMove::PeruvienDetectionAllDirection() const
{
	int32 mX = _milou->GetCurrentTile()->_row;
	int32 mY = _milou->GetCurrentTile()->_column;

	PeruvienDetection(mX + 1, mY, _milou->GetCurrentTile()->_rightLink);
	PeruvienDetection(mX - 1, mY, _milou->GetCurrentTile()->_leftLink);
	PeruvienDetection(mX, mY + 1, _milou->GetCurrentTile()->_upLink);
	PeruvienDetection(mX, mY - 1, _milou->GetCurrentTile()->_downLink);

}

void UState_MilouMove::PeruvienDetection(int32 x, int32 y, bool isLinkActive) const
{
	AGridManager* gridM = AGridManager::GetInstance();

	if(x >= 0 && x < gridM->_gridTiles.Num() && y >= 0 && y < gridM->_gridTiles[x].Tiles.Num() && isLinkActive)
	{
		for (auto tActor : gridM->_gridTiles[x].Tiles[y]->_tileActors)
		{
			if(tActor->IsA(ATileActor_Character_Peruvien::StaticClass()))
			{
				ATileActor_Character_Peruvien* peruvien = Cast<ATileActor_Character_Peruvien>(tActor);
				gridM->MarkStepsOnGrid(peruvien->GetCurrentTile());
				TArray<ATile*> tempList = gridM->GetPath(_milou->GetCurrentTile(), false);
				peruvien->PeruvienTilePath = _milou->MilouTilePath;
				for (int32 i = 0; i < tempList.Num(); i++)
				{
					peruvien->PeruvienTilePath.Add(tempList[i]);
				}
				peruvien->SetNextTile(peruvien->PeruvienTilePath.Last());
				UE_LOG(LogTemp, Warning, TEXT("Peruvien detected milou"));
			}
		}
	}
}
