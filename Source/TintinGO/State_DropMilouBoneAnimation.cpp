// Fill out your copyright notice in the Description page of Project Settings.


#include "State_DropMilouBoneAnimation.h"

#include "GameManager.h"
#include "GridManager.h"
#include "State_MilouRotate.h"
#include "State_TA_Move.h"
#include "TileActor.h"

void UState_DropMilouBoneAnimation::OnStateEnter()
{
	UState::OnStateEnter();
	UE_LOG(LogTemp, Warning, TEXT("Milou Move State Enter"));

	_milou = ATileActor_Character_Milou::GetInstance();
	
	FActorSpawnParameters params;
	params.bNoFail = true;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FVector position = _milou->GetActorLocation();
	FRotator rotation = FRotator(0, 0, 0);

	UE_LOG(LogTemp, Warning, TEXT("valid MilouBP"));

	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	_milouBone = _milou->GetCurrentTile()->milouBoneToDrop;
	
	ATile* previousTile =_milou->GetCurrentTile();

	UE_LOG(LogTemp, Warning, TEXT("%d, %d"), _milou->MilouTilePath[0]->_row, _milou->MilouTilePath[0]->_column);
	
	ATile* nextTile = _milou->MilouTilePath[0];
	_milouBone->SetCurrentTile(nextTile);
	
	AGridManager::GetInstance()->ChangeTile(_barrier, previousTile, _milouBone->GetCurrentTile());
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
	Cast<UState_TA_Move>(_milouBone->_currentState_TA)->_actorSpeed = _milouBone->_speed;
	Cast<UState_TA_Move>(_milouBone->_currentState_TA)->_speed = _milouBone->_speed;
}

void UState_DropMilouBoneAnimation::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted)
	{
		_gameManager->StateChange(NewObject<UState_MilouRotate>(UState_MilouRotate::StaticClass()));
	}
	_barrier->OnTick(DeltaTime);
}

void UState_DropMilouBoneAnimation::OnStateExit()
{
	_milou->MilouTilePath[0]->milouBoneToDrop = _milou->GetCurrentTile()->milouBoneToDrop;
	_milou->GetCurrentTile()->milouBoneToDrop = nullptr;
	UState::OnStateExit();
}