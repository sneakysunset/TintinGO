// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Barrier.h"
#include "TileActor.h"
#include "TileActor_Character.generated.h"
class ATile;

UENUM(BlueprintType)
enum class EAngle : uint8
{
	Right = 0 UMETA(),
	Left = 1 UMETA(),
	Up = 2 UMETA(),
	Down = 4 UMETA()
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
	
protected:
	UPROPERTY()
	ATile* _nextTile;

	UFUNCTION()
	virtual void OnEndTask() override{}

	virtual void BeginPlay() override;
};
