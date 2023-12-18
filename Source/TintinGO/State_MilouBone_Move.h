// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_TActor.h"
#include "State_MilouBone_Move.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API UState_MilouBone_Move : public UState_TActor
{
	GENERATED_BODY()
	
public:
	ATileActor* tActor;
	
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateComplete() override;
	float _actorSpeed;

private:
	FVector _startPosition;
	FVector _endPosition;
	
};
