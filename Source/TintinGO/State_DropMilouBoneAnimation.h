// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Barrier.h"
#include "State.h"
#include "TileActor_Character_Milou.h"
#include "TileActor_MilouBone.h"
#include "State_DropMilouBoneAnimation.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API UState_DropMilouBoneAnimation : public UState
{
	GENERATED_BODY()
public:
	virtual void OnStateEnter() override;
	virtual void OnStateTick(float DeltaTime) override;
	virtual void OnStateExit() override;

	
private:
	UBarrier* _barrier;

	ATileActor_Character_Milou* _milou;

	ATileActor_MilouBone* _milouBone;
};
