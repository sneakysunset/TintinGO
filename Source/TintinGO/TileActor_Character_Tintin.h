// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor_Character.h"
#include "TileActor_Character_Tintin.generated.h"

UCLASS()
class TINTINGO_API ATileActor_Character_Tintin : public ATileActor_Character
{
	GENERATED_BODY()
	ATileActor_Character_Tintin();
public:
	static ATileActor_Character_Tintin* GetInstance();
	static ATileActor_Character_Tintin* SingletonInstance;
};
