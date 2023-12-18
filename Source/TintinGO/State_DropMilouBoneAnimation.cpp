// Fill out your copyright notice in the Description page of Project Settings.


#include "State_DropMilouBoneAnimation.h"

#include "GameManager.h"
#include "MainGameMode.h"
#include "State_MilouBone_Move.h"
#include "State_MilouRotate.h"
#include "TileActor.h"
#include "Kismet/GameplayStatics.h"

void UState_DropMilouBoneAnimation::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Milou Bone Throw State Enter"));

	_milou = ATileActor_Character_Milou::GetInstance();
	
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	
	ATile* previousTile =_milou->GetCurrentTile();

	ATile* nextTile = _milou->MilouTilePath[0];
	_milou->_milouBoneToDrop->SetCurrentTile(nextTile);
	
	_gameManager->ChangeTile(_barrier, previousTile, _milou->_milouBoneToDrop->GetCurrentTile());
	_barrier->OnBarrierIni(UState_MilouBone_Move::StaticClass());
	Cast<UState_MilouBone_Move>(_milou->_milouBoneToDrop->_currentState_TA)->_actorSpeed = _milou->_milouBoneToDrop->_speed;
	Cast<UState_MilouBone_Move>(_milou->_milouBoneToDrop->_currentState_TA)->_speed = _milou->_milouBoneToDrop->_speed;
	UGameplayStatics::SpawnSoundAtLocation(_milou, _milou->_milouBoneToDrop->S_BoneThrow, _milou->_milouBoneToDrop->GetActorLocation());
}

void UState_DropMilouBoneAnimation::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		UGameplayStatics::SpawnSoundAtLocation(_milou, _milou->_milouBoneToDrop->S_BoneLand, _milou->_milouBoneToDrop->GetActorLocation());
		_gameManager->StateChange(NewObject<UState_MilouRotate>(UState_MilouRotate::StaticClass()));
	}
	_barrier->OnTick(DeltaTime);
}

void UState_DropMilouBoneAnimation::OnStateExit()
{
	UState::OnStateExit();
}