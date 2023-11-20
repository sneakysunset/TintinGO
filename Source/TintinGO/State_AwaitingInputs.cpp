#include "State_AwaitingInputs.h"
#include "Math/UnrealMathUtility.h"
#include "GameManager.h"
#include "TileCharacter_Tintin.h"

void State_AwaitingInputs::OnStateEnter()
{
	State::OnStateEnter();
	if (gridManager == nullptr) 
	{
		gridManager = AGridManager::GetInstance();
	}
}

void State_AwaitingInputs::OnStateTick(float DeltaTime)
{
	State::OnStateTick(DeltaTime);
}

void State_AwaitingInputs::OnStateExit()
{
	//_targetStateType = EStateType::PlayerMove;
	State::OnStateExit();
}


void State_AwaitingInputs::ReceiveLeftMouseClick(FVector mousePosition)
{
	UE_LOG(LogTemp, Warning, TEXT("Click"));
	ATile* hitTile = gridManager->WorldCoordinatesToTilePosition(mousePosition);
	ATile* tintinTile = ATileCharacter_Tintin::GetInstance()->_currentTile;
	if (FMath::Abs(hitTile->_row - tintinTile->_row) + FMath::Abs(hitTile->_column - tintinTile->_column) == 1 )
	{
		//Set Tintin Target Tile on Tintin or in Game Manager
		_gameManager->StateChange(EStateType::PlayerMove);
		_gameManager->_playerTargetTile = hitTile;
	}
}