// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"

#include "GameManager.h"

// Sets default values
AUIManager::AUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (YourWidgetClass)
	{
		_coreUI = CreateWidget<UCoreUI>(GetWorld(), YourWidgetClass);

		if (_coreUI)
		{
			_coreUI->AddToViewport();
		}
		AGameManager::GetInstance()->OnBoneConsumed.BindDynamic(this, &AUIManager::ChangeTextValue);
		ChangeTextValue(0, FColor::Emerald);
	}
}

// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUIManager::ChangeTextValue(int32 newValue, FColor DisabledColor)
{
	_coreUI->BoneNumber_Text->SetText(FText(FText::FromString("X  " + newValue)));
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