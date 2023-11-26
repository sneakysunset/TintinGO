// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor.h"
#include "TileActor_MilouBone.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API ATileActor_MilouBone : public ATileActor
{
	GENERATED_BODY()

public:
	virtual void OnEndTask() override;
};
