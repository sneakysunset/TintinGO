// Fill out your copyright notice in the Description page of Project Settings.


#include "State_AwaitingInputs_Milou.h"

#include "GameManager.h"
#include "State_MilouMove.h"

void UState_AwaitingInputs_Milou::OnStateEnter()
{
	Super::OnStateEnter();
	gridManager->MarkStepsOnGrid(ATileActor_Character_Milou::GetInstance()->GetCurrentTile());
}

void UState_AwaitingInputs_Milou::ProcessPlayerInputs()
{
	ATile* milouTile = _milou->GetCurrentTile();
	ATile* tintinTile = _tintin->GetCurrentTile();

	check(milouTile);
	check(tintinTile);
	check(_gameManager);
	if (FMath::Abs(_hitTile->_row - tintinTile->_row) <= _gameManager->_milouBoneThrowRange && FMath::Abs(_hitTile->_column - tintinTile->_column) <= _gameManager->_milouBoneThrowRange && _hitTile->_walkable)
	{
		if(_milou->MilouTilePath.Num() > 1)
		{
			for (int i = 0; i < _milou->MilouTilePath.Num(); i++)
			{
				_milou->MilouTilePath[i]->SetHighlightedPath(false);
			}
		}
		_hitTile->SetHighlighted(true);
		isTileAccessible = true;

		_milou->MilouTilePath = gridManager->GetPath(_hitTile, true);
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
		check(_hitTile);
		_hitTile->SetHighlighted(false);
		DisableTiles(true, false);
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
		_gameManager->_milouBonesNumber--;
		_gameManager->OnBoneConsumed.Execute(_gameManager->_milouBonesNumber, FColor::Emerald);
	}

}

void UState_AwaitingInputs_Milou::ReceiveMiloClickDelegate()
{
	_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
}


