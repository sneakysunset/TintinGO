#include "State_AwaitingInputs.h"

#include "ClickInputManager.h"
#include "Math/UnrealMathUtility.h"
#include "GameManager.h"
#include "State_PlayerMove.h"
#include "TileCharacter_Tintin.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"



void State_AwaitingInputs::OnStateEnter()
{
	State::OnStateEnter();
	
	if (gridManager == nullptr) 
	{
		gridManager = AGridManager::GetInstance();
		_gameManager->OnClickD.BindRaw(this, &State_AwaitingInputs::ReceiveLeftMouseClick);
	}
	
		 
	UE_LOG(LogTemp, Warning, TEXT("Awaiting Inputs State Enter"));
}

void State_AwaitingInputs::OnStateTick(float DeltaTime)
{
	State::OnStateTick(DeltaTime);
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
		return;
	}

	if(hitTile == nullptr)
	{
		isTileAccessible = false;
		return;
	}
	
	if(_hitTile == hitTile)
	{
		return;
	}
	
	ATile* tintinTile = ATileCharacter_Tintin::GetInstance()->_currentTile;

	check(tintinTile);

	//UE_LOG(LogTemp, Warning, TEXT("%d , %d"), hitTile->_row, hitTile->_column);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), FMath::Abs(hitTile->_row - tintinTile->_row) + FMath::Abs(hitTile->_column - tintinTile->_column));
	if (FMath::Abs(hitTile->_row - tintinTile->_row) + FMath::Abs(hitTile->_column - tintinTile->_column) == 1 )
	{
		if(_hitTile != nullptr) _hitTile->SetHighlighted(false);
		if(_hitTile != hitTile)
			hitTile->SetHighlighted(true);
		_hitTile = hitTile;
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

void State_AwaitingInputs::OnStateExit()
{
	State::OnStateExit();
	if(_hitTile != nullptr)
	{
		_hitTile->SetHighlighted(false);
		_hitTile = nullptr;
	}
}


void State_AwaitingInputs::ReceiveLeftMouseClick()
{
	if (isTileAccessible)
	{
		_gameManager->_playerTargetTile = _hitTile;
		_gameManager->StateChange(new State_PlayerMove());
	}

}