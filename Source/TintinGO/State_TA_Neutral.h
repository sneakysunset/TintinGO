#pragma once

#include "State_TActor.h"
#include "CoreMinimal.h"
#include "State_TA_Neutral.generated.h"

UCLASS()
class TINTINGO_API UState_TA_Neutral : public UState_TActor
{
	GENERATED_BODY()
public:

	virtual void OnStateEnter() override;
	//virtual void OnStateTick(float DeltaTime) override;
	//virtual void OnStateComplete() override;
};
