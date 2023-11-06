// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MainGameState.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API AMainGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	AMainGameState();
	~AMainGameState() = default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 _rows;
	UPROPERTY(EDitAnywhere, BlueprintReadWrite)
		int32 _columns;
};
