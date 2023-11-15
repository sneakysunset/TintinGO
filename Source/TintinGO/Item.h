#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class TINTINGO_API AItem : public AActor
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
};