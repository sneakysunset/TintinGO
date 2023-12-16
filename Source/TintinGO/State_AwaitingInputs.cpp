#include "State_AwaitingInputs.h"

#include "Math/UnrealMathUtility.h"
#include "GameManager.h"
#include "MainGameMode.h"
#include "State_AwaitingInputs_Milou.h"
#include "State_MilouMove.h"
#include "State_PlayerMove.h"
#include "State_PlayerRotate.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"



void UState_AwaitingInputs::OnStateEnter()
{
	UState::OnStateEnter();
	
	isTileAccessible = false;
	_milou = ATileActor_Character_Milou::GetInstance();
	_tintin = ATileActor_Character_Tintin::GetInstance();

	_gameManager->OnClickD.BindDynamic(this,&UState_AwaitingInputs::ReceiveLeftMouseClick);
	_gameManager->OnMilouBoneClick.BindDynamic(this, &UState_AwaitingInputs::ReceiveMiloClickDelegate);

	if(_gameManager != nullptr)
	{
		pc = _gameManager->pc;
	}

	if (IsValid(gridManager))
	{
		for(auto condor : gridManager->_condors)
		{
			if(condor->isWaitLastRound)
			{
				ATile* currentTile = condor->GetCurrentTile();

				switch (currentTile->_nestDirection)
				{
				case ENestDirection::Left :
					for (int i = currentTile->_column - 1; i >= 0; --i)
					{
						gridManager->_gridTiles[currentTile->_row].Tiles[i]->RefreshTileBackgroundRenderer(1);
					}
					break;
				case ENestDirection::Right :
					for (int i = currentTile->_column + 1; i < gridManager->_gridTiles[0].Tiles.Num(); ++i)
					{
						gridManager->_gridTiles[currentTile->_row].Tiles[i]->RefreshTileBackgroundRenderer(1);
					}
					break;
				case ENestDirection::Top :
					for (int i = currentTile->_row + 1; i > gridManager->_gridTiles.Num(); ++i)
					{
						gridManager->_gridTiles[i].Tiles[currentTile->_column]->RefreshTileBackgroundRenderer(1);
					}
					break;
				case ENestDirection::Down :
					for (int i = currentTile->_row - 1; i >= 0; --i)
					{
						gridManager->_gridTiles[i].Tiles[currentTile->_column]->RefreshTileBackgroundRenderer(1);
					}
					break;
				default:
					break;
				}
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Awaiting Inputs State Enter"));
}

void UState_AwaitingInputs::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	ProcessMousePositionInput();
}

void UState_AwaitingInputs::OnStateExit()
{
	_gameManager->OnClickD.Unbind();
	_gameManager->OnMilouBoneClick.Unbind();
	if(_hitTile != nullptr)
	{
		_hitTile->SetHighlighted(false);
		_hitTile = nullptr;
	}
	UState::OnStateExit();
}

void UState_AwaitingInputs::ProcessMousePositionInput()
{
	float mouseX;
	float mouseY;
	if(!IsValid(pc)) return;
	pc->GetMousePosition(mouseX, mouseY);
	
	FVector MouseWorldPosition;
	FVector MouseWorldDirection;
	pc->DeprojectScreenPositionToWorld(mouseX, mouseY, MouseWorldPosition, MouseWorldDirection);

	// Perform ray cast
	FHitResult HitResult;
	FVector Start = MouseWorldPosition;
	FVector End = MouseWorldPosition + MouseWorldDirection * 5000.f; // Adjust the length of the ray as needed
	FCollisionQueryParams CollisionParams;
	ATile* hitTile = nullptr;
	if (_gameManager->GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
	{
		hitTile = _gameManager->WorldCoordinatesToTilePosition(HitResult.Location);
	}
	else
	{
		isTileAccessible = false;
		DisableTiles();
		return;
	}

	if(!IsValid(hitTile))
	{
		isTileAccessible = false;
		DisableTiles();
		_hitTile = nullptr;
		return;
	}

	if(_hitTile != hitTile)
	{
		if(IsValid(_hitTile))
			_hitTile->SetHighlighted(false);
		_hitTile = hitTile;
	}
	else if(_hitTile == hitTile)
	{
		return;
	}
	
	if(!IsValid(_hitTile)) return;
	ProcessPlayerInputs();		
}

void UState_AwaitingInputs::ProcessPlayerInputs()
{
	_tintin = ATileActor_Character_Tintin::GetInstance();
	if(!IsValid(_tintin)) return;
	if(!IsValid(_hitTile)) return;
	
	const ATile* tintinTile = _tintin->GetCurrentTile();

	if(!IsValid(tintinTile)) return;

	if (FMath::Abs(_hitTile->_row - tintinTile->_row) + FMath::Abs(_hitTile->_column - tintinTile->_column) == 1 && _hitTile->_walkable)
	{
		if((_hitTile->_row - tintinTile->_row == 1 && _hitTile->_downLink)
			|| (_hitTile->_row - tintinTile->_row == -1 && _hitTile->_upLink)
			|| (_hitTile->_column - tintinTile->_column == 1 && _hitTile->_leftLink)
			|| (_hitTile->_column - tintinTile->_column == -1 && _hitTile->_rightLink)
			)
		{
			_hitTile->SetHighlighted(true);
			isTileAccessible = true;
		}
		else
		{
			_hitTile->SetHighlighted(false);
			isTileAccessible = false;
			_hitTile = nullptr;
		}
	}
	else
	{
		isTileAccessible = false;
		_hitTile->SetHighlighted(false);
		_hitTile = nullptr;
	}
}


void UState_AwaitingInputs::ReceiveLeftMouseClick()
{
	if (isTileAccessible)
	{
		_milou = ATileActor_Character_Milou::GetInstance();
		
		if(!IsValid(_milou) || !IsValid(_tintin) || !IsValid(_hitTile) && !IsValid(_gameManager))return;
		
		_tintin->SetNextTile(_hitTile);
		
		if(_milou->isBoundToTintin)
		{
			_milou->SetCurrentTile(_tintin->GetCurrentTile());
			_milou->SetNextTile(_tintin->GetNextTile());
		}

		_gameManager->StateChange(NewObject<UState_PlayerRotate>(UState_PlayerRotate::StaticClass()));
	}
}

void UState_AwaitingInputs::ReceiveMiloClickDelegate()
{
	check(_gameManager);
	_gameManager->StateChange(NewObject<UState_AwaitingInputs_Milou>(UState_AwaitingInputs_Milou::StaticClass()));
}

void UState_AwaitingInputs::DisableTiles()
{
	if(!IsValid(_hitTile)) return;
	_hitTile->SetHighlighted(false);
}

