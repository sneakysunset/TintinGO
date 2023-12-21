// Fill out your copyright notice in the Description page of Project Settings.


#include "State_DropMilouBoneAnimation.h"

#include "GameManager.h"
#include "MainGameMode.h"
#include "State_MilouBone_Move.h"
#include "State_MilouRotate.h"
#include "State_TA_Move.h"
#include "TileActor.h"
#include "TileActor_Character_Tintin.h"
#include "Kismet/GameplayStatics.h"

void UState_DropMilouBoneAnimation::OnStateEnter()
{
	UState::OnStateEnter();
	if(_gameManager->DebugStateChange)
	UE_LOG(LogTemp, Warning, TEXT("Milou Bone Throw State Enter"));

	_milou = ATileActor_Character_Milou::GetInstance();
	ATileActor_Character_Tintin::GetInstance()->GetCurrentTile()->SpawnMilouBone();
	
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
	if(_gameManager->_milouSign != nullptr)
	{
		_milouSignBarrier = NewObject<UBarrier>(UBarrier::StaticClass());
		for (auto actor : _gameManager->_endTile->_tileActors)
		{
			_milouSignBarrier->_actors.Add(actor);
		}
		_milouSignBarrier->OnBarrierIni(UState_TA_Move::StaticClass());
	}
	
	ATile* previousTile =_milou->GetCurrentTile();

	ATile* nextTile = _milou->MilouTilePath[0];
	_milou->_milouBoneToDrop->SetCurrentTile(nextTile);

	_gameManager->ChangeTile(_barrier, previousTile, _milou->_milouBoneToDrop->GetCurrentTile());
	_barrier->OnBarrierIni(UState_MilouBone_Move::StaticClass());
	Cast<UState_MilouBone_Move>(_milou->_milouBoneToDrop->_currentState_TA)->_actorSpeed = _milou->_milouBoneToDrop->_speed;
	Cast<UState_MilouBone_Move>(_milou->_milouBoneToDrop->_currentState_TA)->_speed = _milou->_milouBoneToDrop->_speed;
	UGameplayStatics::SpawnSoundAtLocation(_milou, _milou->_milouBoneToDrop->S_BoneThrow, _milou->_milouBoneToDrop->GetActorLocation());
	ATileActor_Character_Tintin::GetInstance()->SetTintinMesh(ETintinState::Running);

}

void UState_DropMilouBoneAnimation::OnStateTick(float DeltaTime)
{
	UState::OnStateTick(DeltaTime);
	if(_barrier->_isBarriereCompleted && (_milouSignBarrier == nullptr || _milouSignBarrier->_isBarriereCompleted))
	{
		UGameplayStatics::SpawnSoundAtLocation(_milou, _milou->_milouBoneToDrop->S_BoneLand, _milou->_milouBoneToDrop->GetActorLocation());
		_gameManager->StateChange(NewObject<UState_MilouRotate>(UState_MilouRotate::StaticClass()));
	}
	_barrier->OnTick(DeltaTime);
	if(_milouSignBarrier != nullptr)
	{
		_milouSignBarrier->OnTick(DeltaTime);
	}
}

void UState_DropMilouBoneAnimation::OnStateExit()
{
	UState::OnStateExit();
}