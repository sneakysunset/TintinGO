// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GlobalGameManager.generated.h"

UCLASS()
class TINTINGO_API UGlobalGameManager : public UGameInstance
{
	GENERATED_BODY()
public:
	UGlobalGameManager();
	
	UPROPERTY()
	TArray<FString> _levelNames;

	UPROPERTY()
	FString _currentLevel;

	UFUNCTION()
	void OnWin();

	UFUNCTION()
	void OnGameOver() const;

	UFUNCTION()
	static void OnLevelLoad();
};
