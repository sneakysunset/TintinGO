// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CoreUI.generated.h"

class UButton;
class UCanvasPanel;

UCLASS()
class TINTINGO_API UCoreUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ButtonMilou;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> BoneNumber_Text;


};
