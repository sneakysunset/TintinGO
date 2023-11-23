#include "State_AwaitingInputs.h"

#include "Math/UnrealMathUtility.h"
#include "GameManager.h"
#include "State_MilouMove.h"
#include "State_PlayerMove.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"



void State_AwaitingInputs::OnStateEnter()
{
	State::OnStateEnter();
	
	gridManager = AGridManager::GetInstance();
	_milou = ATileActor_Character_Milou::GetInstance();
	_tintin = ATileActor_Character_Tintin::GetInstance();
	_gameManager->OnClickD.BindRaw(this, &State_AwaitingInputs::ReceiveLeftMouseClick);
	_gameManager->OnMilouBoneClick.BindRaw(this, &State_AwaitingInputs::ReceiveMiloClickDelegate);


	isTintinInput = true;
	UE_LOG(LogTemp, Warning, TEXT("Awaiting Inputs State Enter"));
}

void State_AwaitingInputs::OnStateTick(float DeltaTime)
{
	State::OnStateTick(DeltaTime);
	ProcessMousePositionInput();
}

void State_AwaitingInputs::OnStateExit()
{
	State::OnStateExit();
	if(_hitTile != nullptr)
	{
		_hitTile->SetHighlighted(false);
		_hitTile = nullptr;
	}
}

void State_AwaitingInputs::ProcessMousePositionInput()
{
	float mouseX;
	float mouseY;
	check (_gameManager)
	APlayerController* pc = UGameplayStatics::GetPlayerController(_gameManager->GetWorld(), 0);
	check(pc)
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
		hitTile = AGridManager::GetInstance()->WorldCoordinatesToTilePosition(HitResult.Location);
	}
	else
	{
		isTileAccessible = false;
		DisableTiles(true, true);
		return;
	}

	if(hitTile == nullptr)
	{
		isTileAccessible = false;
		DisableTiles(true, true);
		return;
	}
	
	if(_hitTile == hitTile)
	{
		return;
	}
	
	if(isTintinInput)
	{
		ProcessPlayerInputs(hitTile);		
	}
	else
	{
		ProcessMiloInputs(hitTile);
	}
}

void State_AwaitingInputs::ProcessPlayerInputs(ATile* hitTile)
{
	ATile* tintinTile = _tintin->_currentTile;

	check(tintinTile);

	if (FMath::Abs(hitTile->_row - tintinTile->_row) + FMath::Abs(hitTile->_column - tintinTile->_column) == 1 && hitTile->_walkable)
	{
		if((hitTile->_row - tintinTile->_row == 1 && !hitTile->_leftLink)
			|| (hitTile->_row - tintinTile->_row == -1 && !hitTile->_rightLink)
			|| (hitTile->_column - tintinTile->_column == 1 && !hitTile->_downLink)
			|| (hitTile->_column - tintinTile->_column == -1 && !hitTile->_upLink)
			)
		if(_hitTile != nullptr) _hitTile->SetHighlighted(false);
		DisableTiles(true, false);
		_hitTile = hitTile;
		_hitTile->SetHighlighted(true);
		isTileAccessible = true;
	}
	else
	{
		if(_hitTile != nullptr && _hitTile != hitTile)
		{
			_hitTile->SetHighlighted(false);
			_hitTile = hitTile;
		}
		isTileAccessible = false;
	}
}

void State_AwaitingInputs::ProcessMiloInputs(ATile* hitTile)
{
	ATile* milouTile = _milou->_currentTile;
	ATile* tintinTile = _tintin->_currentTile;

	check(milouTile);

	if (FMath::Abs(hitTile->_row - tintinTile->_row) <= _gameManager->milouBoneThrowRange && FMath::Abs(hitTile->_column - tintinTile->_column) <= _gameManager->milouBoneThrowRange && hitTile->_walkable)
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
		UE_LOG(LogTemp, Warning, TEXT("%d"), hitTile->_step);
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

void State_AwaitingInputs::ReceiveLeftMouseClick()
{
	if (isTileAccessible)
	{
		if(isTintinInput)
		{
			_tintin->_nextTile = _hitTile;
			_gameManager->StateChange(new State_PlayerMove());
		}
		else
		{
			_gameManager->StateChange(new State_MilouMove());
		}
	}
}

void State_AwaitingInputs::ReceiveMiloClickDelegate()
{
	if(isTintinInput)
	{
		isTintinInput = false;
		gridManager->MarkStepsOnGrid(ATileCharacter_Milou::GetInstance()->_currentTile);
	}
	else
	{
		isTintinInput = true;
	}
}

void State_AwaitingInputs::DisableTiles(bool disablePath, bool disablePlayerTarget)
{
	if(disablePlayerTarget && _hitTile != nullptr)
	{
		_hitTile->SetHighlighted(false);
		_hitTile = nullptr;
	}
	if(disablePath && _milou->MilouTilePath.Num() > 1)
	{
		for (int i = 0; i < _milou->MilouTilePath.Num(); i++)
		{
			_milou->MilouTilePath[i]->SetHighlightedPath(false);
		}
	}
}

