// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Clue.h"

#include "GameManager.h"

ATileActor_Clue::ATileActor_Clue()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor_Clue::OnEndTask()
{
	AGameManager* gameManager = AGameManager::GetInstance();
	UE_LOG(LogTemp, Warning, TEXT("clue %d %d"), clueNumber, gameManager->_clueNumber);
	if(clueNumber == gameManager->_clueNumber--)
	{
		gameManager->_clueNumber--;
		Super::OnEndTask();
	}
}
