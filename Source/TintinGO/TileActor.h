#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "State_TActor.h"
#include "TileActor.generated.h"

UCLASS()
class TINTINGO_API ATileActor : public AActor
{
	GENERATED_BODY()
	
public:
	ATileActor();
	virtual void OnEndTask();
	virtual void TriggerBody();

	State_TActor* _currentState_TA;
	
	bool _isTaskOver;
	class UStaticMeshComponent* _staticMeshComponent = nullptr;

	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
