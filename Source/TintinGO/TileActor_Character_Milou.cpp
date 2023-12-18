// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Character_Milou.h"

#include "GameManager.h"
#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"

ATileActor_Character_Milou* ATileActor_Character_Milou::SingletonInstance = nullptr;

ATileActor_Character_Milou* ATileActor_Character_Milou::GetInstance() 
{
	return SingletonInstance;
}

ATileActor_Character_Milou::ATileActor_Character_Milou()
{
	SingletonInstance = this;
	PrimaryActorTick.bCanEverTick = true;

	isBoundToTintin = true;
}

void ATileActor_Character_Milou::BeginPlay()
{
	Super::BeginPlay();

	TInlineComponentArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);

	for (int i = 0; i < Components.Num(); i++)
	{
		if(Components[i]->GetName() == TEXT("Milou Sitting"))
		{
			_milouMeshes.Add(EMilouState::Sitting, Components[i]);
		}
		else if(Components[i]->GetName() == TEXT("Milou Standing"))
		{
			_milouMeshes.Add(EMilouState::Standing, Components[i]);
		}
		else if(Components[i]->GetName() == TEXT("Milou Running"))
		{
			_milouMeshes.Add(EMilouState::Running, Components[i]);
		}
	}

	SetMilouMesh(EMilouState::Standing);
}

void ATileActor_Character_Milou::SetMilouMesh(EMilouState state)
{
	for (auto key : _milouMeshes)
	{
		if(key.Key == state)
		{
			key.Value->SetVisibility(true);
		}
		else
		{
			key.Value->SetVisibility(false);
		}
	}
}




