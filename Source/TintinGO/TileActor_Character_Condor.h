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
	
	ATileActor_Character_Condor();
public:
	UPROPERTY(EditAnywhere)
	int32 currentNestNb;

	UPROPERTY(EditAnywhere)
	bool isWaitLastRound;

	UPROPERTY(EditAnywhere)
	TArray<ATileActor_Character*> _characters;


	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* _sound_CondorOnAttack;
};
