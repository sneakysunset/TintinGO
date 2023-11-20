// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "MainGameState.h"
#include "GridManager.h"

AMainGameMode::AMainGameMode()
{
    // Set default pawn class to your character class
    //DefaultPawnClass = AYourCharacter::StaticClass();

    // Set the grid manager class
    HUDClass = AGridManager::StaticClass();
}
