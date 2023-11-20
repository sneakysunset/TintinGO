// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

class State;

UENUM()
enum class EStateType : uint8
{
	AwaitingInputs = 0b0000,
	PlayerMove = 0b0001,
};
UCLASS()
class TINTINGO_API AGameManager : public AActor
{
	GENERATED_BODY()

public:	
	AGameManager();
	TMap<EStateType, State*> _states;
	EStateType _currentStateType;
	UFUNCTION()
	void StateChange();
	static AGameManager* GetInstance();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	// Called when the game starts or when spawned
	static AGameManager* SingletonInstance;
};
