// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

#include "GameManager.h"

// Sets default values
AUIManager::AUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (IsValid(YourWidgetClass))
	{
		_coreUI = CreateWidget<UCoreUI>(GetWorld(), YourWidgetClass);

		if (IsValid(_coreUI))
		{
			_coreUI->AddToViewport();
		}
	}
}

// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
	Super::BeginPlay();
	//ChangeTextValue(0, FColor::Emerald);
	if (IsValid(YourWidgetClass))
	{
		_coreUI = CreateWidget<UCoreUI>(GetWorld(), YourWidgetClass);
	}
	_coreUI->AddToViewport(9999);
	AGameManager* gameManager = AGameManager::GetInstance();
	gameManager->OnBoneConsumed.BindDynamic(this, &AUIManager::ChangeTextValue);
	if(gameManager->OnBoneConsumed.IsBound())
	{
		gameManager->OnBoneConsumed.Execute(0, FColor::Emerald);
	}
}

void AUIManager::ChangeTextValue(int32 newValue, FColor DisabledColor)
{
	_coreUI->BoneNumber_Text->SetText(FText(FText::FromString("X  " + newValue)));
	UE_LOG(LogTemp, Warning, TEXT("boneNumber %d"), newValue);
	if(newValue == 0)
	{
		_coreUI->ButtonMilou->SetIsEnabled(false);
		_coreUI->BoneNumber_Text->SetColorAndOpacity(DisabledColor);
	}
	else
	{
		_coreUI->ButtonMilou->SetIsEnabled(true);
		_coreUI->BoneNumber_Text->SetColorAndOpacity(FColor::Black);
	}
}



