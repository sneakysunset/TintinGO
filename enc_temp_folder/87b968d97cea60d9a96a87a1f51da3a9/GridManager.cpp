// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"

// Sets default values
AGridManager::AGridManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

bool AGridManager::ShouldTickIfViewportsOnly() const
{
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor && _useEditorTick)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AGridManager::InitializeGrid()
{

}

void AGridManager::OccupyCell(int32 Row, int32 Col)
{

}

void AGridManager::ReleaseCell(int32 Row, int32 Col)
{

}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGridManager::BlueprintEditorTick(float DeltaTime)
{
	if (_initializeGrid) 
	{
		InitializeGrid();
		_initializeGrid = false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Test"));
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("Test"));
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}

#endif
	Super::Tick(DeltaTime);

}
