#include "TileActor_Character_Peruvien.h"

#include "Tile.h"


ATileActor_Character_Peruvien::ATileActor_Character_Peruvien(): _startingTile(nullptr), _startingAngle(),
                                                                _currentPBehaviour()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool ATileActor_Character_Peruvien::Detection(ATile* detectTile) const
{
	int32 distance;
	switch(angle)
	{
		case EAngle::Right:
			distance =detectTile->_column - GetCurrentTile()->_column;
			if(distance >= 0 && distance <= 2 && detectTile->_row == GetCurrentTile()->_row) return true;
		return false;
		case EAngle::Left:
			distance = detectTile->_column - GetCurrentTile()->_column;
			if(distance <= 0 && distance >= -2 && detectTile->_row == GetCurrentTile()->_row) return true;
		return false;
		case EAngle::Up:
			distance = detectTile->_row - GetCurrentTile()->_row;
			if(distance >= 0 && distance <= 2 && detectTile->_column == GetCurrentTile()->_column) return true;
		return false;
		case EAngle::Down:
			distance = detectTile->_row - GetCurrentTile()->_row;
			if(distance <= 0 && distance >= -2 && detectTile->_column == GetCurrentTile()->_column) return true;
			return false;
		default:
			return false;
	}
}

void ATileActor_Character_Peruvien::BeginPlay()
{
	Super::BeginPlay();
	_currentPBehaviour = EPeruvienBehaviour::Static;
}
