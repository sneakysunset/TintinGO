// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"


#include "Barrier.h"
#include "CoreUI.h"
#include "State_AwaitingInputs.h"
#include "Curves/CurveFloat.h"
#include "State_TA_Move.h"
#include "Tile.h"
#include "TileActor_Clue.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "State.h"
#include "State_LevelEnd.h"
#include "State_Start.h"

AMainGameMode::AMainGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	_rows = 10;
	_columns = 10;
	_tileWidth = 1;
}

AMainGameMode::~AMainGameMode()
{
	OnClickD.Clear();
	OnMilouBoneClick.Clear();
	OnBoneConsumed.Clear();
}

void AMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(IsValid(this) && IsValid(_currentStateType) && _currentStateType != nullptr)
	{
		_currentStateType->OnStateTick(DeltaTime);
	}
}


void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> ActorsToFind;
	TArray<ATile*> tiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATile::StaticClass(), ActorsToFind);
	_rows = 0;
	_columns = 0;
	for (const auto actor : ActorsToFind)
	{
		ATile* tile = Cast<ATile>(actor);
		if(tile->_row > _rows) _rows = tile->_row;
		if(tile->_column > _columns) _columns = tile->_column;
		tiles.Add(tile);
	}
	_rows++;
	_columns++;
	for(int i = 0; i < _rows; i++)
	{
		_gridTiles.Add(FTileArray());
		for(int j = 0; j < _columns; j++)
		{
			_gridTiles[i].Tiles.Add(nullptr);
		}
	}
	for(auto tile : tiles)
	{
		_gridTiles[tile->_row].Tiles[tile->_column] = tile;
		/*for(auto item : tile->_TileItems)
		{
			if(item.actorType == ETileActorType::Clue)
			{
				_clueNumber++;
			}
		}*/
	}

	if (IsValid(YourWidgetClass))
	{
		_coreUI = CreateWidget<UCoreUI>(GetWorld(), YourWidgetClass);

		if (IsValid(_coreUI))
		{
			_coreUI->AddToViewport();
		}
	}
	_currentStateType = NewObject<UState_Start>(UState_Start::StaticClass());
	_currentStateType->_gameManager = this;
	UState_Start* state = Cast<UState_Start>(_currentStateType);
	state->_widget = _coreUI;
	state->_speed = _fadeOutScreenSpeed;
	state->_curve = _fadeOutCurve;
	
	_currentStateType->OnStateEnter();
	OnBoneConsumed.BindDynamic(this, &AMainGameMode::ChangeTextValue);
	ChangeTextValue(0, FColor::Emerald);
}

void AMainGameMode::LateInit()
{
	pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	_currentStateType->_gameManager = this;
}

void AMainGameMode::ChangeTile(UBarrier* barrier, ATile* previousTile, ATile* currentTile)
{

	if(IsValid(previousTile))
	{
		for(auto body : previousTile->_tileActors)
		{
			if(body == nullptr) continue;
			//UState_TActor* state = NewObject<UState_TA_Move>(UState_TA_Move::StaticClass());
			
			if(!barrier->_actors.Contains(body))
			{
				//body->ChangeState(state);
				barrier->_actors.Add(body);
			}
		}
	}

	if(IsValid(currentTile))
	{
		for(auto body : currentTile->_tileActors)
		{
			if(body == nullptr) continue;
			UState_TActor* state = NewObject<UState_TA_Move>(UState_TA_Move::StaticClass());
			if(!barrier->_actors.Contains(body))
			{
				body->ChangeState(state);
				barrier->_actors.Add(body);
			}
		}
	}
}

void AMainGameMode::MarkStepsOnGrid(ATile* CenterTile)
{
	check(CenterTile != nullptr);
	for(int i = 0; i < _gridTiles.Num(); i++)
	{
		for(int j = 0; j < _gridTiles[i].Tiles.Num(); j++)
		{
			_gridTiles[i].Tiles[j]->_step = -1;
		}
	}
	CenterTile->_step = 0;
	//return;
	SetStepOnAdjacentsRecursive(CenterTile);
	
}

void AMainGameMode::SetStepOnAdjacentsRecursive(ATile* tile)
{
	//Haut-> Bas -> Droite -> Gauche
	SetStepOnAdjacentTile(tile, FVector2D(1, 0));
	SetStepOnAdjacentTile(tile, FVector2D(-1, 0));
	SetStepOnAdjacentTile(tile, FVector2D(0, 1));
	SetStepOnAdjacentTile(tile, FVector2D(0, -1));
}

void AMainGameMode::SetStepOnAdjacentTile(ATile* tile, FVector2D direction)
{
	if(TileIsAvailable(tile, direction))
	{
		ATile* nextTile = _gridTiles[tile->_row + direction.X].Tiles[tile->_column + direction.Y];
		nextTile->_step = tile->_step + 1;
		SetStepOnAdjacentsRecursive(nextTile);
	}
}

bool AMainGameMode::TileIsAvailable(ATile* tile, FVector2D direction)
{
	if(tile->_row + direction.X >= 0 && tile->_row + direction.X < _gridTiles.Num() &&
		tile->_column + direction.Y >= 0 && tile->_column + direction.Y < _gridTiles[0].Tiles.Num())
	{
		ATile* adjTile = _gridTiles[tile->_row + direction.X].Tiles[tile->_column + direction.Y];
		bool directionalCondition = direction.X == 1 ? tile->_upLink : false;
		directionalCondition = direction.X == -1 ? tile ->_downLink : directionalCondition;
		directionalCondition = direction.Y == 1 ? tile ->_rightLink : directionalCondition;
		directionalCondition = direction.Y == -1 ? tile ->_leftLink : directionalCondition;
		
		if(adjTile->_walkable && directionalCondition && (adjTile->_step == -1 || adjTile->_step > tile->_step + 1))
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

TArray<ATile*> AMainGameMode::GetPath(ATile* endTile, bool getCurrentTile)
{
	TArray<ATile*> path;
	ATile* currentTile = endTile;
	path.Add(currentTile);
	int32 lastStep = 0;
	if(!getCurrentTile) lastStep = 1;
	while(currentTile->_step > lastStep)
	{
		currentTile = GetNextTileInPath(currentTile);
		path.Add(currentTile);
	}
	return path;
}

ATile* AMainGameMode::GetNextTileInPath(ATile* tile)
{
	if(tile->_row + 1 >= 0 && tile->_row + 1 < _gridTiles.Num() && _gridTiles[tile->_row + 1].Tiles[tile->_column]->_step == tile->_step - 1 && tile->_upLink)
		return _gridTiles[tile->_row + 1].Tiles[tile->_column];
	else if(tile->_row - 1 >= 0 && tile->_row - 1 < _gridTiles.Num() && _gridTiles[tile->_row - 1].Tiles[tile->_column]->_step == tile->_step - 1 && tile->_downLink)
    	return _gridTiles[tile->_row - 1].Tiles[tile->_column];
	else if(tile->_column + 1 >= 0 && tile->_column + 1 < _gridTiles[0].Tiles.Num() && _gridTiles[tile->_row].Tiles[tile->_column + 1]->_step == tile->_step - 1 && tile->_rightLink)
		return _gridTiles[tile->_row].Tiles[tile->_column + 1];
	else if(tile->_column - 1 >= 0 && tile->_column- 1 < _gridTiles[0].Tiles.Num() && _gridTiles[tile->_row].Tiles[tile->_column - 1]->_step == tile->_step - 1&& tile->_leftLink)
		return _gridTiles[tile->_row].Tiles[tile->_column - 1];
	else return nullptr;
}

ATile* AMainGameMode::WorldCoordinatesToTilePosition(const FVector& worldCoordinates)
{
	const int32 x = FMath::RoundToInt32( static_cast<float>(FMath::CeilToInt32(worldCoordinates.X)) / (_tileWidth * 100.0f)) ;
	const int32 y = FMath::RoundToInt32( static_cast<float>(FMath::CeilToInt32(worldCoordinates.Y)) / (_tileWidth * 100.0f)) ;
	if (x >= 0 && x < _rows && y >= 0 && y < _columns && _gridTiles[x].Tiles[y]->_walkable)
		return _gridTiles[x].Tiles[y];
	else
		return nullptr;
}

void AMainGameMode::ReceiveMilouUIClick()
{
	if(OnMilouBoneClick.IsBound())
	{
		OnMilouBoneClick.Execute();
	}
}

void AMainGameMode::ReceiveNextLevelClick1()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level_1"), true);
}

void AMainGameMode::ReceiveNextLevelClick2()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level_2"), true);
}

void AMainGameMode::ReceiveNextLevelClick3()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level_3"), true);
}


void AMainGameMode::ChangeTextValue(int32 newValue, FColor DisabledColor)
{
	FText MyText = FText::Format(FText::FromString(TEXT("X {0}")), FText::AsNumber(newValue));
	_coreUI->BoneNumber_Text->SetText(MyText);
	UE_LOG(LogTemp, Warning, TEXT("boneNumber %d"), newValue);
	if(newValue == 0)
	{
		_coreUI->ButtonMilou->SetIsEnabled(false);
		_coreUI->BoneNumber_Text->SetColorAndOpacity(FLinearColor(0,0,0, .6));
	}
	else
	{
		_coreUI->ButtonMilou->SetIsEnabled(true);
		_coreUI->BoneNumber_Text->SetColorAndOpacity(FLinearColor(0,0,0, 1));
	}
}

void AMainGameMode::StateChange(UState* newState)
{
	_currentStateType->OnStateExit();
	_currentStateType = newState;
	_currentStateType->_gameManager = this;
	_currentStateType->OnStateEnter();
}

void AMainGameMode::StartGameOver()
{
	_currentStateType = NewObject<UState_LevelEnd>(UState_LevelEnd::StaticClass());
	_currentStateType->_gameManager = this;
	UState_LevelEnd* state = Cast<UState_LevelEnd>(_currentStateType);
	state->_widget = _coreUI;
	state->_speed = _fadeInScreenSpeed;
	state->_curve = _fadeInCurve;
	UGameplayStatics::SpawnSoundAtLocation(ATileActor_Character_Tintin::GetInstance(), S_GameOver, ATileActor_Character_Tintin::GetInstance()->GetActorLocation());
	_nextLevelName = *UGameplayStatics::GetCurrentLevelName(GetWorld());
	
	_currentStateType->OnStateEnter();
}

void AMainGameMode::OnWin()
{
	_currentStateType = NewObject<UState_LevelEnd>(UState_LevelEnd::StaticClass());
	_currentStateType->_gameManager = this;
	UState_LevelEnd* state = Cast<UState_LevelEnd>(_currentStateType);
	state->_widget = _coreUI;
	state->_speed = _fadeInScreenSpeed;
	state->_curve = _fadeInCurve;
	
	if(UGameplayStatics::GetCurrentLevelName(GetWorld()) == FString("Level_1"))
	{
		 _nextLevelName =  *FString("Level_2");
	}
	else if(UGameplayStatics::GetCurrentLevelName(GetWorld()) == FString("Level_2"))
	{
		_nextLevelName =  *FString("Level_3");
	}
	
	_currentStateType->OnStateEnter();
}

void AMainGameMode::LevelTransi() const
{
	UGameplayStatics::OpenLevel(GetWorld(), *_nextLevelName, true);
}

ATile* AMainGameMode::GetTile(int32 i, int32 j)
{
	if (i >= 0 && i < _gridTiles.Num() && j >= 0 && j < _gridTiles[i].Tiles.Num())
	{
		return _gridTiles[i].Tiles[j];
	}

	return nullptr;
}
