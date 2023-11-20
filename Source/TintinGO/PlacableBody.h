#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlacableBody.generated.h"


UENUM(BlueprintType)
enum class EPlacableBodyType : uint8
{
	Tintin = 0 UMETA(DisplayName = "Tintin (Not implemented)"),
	Enemy = 1 UMETA(DisplayName = "Enemy"),
	Stone = 2 UMETA(DisplayName = "Stone"),
	Wallet = 4 UMETA(DisplayName = "Wallet")
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