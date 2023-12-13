// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "TileActor.h"
#include "Barrier.h"
#include "TileActor_Character.generated.h"
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
class TINTINGO_API ATileActor_Character : public ATileActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	ATile* GetNextTile() const { return _nextTile;}
	
	UFUNCTION()
	void SetNextTile(ATile* tile){_nextTile = tile;}

	UPROPERTY()
	EAngle angle;

	UPROPERTY(EditAnywhere)
	float _rotationSpeed;
	
	UPROPERTY(EditAnywhere)
	float _baseAngleOffset;

	UFUNCTION()
	void SetUpRotation(EAngle newAngle);
	
protected:
	UPROPERTY(EditAnywhere)
	ATile* _nextTile;

	UFUNCTION()
	virtual void OnEndTask() override{}

	virtual void BeginPlay() override;
};
