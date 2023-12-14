// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor.h"
#include "TileActor_Clue.generated.h"

UCLASS()
class TINTINGO_API ATileActor_Clue : public ATileActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32 clueNumber;

	ATileActor_Clue();
	
	UFUNCTION()
	virtual void OnEndTask() override;


	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void Init();

	UPROPERTY()
	float initTimer;

	UPROPERTY()
	bool hasInit;
};
