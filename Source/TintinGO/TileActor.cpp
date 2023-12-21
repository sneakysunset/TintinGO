#include "TileActor.h"

#include "MainGameMode.h"
#include "State_TA_Neutral.h"
#include "State_TActor.h"
#include "Tile.h"



void ATileActor::OnEndTask()
{
}

void ATileActor::TriggerBody()
{
	_isTaskOver = true;
}

void ATileActor::ChangeState(UState_TActor* newState)
{
	_currentState_TA->OnStateExit();
	_currentState_TA = newState;
	_currentState_TA->_gameManager = _gameManager;
	newState->SetTileActor(this);
	_currentState_TA->OnStateEnter();
}

ATile* ATileActor::GetCurrentTile() const
{
	return _currentTile;
}

void ATileActor::SetCurrentTile(ATile* tile)
{
	if(IsValid(_currentTile) && _currentTile->_tileActors.Contains(this))
	{
		_currentTile->_tileActors.Remove(this);
	}
	_currentTile = tile;
		
	if(IsValid(tile) && !tile->_tileActors.Contains(this))
	{
		tile->_tileActors.Add(this);
	}
}

void ATileActor::BeginPlay()
{
	Super::BeginPlay();
	_gameManager = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	_currentState_TA = NewObject<UState_TA_Neutral>(UState_TA_Neutral::StaticClass());
}

void ATileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_currentState_TA->OnStateTick(DeltaTime);
}

void ATileActor::SetUpRotation(EAngle newAngle)
{
	angle = newAngle;
	float angleV = 0;
	switch(angle)
	{
	    case EAngle::Right: break;
	    case EAngle::Up: angleV = 90; break;
	    case EAngle::Left: angleV = 180; break;
	    case EAngle::Down: angleV = 270; break;
	}
	SetActorRotation(FQuat::MakeFromEuler(FVector::UpVector * (angleV + _baseAngleOffset)).Rotator());
}

