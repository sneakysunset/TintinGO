// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor.h"
#include "TileActor_Character.generated.h"

UCLASS()
class TINTINGO_API ATileActor_Character : public ATileActor
{
	GENERATED_BODY()

public:
	ATile* _currentTile;
	ATile* _nextTile;
};
