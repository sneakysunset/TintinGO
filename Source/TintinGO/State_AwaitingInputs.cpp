#include "State_AwaitingInputs.h"
#include "Math/UnrealMathUtility.h"
#include "GameManager.h"
void State_AwaitingInputs::OnStateEnter()
{
	State::OnStateEnter();
	if (gridManager == nullptr) 
	{
		gridManager = AGridManager::GetInstance();
	}
}

void State_AwaitingInputs::OnStateTick()
{
	State::OnStateTick();
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
	ATile* tintinTile = gridManager->GetTintinTileCoordinates();
	if (FMath::Abs(hitTile->_row - tintinTile->_row) + FMath::Abs(hitTile->_column - tintinTile->_column) == 1 )
	{
		//Set Tintin Target Tile on Tintin or in Game Manager
		_gameManager->StateChange();
	}
}