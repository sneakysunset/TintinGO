#include "TileActor_Character.h"
#include "Barrier.h"
#include "State_TActor.h"
#include "State_TA_Move.h"
#include "Tile.h"

void ATileActor_Character::BeginPlay()
{
	Super::BeginPlay();
	angle = EAngle::Right;
}
