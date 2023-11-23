#include "State_TActor.h"
#include "TileActor.h"

State_TActor::State_TActor()
{
}

State_TActor::State_TActor(ATileActor* tileActor)
{
	_tileActor = tileActor;
}
