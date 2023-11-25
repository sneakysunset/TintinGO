// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor_Character.h"
#include "TileActor_Character_Milou.generated.h"


UCLASS()
class TINTINGO_API ATileActor_Character_Milou : public ATileActor_Character
{
	GENERATED_BODY()
	ATileActor_Character_Milou();
public:
	static ATileActor_Character_Milou* GetInstance();
	static ATileActor_Character_Milou* SingletonInstance;
	bool isBoundToTintin;
	TArray<ATile*> MilouTilePath;
};
