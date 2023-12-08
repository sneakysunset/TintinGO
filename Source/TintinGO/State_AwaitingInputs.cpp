#include "State_AwaitingInputs.h"

#include "Math/UnrealMathUtility.h"
#include "GameManager.h"
#include "State_AwaitingInputs_Milou.h"
#include "State_MilouMove.h"
#include "State_PlayerMove.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"



void UState_AwaitingInputs::OnStateEnter()
{
	UState::OnStateEnter();
	
	gridManager = AGridManager::GetInstance();
	_milou = ATileActor_Character_Milou::GetInstance();
	_tintin = ATileActor_Character_Tintin::GetInstance();

	_gameManager->OnClickD.BindDynamic(this,&UState_AwaitingInputs::ReceiveLeftMouseClick);
	_gameManager->OnMilouBoneClick.BindDynamic(this, &UState_AwaitingInputs::ReceiveMiloClickDelegate);

	pc = UGameplayStatics::GetPlayerController(_gameManager->GetWorld(), 0);

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
	
	pc->GetMousePosition(mouseX, mouseY);
	if(!IsValid(pc)) return;
	
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
		DisableTiles(false, true);
		return;
	}

	if(!IsValid(hitTile))
	{
		isTileAccessible = false;
		DisableTiles(false, true);
		return;
	}

	if(_hitTile == nullptr || _hitTile != hitTile)
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
	
	const ATile* tintinTile = _tintin->GetCurrentTile();

	if(!IsValid(tintinTile)) return;
	
	if (FMath::Abs(_hitTile->_row - tintinTile->_row) + FMath::Abs(_hitTile->_column - tintinTile->_column) == 1 && _hitTile->_walkable)
	{
		if((_hitTile->_row - tintinTile->_row == 1 && _hitTile->_leftLink)
			|| (_hitTile->_row - tintinTile->_row == -1 && _hitTile->_rightLink)
			|| (_hitTile->_column - tintinTile->_column == 1 && _hitTile->_downLink)
			|| (_hitTile->_column - tintinTile->_column == -1 && _hitTile->_upLink)
			)
		{
			_hitTile->SetHighlighted(true);
			isTileAccessible = true;
		}
		else
		{
			_hitTile->SetHighlighted(false);
			isTileAccessible = false;
		}
	}
	else
	{
		_hitTile->SetHighlighted(false);
		isTileAccessible = false;
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
		_gameManager->StateChange(NewObject<UState_PlayerMove>(UState_PlayerMove::StaticClass()));
	}
}

void UState_AwaitingInputs::ReceiveMiloClickDelegate()
{
	check(_gameManager);
	_gameManager->StateChange(NewObject<UState_AwaitingInputs_Milou>(UState_AwaitingInputs_Milou::StaticClass()));
}

void UState_AwaitingInputs::DisableTiles(bool disablePath, bool disablePlayerTarget)
{
	if(!IsValid(_hitTile)) return;
	if(disablePlayerTarget && _hitTile != nullptr)
	{
		_hitTile->SetHighlighted(false);
		//_hitTile = nullptr;
	}
	if(!IsValid(_milou)) return;
	if(disablePath && IsValid(_milou) && _milou->MilouTilePath.Num() > 1)
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

