#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlacableBody.generated.h"


UENUM(BlueprintType)
enum class EPlacableBodyType : uint8
{
	Enemy = 0 UMETA(DisplayName = "Enemy"),
	MilouBone = 1 UMETA(DisplayName = "MilouBone"),
	HaddockBottle = 2 UMETA(DisplayName = "HaddockBottle")
};

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