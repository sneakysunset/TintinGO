// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "MainGameState.h"

AMainGameMode::AMainGameMode()
{
	GameStateClass = AMainGameState::StaticClass();
}

int32 AMainGameMode::GetRows() const
{
	return GetGameState<AMainGameState>()->_rows;
}

int32 AMainGameMode::GetColumns() const
{
	return GetGameState<AMainGameState>()->_columns;
}

void AMainGameMode::SetRows(int32 rows) 
{
	GetGameState<AMainGameState>()->_rows = rows;
}

void AMainGameMode::SetColumns(int32 columns)
{
	GetGameState<AMainGameState>()->_columns = columns;
}

void AMainGameMode::StartPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Start Play called"));

	StartPlayEvent();

	GetWorld()->GetAuthGameMode()->GetGameState<AMainGameState>()->_rows = 50;

	Super::StartPlay();
}

void AMainGameMode::StartPlayEvent_Implementation() 
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("StartPlayEvent Default Implementation called"));

}

//void AMainGameMode::GenerateGrid() 
//{
//	AMainGameMode::_tileGrid.SetNum(AMainGameMode::_rows);
//	for (size_t i = 0; i < AMainGameMode::_rows; i++)
//	{
//		AMainGameMode::_tileGrid[i].SetNum(AMainGameMode::_columns);
//		for (size_t i = 0; i < AMainGameMode::_columns; i++)
//		{
//
//		}
//	}
//	
//
//}