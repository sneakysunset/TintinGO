// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor_Character.h"
#include "TileActor_Character_Condor.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API ATileActor_Character_Condor : public ATileActor_Character
{
	GENERATED_BODY()
	

public:
	ATileActor_Character_Condor();
	
	virtual void SetUpRotation(EAngle newAngle) override;

	UFUNCTION()
	FRotator GetTargetRotation(EAngle newAngle);

	UPROPERTY(EditAnywhere)
	float _rotateSpeed;

	UPROPERTY()
	FQuat _startRotation;

	UPROPERTY()
	FQuat _endRotation;
	
	UPROPERTY(EditAnywhere)
	int32 currentNestNb;

	UPROPERTY(EditAnywhere)
	bool isWaitLastRound;

	UPROPERTY(EditAnywhere)
	TArray<ATileActor_Character*> _characters;


	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_CondorAttack;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_CondorPickUpEnnemy;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_CondorPickUpMilou;
	
	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_CondorPickUpTintin;
};
