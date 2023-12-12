// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGameManager.h"

#include "Kismet/GameplayStatics.h"

UGlobalGameManager::UGlobalGameManager()
{
	_levelNames.Add("Levels/Level_1");
	_levelNames.Add("Levels/Level_2");
	_levelNames.Add("Levels/Level_3");
}

void UGlobalGameManager::OnWin()
{
	if(UGameplayStatics::GetCurrentLevelName(GetWorld()) == _levelNames[0])
	{
		UGameplayStatics::OpenLevel(GetWorld(),  *_levelNames[1], true);
	}
	else if(UGameplayStatics::GetCurrentLevelName(GetWorld()) == _levelNames[1])
	{
		UGameplayStatics::OpenLevel(GetWorld(),  *_levelNames[2], true);
	}
}

void UGlobalGameManager::OnGameOver() const
{
	UGameplayStatics::OpenLevel(GetWorld(), *UGameplayStatics::GetCurrentLevelName(GetWorld()), true);
}

void UGlobalGameManager::OnLevelLoad()
{
	
}

