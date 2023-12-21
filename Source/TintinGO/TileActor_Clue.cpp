// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Clue.h"

#include "GameManager.h"
#include "GridManager.h"
#include "MainGameMode.h"
#include "State_TA_Move.h"
#include "TileActor_Cadenas.h"
#include "Kismet/GameplayStatics.h"

ATileActor_Clue::ATileActor_Clue()
{
	PrimaryActorTick.bCanEverTick = true;
}



void ATileActor_Clue::BeginPlay()
{
	Super::BeginPlay();

	TInlineComponentArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	for (auto component : Components)
	{
		if(component->GetName() == TEXT("QuestionMark"))
		{
			MeshComponent = component;
			break;
		}
	}
	_startHeight = MeshComponent->GetComponentLocation().Z;
	_endHeight = _startHeight + _heightToGoUp;
}

void ATileActor_Clue::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if(_barrier != nullptr && _barrier->_isBarriereCompleted)
	{
		_isTaskOver = true;
	}
	else if(_barrier != nullptr && !_barrier->_isBarriereCompleted)
	{
		_barrier->OnTick(DeltaSeconds);
	}

	ClueAnimation(DeltaSeconds);
}

void ATileActor_Clue::TriggerBody()
{
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());

	//Barrier this clue tile without Destroying and make actor hidden
	{
		if(GetCurrentTile()->_tileActors.Contains(this)) GetCurrentTile()->_tileActors.Remove(this);
		for(int i = 0; i < GetCurrentTile()->_tileActors.Num(); i++)
		{
			_barrier->_actors.Add(GetCurrentTile()->_tileActors[i]);
		}
		SetActorHiddenInGame(true);
	}

	//Barrier the cadenas tile and Destroy the cadenas
	if(clueNumber == 1)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, S_EndTileActivated, GetActorLocation());
		ATile* endTile = _gameManager->_endTile;
		if(_gameManager->_cadenas != nullptr && endTile->_tileActors.Contains(_gameManager->_cadenas)) endTile->_tileActors.Remove(_gameManager->_cadenas);
		for(int i = 0; i < endTile->_tileActors.Num(); i++)
		{
			_barrier->_actors.Add(endTile->_tileActors[i]);
		}
	}
	//Spawn new clue if clueNumber is > 1
	else
	{
		bool isOver = false;
		for (int i = 0; i < _gameManager->_gridTiles.Num(); i++)
		{
			if(isOver) break;
			for (int j = 0; j < _gameManager->_gridTiles[i].Tiles.Num(); j++)
			{
				if(isOver) break;
				for (int k = 0; k < _gameManager->_gridTiles[i].Tiles[j]->_TileItems.Num(); k++)
				{
					if(_gameManager->_gridTiles[i].Tiles[j]->_TileItems[k].actorType == ETileActorType::Clue && _gameManager->_gridTiles[i].Tiles[j]->_TileItems[k].clueIndex == clueNumber - 1)
					{
						FActorSpawnParameters params;
						params.bNoFail = true;
						params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
						params.ObjectFlags |= RF_Transient;
						const FRotator rotation = FRotator(0, 0, 0);
						const FVector position = _gameManager->_gridTiles[i].Tiles[j]->GetActorLocation();
						const auto newClue = GetWorld()->SpawnActor<ATileActor_Clue>(_gameManager->_gridTiles[i].Tiles[j]->_clueBP, position, rotation, params);
						//_gameManager->_clues.Add(newClue);
						UGameplayStatics::SpawnSoundAtLocation(this, S_CluePickUp, GetActorLocation());

						newClue->SetCurrentTile(_gameManager->_gridTiles[i].Tiles[j]);
						for (int f = 0; f < _gameManager->_gridTiles[i].Tiles[j]->_tileActors.Num(); f++)
						{
							_barrier->_actors.Add(_gameManager->_gridTiles[i].Tiles[j]->_tileActors[f]);
						}
						newClue->clueNumber = clueNumber - 1;
						newClue->angle = _gameManager->_gridTiles[i].Tiles[j]->_TileItems[k].angle;
						newClue->SetUpRotation(newClue->angle);
						isOver= true;
						break;
					}
				} 
			}
	}	
	}
	
	_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
}

void ATileActor_Clue::OnEndTask()
{
	_gameManager->_clueNumber--;
	Super::OnEndTask();
	if(clueNumber == 1)
	{
		_gameManager->_cadenas->Destroy();
	}
	Destroy();
}


void ATileActor_Clue::ClueAnimation(float DeltaSeconds)
{
	_interpolateValue += ascending ? _animationSpeed * DeltaSeconds : -_animationSpeed * DeltaSeconds;
	_interpolateValue = FMath::Clamp(_interpolateValue, 0, 1);
	const FVector position = FVector(MeshComponent->GetComponentLocation().X, MeshComponent->GetComponentLocation().Y, FMath::Lerp(_startHeight, _endHeight, _animCurve->FloatCurve.Eval(_interpolateValue)));
	MeshComponent->SetWorldLocation(position);

	if(_interpolateValue >= 1 && ascending)
	{
		ascending = false;
	}
	else if(_interpolateValue <= 0 && !ascending)
	{
		ascending = true;
	}
}
