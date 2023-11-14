// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

class UState;

UCLASS()
class TINTINGO_API AGameManager : public AActor
{
	GENERATED_BODY()

public:	
	AGameManager();
	TArray<UState*> _states;
	int32 _currentStateIndex;
	UFUNCTION()
	void StateChange();
	static AGameManager* GetInstance();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	// Called when the game starts or when spawned
	static AGameManager* SingletonInstance;
};
