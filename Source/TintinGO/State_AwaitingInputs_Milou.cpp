// Fill out your copyright notice in the Description page of Project Settings.


#include "State_AwaitingInputs_Milou.h"

#include "GameManager.h"
#include "State_MilouMove.h"

void UState_AwaitingInputs_Milou::OnStateEnter()
{
	Super::OnStateEnter();
	gridManager->MarkStepsOnGrid(ATileActor_Character_Milou::GetInstance()->GetCurrentTile());
}

void UState_AwaitingInputs_Milou::ProcessPlayerInputs(ATile* hitTile)
{
	ATile* milouTile = _milou->GetCurrentTile();
	ATile* tintinTile = _tintin->GetCurrentTile();

	check(milouTile);

	if (FMath::Abs(hitTile->_row - tintinTile->_row) <= _gameManager->_milouBoneThrowRange && FMath::Abs(hitTile->_column - tintinTile->_column) <= _gameManager->_milouBoneThrowRange && hitTile->_walkable)
	{
		if(_milou->MilouTilePath.Num() > 1)
		{
			for (int i = 0; i < _milou->MilouTilePath.Num(); i++)
			{
				_milou->MilouTilePath[i]->SetHighlightedPath(false);
			}
		}
		if(_hitTile != nullptr) _hitTile->SetHighlighted(false);
		if(_hitTile != hitTile)
			hitTile->SetHighlighted(true);
		_hitTile = hitTile;
		isTileAccessible = true;

		_milou->MilouTilePath = gridManager->GetPath(hitTile);
		if(_milou->MilouTilePath.Num() > 1)
		{
			for (int i = 1; i < _milou->MilouTilePath.Num(); i++)
			{
				_milou->MilouTilePath[i]->SetHighlightedPath(true);
			}
		}
	}
	else
	{
		if(_hitTile != nullptr && _hitTile != hitTile)
		{
			_hitTile->SetHighlighted(false);
			DisableTiles(true, false);
			_hitTile = hitTile;
		}
		isTileAccessible = false;
	}
}

void UState_AwaitingInputs_Milou::ReceiveLeftMouseClick()
{
	if(isTileAccessible)
	{
		if(_milou->isBoundToTintin)
			_milou->isBoundToTintin = false;
		_gameManager->StateChange(NewObject<UState_MilouMove>(UState_MilouMove::StaticClass()));
	}

}

void UState_AwaitingInputs_Milou::ReceiveMiloClickDelegate()
{
	if(_gameManager->OnBoneConsumed.IsBound())
	{
		_gameManager->OnBoneConsumed.Execute(_gameManager->_milouBonesNumber, FColor::Emerald);
	}
	_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
}


