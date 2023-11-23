// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileCharacter.h"
#include "TileCharacter_Milou.generated.h"

class ATile;

UCLASS()
class TINTINGO_API ATileCharacter_Milou : public ATileCharacter
{
	GENERATED_BODY()

public:
	ATileCharacter_Milou();
	static ATileCharacter_Milou* GetInstance();
	static ATileCharacter_Milou* SingletonInstance;
	bool isBoundToTintin;
	UPROPERTY()
	ATile* _currentTile;
	TArray<ATile*> MilouTilePath;
};
