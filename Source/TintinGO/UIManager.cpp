// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

#include "GameManager.h"
#include "MainGameMode.h"

/*AUIManager* AUIManager::SingletonInstance = nullptr;

AUIManager* AUIManager::GetInstance()
{
	return SingletonInstance;
}

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
	SingletonInstance = this;
	//ChangeTextValue(0, FColor::Emerald);
	if (IsValid(YourWidgetClass))
	{
		_coreUI = CreateWidget<UCoreUI>(GetWorld(), YourWidgetClass);
	}
	_coreUI->AddToViewport(9999);
	ChangeTextValue(0, FColor::Emerald);
}

void AUIManager::ChangeTextValue(int32 newValue, FColor DisabledColor)
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

void AUIManager::CustomInit()
{
	AMainGameMode* gameManager = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	gameManager->OnBoneConsumed.BindDynamic(this, &AUIManager::ChangeTextValue);
}*/



