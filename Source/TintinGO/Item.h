#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlacableBody.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    Stone = 0b0000 UMETA(DisplayName = "Stone"),
    Wallet = 0b0001 UMETA(DisplayName = "Wallet")
};

UCLASS()
class TINTINGO_API AItem : public AActor, public IPlacableBody
{
    GENERATED_BODY()

public:
    AItem();

protected:
    virtual void BeginPlay() override;

    class UStaticMeshComponent* _staticMeshComponent = nullptr;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void OnTriggered();

    virtual void PlaceBody() override;

    virtual void TriggerBody() override;
};