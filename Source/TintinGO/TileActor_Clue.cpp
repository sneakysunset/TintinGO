// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Clue.h"

#include "GameManager.h"
#include "GridManager.h"
#include "MainGameMode.h"
#include "State_TA_Move.h"
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
	if(clueNumber == 1)
	{
		Super::TriggerBody();
		UGameplayStatics::SpawnSoundAtLocation(this, S_EndTileActivated, GetActorLocation());	

		return;
	}
	_barrier = NewObject<UBarrier>(UBarrier::StaticClass());
		
	for (int i = 0; i < _gameManager->_gridTiles.Num(); i++)
	{
		for (int j = 0; j < _gameManager->_gridTiles[i].Tiles.Num(); j++)
		{
			for (int k = 0; k < _gameManager->_gridTiles[i].Tiles[j]->_TileItems.Num(); k++)
			{
				if(_gameManager->_gridTiles[i].Tiles[j]->_TileItems[k].actorType == ETileActorType::Clue && _gameManager->_gridTiles[i].Tiles[j]->_TileItems[k].clueIndex == clueNumber - 1)
				{
					FActorSpawnParameters params;
					params.bNoFail = true;
					params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
					params.ObjectFlags |= RF_Transient;
					FRotator rotation = FRotator(0, 0, 0);
					FVector position = _gameManager->_gridTiles[i].Tiles[j]->GetActorLocation();
					const auto newClue = GetWorld()->SpawnActor<ATileActor_Clue>(_clueBP, position, rotation, params);
					//_gameManager->_clues.Add(newClue);
					UGameplayStatics::SpawnSoundAtLocation(this, S_CluePickUp, GetActorLocation());

					newClue->SetCurrentTile(_gameManager->_gridTiles[i].Tiles[j]);
					for (int f = 0; f < _gameManager->_gridTiles[i].Tiles[j]->_tileActors.Num(); f++)
					{
						_barrier->_actors.Add(_gameManager->_gridTiles[i].Tiles[j]->_tileActors[f]);
					}
					_barrier->OnBarrierIni(UState_TA_Move::StaticClass());
					return;
				}
			} 
		}
	}
}

void ATileActor_Clue::OnEndTask()
{
	_gameManager->_clueNumber--;
	Super::OnEndTask();
	if(_currentTile->_tileActors.Contains(this))
		_currentTile->_tileActors.Remove(this);
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
