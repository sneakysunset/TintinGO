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


	ATile* GetNextTile() const { return _nextTile;}
	void SetNextTile(ATile* tile){_nextTile = tile;}
	void ChangeTile(UBarrier* barrier, ATile* previousTile);
	
protected:
	ATile* _nextTile;
};