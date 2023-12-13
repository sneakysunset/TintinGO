#pragma once

#include "CoreMinimal.h"
#include "State_TActor.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"

class ATile;

UCLASS()
class TINTINGO_API ATileActor : public AActor
{
	GENERATED_BODY()

	
public:
	virtual void OnEndTask();
	virtual void TriggerBody();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UState_TActor* _currentState_TA;
	
	void ChangeState(UState_TActor* newState);
	
	virtual ATile* GetCurrentTile() const;
	virtual void SetCurrentTile(ATile* tile);
	bool _isTaskOver;

	UPROPERTY(EditAnywhere)
	float _speed;
	
protected:
	UPROPERTY()
	ATile* _currentTile;
	virtual void BeginPlay() override;

public:	
	
};
