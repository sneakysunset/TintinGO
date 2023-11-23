#pragma once

#include "State_TActor.h"
#include "CoreMinimal.h"

class TINTINGO_API State_TActor_Neutral : public State_TActor
{
public:
	State_TActor_Neutral();
	State_TActor_Neutral(ATileActor* tileActor);
	ATileActor* _tileActor;
};
