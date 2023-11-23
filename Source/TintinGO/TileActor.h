#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "TileActor.generated.h"

UCLASS()
class TINTINGO_API ATileActor : public AActor
{
	GENERATED_BODY()
	
public:
	ATileActor();
	virtual void OnEndTask();
	virtual void TriggerBody();

	bool _isTaskOver;
	class UStaticMeshComponent* _staticMeshComponent = nullptr;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
