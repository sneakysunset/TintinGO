// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor.h"
#include "TileActor_MilouSign.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API ATileActor_MilouSign : public ATileActor
{
	GENERATED_BODY()

	ATileActor_MilouSign();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void MilouSignAnimation(float DeltaSeconds);
	
	UPROPERTY()
	UStaticMeshComponent* _staticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	float _heightToGoUp;

	UPROPERTY(EditDefaultsOnly)
	float _animationSpeed;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _animCurve;
	
	UPROPERTY()
	float _startHeight;

	UPROPERTY()
	float _endHeight;

public:
	UPROPERTY()
	float _interpolateValue;
};
