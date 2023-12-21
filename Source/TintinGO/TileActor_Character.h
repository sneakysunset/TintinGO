// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "TileActor.h"
#include "TileActor_Character.generated.h"
class ATile;



UCLASS()
class TINTINGO_API ATileActor_Character : public ATileActor
{
	GENERATED_BODY()

public:
	UFUNCTION()
	ATile* GetNextTile() const { return _nextTile;}
	
	UFUNCTION()
	void SetNextTile(ATile* tile){_nextTile = tile;}

	UPROPERTY(EditAnywhere)
	float _rotationSpeed;
	

	
protected:
	UPROPERTY(EditAnywhere)
	ATile* _nextTile;

	UFUNCTION()
	virtual void OnEndTask() override;

	virtual void BeginPlay() override;
};
