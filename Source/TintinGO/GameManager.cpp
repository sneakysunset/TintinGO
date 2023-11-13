// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "State_AwaitingInputs.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_states.Add(new State_AwaitingInputs());
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_states[_currentStateIndex]->OnStateTick();
}

void AGameManager::StateChange()
{
	_states[_currentStateIndex]->OnStateExit(&_currentStateIndex);
	_states[_currentStateIndex]->OnStateEnter();
}

