#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlacableBody.generated.h"

UINTERFACE(MinimalAPI)
class UPlacableBody : public UInterface
{
	GENERATED_BODY()
};

class TINTINGO_API IPlacableBody
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void PlaceBody() = 0;
	virtual void TriggerBody() = 0;
};