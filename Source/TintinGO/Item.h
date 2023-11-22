#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlacableBody.h"
#include "Item.generated.h"

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

    void OnEndTask();
    
    bool isTaskOver;

};