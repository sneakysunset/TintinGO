// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Clue.h"

#include "GameManager.h"
#include "GridManager.h"

ATileActor_Clue::ATileActor_Clue()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor_Clue::OnEndTask()
{
	AGameManager* gameManager = AGameManager::GetInstance();
	UE_LOG(LogTemp, Warning, TEXT("clue %d %d"), clueNumber, gameManager->_clueNumber);
	if(clueNumber == gameManager->_clueNumber)
	{
		gameManager->_clueNumber--;
		AGridManager* gridManager = AGridManager::GetInstance();
		for(auto tileRow : gridManager->_gridTiles)
		{
			for (auto tile : tileRow.Tiles)
			{
				for (auto actor : tile->_tileActors)
				{
					if(actor->IsA<ATileActor_Clue>())
					{
						ATileActor_Clue* clue = Cast<ATileActor_Clue>(actor);
						if(clue->clueNumber == clueNumber - 1)
						{
							clue->SetActorHiddenInGame(false);
						}
					}
				}
			}
		}
		Super::OnEndTask();
	}
}

void ATileActor_Clue::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(initTimer < .3f)
	{
		initTimer += DeltaSeconds;
	}
	else if(!hasInit)
	{
		hasInit = true;
		Init();
	}
}

void ATileActor_Clue::Init()
{
		UE_LOG(LogTemp, Error, TEXT("ClueNUmer = %d, %d"), clueNumber, AGameManager::GetInstance()->_clueNumber);
	if(clueNumber == AGameManager::GetInstance()->_clueNumber)
	{
		SetActorHiddenInGame(false);
	}
}



