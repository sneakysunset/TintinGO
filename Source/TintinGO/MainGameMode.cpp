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
#include "TileActor_Character_Peruvien.h"

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

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> ActorsToFind;

	//Populate _gridTiles with the tiles in the scene.
	//I am using such a dirty way because I had some urgent package crashs (that were not happening in editor)
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

	//Initialize States 
	_currentStateType = NewObject<UState_Start>(UState_Start::StaticClass());
	_currentStateType->_gameManager = this;
	UState_Start* state = Cast<UState_Start>(_currentStateType);
	state->_widget = _coreUI;
	state->_speed = _fadeOutScreenSpeed;
	state->_curve = _fadeOutCurve;
	
	_currentStateType->OnStateEnter();

	//UIBinding and initialization
	OnBoneConsumed.BindDynamic(this, &AMainGameMode::ChangeTextValue);
	ChangeTextValue(0, FColor::Emerald);

	InitializeMusic();
}

void AMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(IsValid(this) && IsValid(_currentStateType) && _currentStateType != nullptr)
	{
		_currentStateType->OnStateTick(DeltaTime);
	}

	UpdateMusic(DeltaTime);
}

void AMainGameMode::InitializeMusic()
{
	//We have 2 main musics that switch when a peruvien detects tintin and switchs back when no one detects tintin.
	//To have smooth transitions I had to set up some things later used.
	_puruitMusicAudioComponent = NewObject<UAudioComponent>(this);
	_puruitMusicAudioComponent->SetSound(S_pursuitMusic);
	_puruitMusicAudioComponent->RegisterComponent();
	_puruitMusicAudioComponent->SetVolumeMultiplier(0.1);
	_musicAudioComponent = NewObject<UAudioComponent>(this);
	_musicAudioComponent->SetSound(S_music);
	_musicAudioComponent->RegisterComponent();
	_musicFadeInterpolateValue = 1;
	_musicCurve = _musicFadeUpCurve;
	_pursuitMusicCurve = _musicFadeDownCurve;
	chaseMusic = false;
}

//Late Init is started At the end of startState. It is helpful to avoid packaging crashs
//that were triggered because the exectution order was fucked up.
void AMainGameMode::LateInit()
{
	pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	_currentStateType->_gameManager = this;
}

//When actors change tile in a state this will add all the tile actors in the previous and destination tiles
//to the barrier in order to change their positions on the tile acoordingly to the new number of tileActors.
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

//Initialize Pathfinding. Marks all tile with the number of movements that seperate them from the center tile.
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

//Set the steps for pathfinding on all the adjacent tiles to the parameter tile. If the tile is already marked with
//a lower number or is inaccessible it will be skipped.
void AMainGameMode::SetStepOnAdjacentsRecursive(ATile* tile)
{
	//Haut-> Bas -> Droite -> Gauche
	SetStepOnAdjacentTile(tile, FVector2D(1, 0));
	SetStepOnAdjacentTile(tile, FVector2D(-1, 0));
	SetStepOnAdjacentTile(tile, FVector2D(0, 1));
	SetStepOnAdjacentTile(tile, FVector2D(0, -1));
}

//The single process of the above method.
void AMainGameMode::SetStepOnAdjacentTile(ATile* tile, FVector2D direction)
{
	if(TileIsAvailable(tile, direction))
	{
		ATile* nextTile = _gridTiles[tile->_row + direction.X].Tiles[tile->_column + direction.Y];
		nextTile->_step = tile->_step + 1;
		SetStepOnAdjacentsRecursive(nextTile);
	}
}

//Check if the targetted tile should be marked for pathfinding.
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

//Returns an array of tiles containing the quickest way to the center
//tile called in the last MarkStepsOnGrid starting at the endTile.
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

//Function used to generate the array in GetPath. Order is important here as
//it will define pathfinding directional priority.
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

//Transforms a FVector position to the corresponding tile position.
//If the position is outside the bounds of the grid nullptr will be returned.
ATile* AMainGameMode::WorldCoordinatesToTilePosition(const FVector& worldCoordinates)
{
	const int32 x = FMath::RoundToInt32( static_cast<float>(FMath::CeilToInt32(worldCoordinates.X)) / (_tileWidth * 100.0f)) ;
	const int32 y = FMath::RoundToInt32( static_cast<float>(FMath::CeilToInt32(worldCoordinates.Y)) / (_tileWidth * 100.0f)) ;
	if (x >= 0 && x < _rows && y >= 0 && y < _columns && _gridTiles[x].Tiles[y]->_walkable)
		return _gridTiles[x].Tiles[y];
	else
		return nullptr;
}

//Delegate function receiver.
void AMainGameMode::ReceiveMilouUIClick()
{
	if(OnMilouBoneClick.IsBound())
	{
		OnMilouBoneClick.Execute();
	}
}

//Delegate function receiver.
void AMainGameMode::ReceiveNextLevelClick1()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level_1"), true);
}

//Delegate function receiver.
void AMainGameMode::ReceiveNextLevelClick2()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level_2"), true);
}

//Delegate function receiver.
void AMainGameMode::ReceiveNextLevelClick3()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level_3"), true);
}

//Delegate function receiver to change the bone button.
void AMainGameMode::ChangeTextValue(int32 newValue, FColor DisabledColor)
{
	FText MyText = FText::Format(FText::FromString(TEXT("X {0}")), FText::AsNumber(newValue));
	_coreUI->BoneNumber_Text->SetText(MyText);
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

//Change State
void AMainGameMode::StateChange(UState* newState)
{
	_currentStateType->OnStateExit();
	_currentStateType = newState;
	_currentStateType->_gameManager = this;
	_currentStateType->OnStateEnter();
}

//Start Game over transition state to get fade out and delay.
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

//Start Win transition state to get fade out and delay.
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

//Load new level.
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

ATile* AMainGameMode::GetTileIfAccessible(int32 i, int32 j, EAngle angle)
{
	if (i >= 0 && i < _gridTiles.Num() && j >= 0 && j < _gridTiles[i].Tiles.Num())
	{
		ATile* nextTile = _gridTiles[i].Tiles[j];
		if(nextTile->_walkable)
		{
			switch(angle)
			{
				case EAngle::Right: if(nextTile->_rightLink) return nextTile; break;
				case EAngle::Left: if(nextTile->_leftLink) return nextTile; break;
				case EAngle::Up: if(nextTile->_upLink) return nextTile; break;
				case EAngle::Down: if(nextTile->_downLink) return nextTile; break;
			}
		}
	}

	return nullptr;
}

//Get the tile in the direction specified.
ATile* AMainGameMode::GetForwardTile(const ATile* tile, EAngle angle)
{
	ATile* resultTile = nullptr;
	switch(angle)
	{
		case EAngle::Up: resultTile = GetTileIfAccessible(tile->_row + 1, tile->_column, EAngle::Down); break;
		case EAngle::Left: resultTile = GetTileIfAccessible(tile->_row, tile->_column -1, EAngle::Right); break;
		case EAngle::Right: resultTile = GetTileIfAccessible(tile->_row, tile->_column + 1, EAngle::Left); break;
		case EAngle::Down: resultTile = GetTileIfAccessible(tile->_row - 1, tile->_column, EAngle::Up); break;
	}
	return resultTile;
}

//Update visual feedback for the peruviens detect range.
void AMainGameMode::SetTilesPeruvienColor(bool toVisible, EAngle direction, const ATile* startTile)
{
	const ATile* forwardTile = GetForwardTile(startTile, direction);
	if(IsValid(forwardTile))
	{
		startTile->SetEnnemyDirection(toVisible, direction, false);
		const ATile* forwardForwardTile = GetForwardTile(forwardTile, direction);
		if(IsValid(forwardForwardTile))
		{
			forwardTile->SetEnnemyDirection(toVisible, direction, false);
			forwardForwardTile->SetEnnemyDirection(toVisible, direction, true);
		}
		else
		{
			forwardTile->SetEnnemyDirection(toVisible, direction, true);
		}
	}
	else
	{
		startTile->SetEnnemyDirection(toVisible, direction, true);
	}


	
}

//Initialization of smooth switch between nomal music and pursuit music.
void AMainGameMode::ChangeMusic()
{
	if(_pursuitPeruviens.Num() > 0 && chaseMusic) return;
	else if(_pursuitPeruviens.Num() > 0 && !chaseMusic) chaseMusic = true;
	else if(_pursuitPeruviens.Num() == 0 && !chaseMusic) return;
	else if(_pursuitPeruviens.Num() == 0 && chaseMusic) chaseMusic = false;

	_musicFadeInterpolateValue = 0;
	_musicCurve = chaseMusic ? _musicFadeDownCurve : _musicFadeUpCurve;
	_pursuitMusicCurve = chaseMusic ? _musicFadeUpCurve : _musicFadeDownCurve;
	//_musicAudioComponent->AdjustVolume(2, musicAudioTarget, EAudioFaderCurve::Linear);
	//_puruitMusicAudioComponent->AdjustVolume(2, pursuitMusicAudioTarget, EAudioFaderCurve::Linear);
	//UE_LOG(LogTemp, Warning, TEXT("MUSIC CHANGE music = %f and pursuit = %f"), musicAudioTarget, pursuitMusicAudioTarget);
}

//Smoothe switch between musics.
void AMainGameMode::UpdateMusic(float DeltaTime)
{
	if(_musicFadeInterpolateValue <= 1)
	{
		_musicFadeInterpolateValue += DeltaTime * _fadeTime;
		_musicAudioComponent->SetVolumeMultiplier(_musicCurve->FloatCurve.Eval(_musicFadeInterpolateValue));
		_puruitMusicAudioComponent->SetVolumeMultiplier(_pursuitMusicCurve->FloatCurve.Eval(_musicFadeInterpolateValue));
	}
}
