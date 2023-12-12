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
	ATile* nest1Tile;
	
	UPROPERTY(EditAnywhere)
	ATile* endNest1Tile;
	
	UPROPERTY(EditAnywhere)
	ATile* nest2Tile;
	
	UPROPERTY(EditAnywhere)
	ATile* endNest2Tile;

	bool isWaitLastRound;

protected:
	virtual void BeginPlay() override;
};
