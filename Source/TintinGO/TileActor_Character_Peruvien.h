// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridManager.h"
#include "TileActor_Character.h"
#include "TileActor_Character_Peruvien.generated.h"

class AGridManager;
/**
 * 
 */
UCLASS()
class TINTINGO_API ATileActor_Character_Peruvien : public ATileActor_Character
{
	GENERATED_BODY()

	ATileActor_Character_Peruvien();

	virtual void BeginPlay() override
	{
		Super::BeginPlay();
		AGridManager::GetInstance()->_peruviens.Add(this);
	}
};