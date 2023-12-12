// Fill out your copyright notice in the Description page of Project Settings.


#include "State_AwaitingInputs_Milou.h"

#include "GameManager.h"
#include "State_MilouRotate.h"

void UState_AwaitingInputs_Milou::OnStateEnter()
{
	Super::OnStateEnter();
	gridManager->MarkStepsOnGrid(ATileActor_Character_Milou::GetInstance()->GetCurrentTile());
	_tintin = ATileActor_Character_Tintin::GetInstance();
	
	for (int i = 0; i < gridManager->_gridTiles.Num(); i++)
	{
		for (int j = 0; j < gridManager->_gridTiles[0].Tiles.Num(); j++)
		{
			const bool condition1 = FMathf::Abs(gridManager->_gridTiles[i].Tiles[j]->_row  - _tintin->GetCurrentTile()->_row) <= 2;
			const bool condition2 = FMathf::Abs(gridManager->_gridTiles[i].Tiles[j]->_column -_tintin->GetCurrentTile()->_column) <= 2;
			if(condition1 && condition2)
			{
				gridManager->_gridTiles[i].Tiles[j]->SetTilesInBoneRangeMat(true);
			}
		}
	}
}

void UState_AwaitingInputs_Milou::ProcessPlayerInputs()
{
	const ATile* milouTile = _milou->GetCurrentTile();
	const ATile* tintinTile = _tintin->GetCurrentTile();

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
		DisableTiles();
		isTileAccessible = false;
	}
}

void UState_AwaitingInputs_Milou::ReceiveLeftMouseClick()
{
	if(isTileAccessible)
	{
		if(_milou->isBoundToTintin)
			_milou->isBoundToTintin = false;
		_milou->SetNextTile(_milou->MilouTilePath.Last());
		_gameManager->_milouBonesNumber--;
		_gameManager->OnBoneConsumed.Execute(_gameManager->_milouBonesNumber, FColor::Emerald);
		_gameManager->StateChange(NewObject<UState_MilouRotate>(UState_MilouRotate::StaticClass()));
	}

}

void UState_AwaitingInputs_Milou::ReceiveMiloClickDelegate()
{
	_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
}

void UState_AwaitingInputs_Milou::OnStateExit()
{
	Super::OnStateExit();
	for (int i = 0; i < gridManager->_gridTiles.Num(); i++)
	{
		for (int j = 0; j < gridManager->_gridTiles[0].Tiles.Num(); j++)
		{
			const bool condition1 = FMathf::Abs(gridManager->_gridTiles[i].Tiles[j]->_row  - _tintin->GetCurrentTile()->_row) <= 2;
			const bool condition2 = FMathf::Abs(gridManager->_gridTiles[i].Tiles[j]->_column -_tintin->GetCurrentTile()->_column) <= 2;
			if(condition1 && condition2)
			{
				gridManager->_gridTiles[i].Tiles[j]->SetTilesInBoneRangeMat(false);
			}
		}
	}
	if(_milou->MilouTilePath.Num() > 1)
	{
		for (int i = 0; i < _milou->MilouTilePath.Num(); i++)
		{
			if(!IsValid(_milou->MilouTilePath[i]))continue;
			if(IsValid(_milou->MilouTilePath[i]))
			{
				_milou->MilouTilePath[i]->SetHighlightedPath(false);
			}
		}
	}
}

void UState_AwaitingInputs_Milou::DisableTiles()
{
	if(!IsValid(_milou)) return;
	if(_milou->MilouTilePath.Num() > 1)
	{
		for (int i = 0; i < _milou->MilouTilePath.Num(); i++)
		{
			if(!IsValid(_milou->MilouTilePath[i]))continue;
			if(IsValid(_milou->MilouTilePath[i]))
			{
				_milou->MilouTilePath[i]->SetHighlightedPath(false);
			}
		}
		_milou->MilouTilePath.Empty();
	}
}

