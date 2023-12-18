// Fill out your copyright notice in the Description page of Project Settings.


#include "State_AwaitingInputs_Milou.h"
#include "MainGameMode.h"
#include "State_DropMilouBoneAnimation.h"
#include "State_MilouRotate.h"
#include "Tile.h"
#include "Kismet/GameplayStatics.h"

void UState_AwaitingInputs_Milou::OnStateEnter()
{
	Super::OnStateEnter();
	_milou->GetCurrentTile()->SpawnMilouBone();
	_gameManager->MarkStepsOnGrid(ATileActor_Character_Milou::GetInstance()->GetCurrentTile());
	_tintin = ATileActor_Character_Tintin::GetInstance();
	_tintin->SetTintinMesh(ETintinState::Throwing);
	UGameplayStatics::SpawnSoundAtLocation(pc, _gameManager->S_buttonClick, pc->PlayerCameraManager->GetCameraLocation());
	for (int i = 0; i < _gameManager->_gridTiles.Num(); i++)
	{
		for (int j = 0; j < _gameManager->_gridTiles[0].Tiles.Num(); j++)
		{
			const bool condition1 = FMathf::Abs(_gameManager->_gridTiles[i].Tiles[j]->_row  - _tintin->GetCurrentTile()->_row) <= 2;
			const bool condition2 = FMathf::Abs(_gameManager->_gridTiles[i].Tiles[j]->_column -_tintin->GetCurrentTile()->_column) <= 2;
			if(condition1 && condition2)
			{
				_gameManager->_gridTiles[i].Tiles[j]->SetTilesInBoneRangeMat(true);
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

		_milou->MilouTilePath = _gameManager->GetPath(_hitTile, false);
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
		if(_gameManager->OnBoneConsumed.IsBound())
			_gameManager->OnBoneConsumed.Execute(_gameManager->_milouBonesNumber, FColor::Emerald);
		int32 randomAudioFileIndex = FMath::RandRange(0, _tintin->S_throwBoneArray.Num() - 1);
		
		UGameplayStatics::SpawnSoundAtLocation(_tintin, _tintin->S_throwBoneArray[randomAudioFileIndex], _tintin->GetActorLocation());
		UGameplayStatics::SpawnSoundAtLocation(_milou, _milou->S_milouStartMoving, _milou->GetActorLocation());

		_gameManager->StateChange(NewObject<UState_DropMilouBoneAnimation>(UState_DropMilouBoneAnimation::StaticClass()));
	}

}

void UState_AwaitingInputs_Milou::ReceiveMiloClickDelegate()
{
	UGameplayStatics::SpawnSoundAtLocation(pc, _gameManager->S_buttonClick, pc->PlayerCameraManager->GetCameraLocation());
	_milou->_milouBoneToDrop->OnDestroyBone();
	_tintin->SetTintinMesh(ETintinState::Running);
	_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
}

void UState_AwaitingInputs_Milou::OnStateExit()
{
	Super::OnStateExit();
	for (int i = 0; i < _gameManager->_gridTiles.Num(); i++)
	{
		for (int j = 0; j < _gameManager->_gridTiles[0].Tiles.Num(); j++)
		{
			const bool condition1 = FMathf::Abs(_gameManager->_gridTiles[i].Tiles[j]->_row  - _tintin->GetCurrentTile()->_row) <= 2;
			const bool condition2 = FMathf::Abs(_gameManager->_gridTiles[i].Tiles[j]->_column -_tintin->GetCurrentTile()->_column) <= 2;
			if(condition1 && condition2)
			{
				_gameManager->_gridTiles[i].Tiles[j]->SetTilesInBoneRangeMat(false);
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

