#pragma once

#include "CoreMinimal.h"
#include "State_TActor.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"

class AMainGameMode;
class ATile;

UENUM(BlueprintType)
enum class EAngle : uint8
{
	Right = 0 UMETA(DisplayName = "Right"),
	Left = 1 UMETA(DisplayName = "Left"),
	Up = 2 UMETA(DisplayName = "Up"),
	Down = 4 UMETA(DisplayName = "Down")
};

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

	UPROPERTY(EditAnywhere)
	float _baseAngleOffset;

	UFUNCTION()
	virtual void SetUpRotation(EAngle newAngle);

	UPROPERTY()
	EAngle angle;
	
	bool _isTaskOver;

	UPROPERTY(EditAnywhere)
	float _speed;
	
protected:
	UPROPERTY()
	ATile* _currentTile;
	virtual void BeginPlay() override;

	UPROPERTY()
	AMainGameMode* _gameManager;
	
};
