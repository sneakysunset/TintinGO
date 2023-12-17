// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Clue.h"

#include "GameManager.h"
#include "GridManager.h"
#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"

ATileActor_Clue::ATileActor_Clue()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor_Clue::OnEndTask()
{
	if(clueNumber == _gameManager->_clueNumber)
	{
		_gameManager->_clueNumber--;
		for(auto tileRow : _gameManager->_gridTiles)
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
		if(clueNumber == 1)
		{
			UGameplayStatics::SpawnSoundAtLocation(this, S_EndTileActivated, GetActorLocation());	
		}
		else
		{
			UGameplayStatics::SpawnSoundAtLocation(this, S_CluePickUp, GetActorLocation());
		}
		if(_currentTile->_tileActors.Contains(this))
			_currentTile->_tileActors.Remove(this);
		Destroy();
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
	if(clueNumber == _gameManager->_clueNumber)
	{
		SetActorHiddenInGame(false);
	}
}



