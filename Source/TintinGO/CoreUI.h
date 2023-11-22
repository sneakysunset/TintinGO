// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoreUI.generated.h"

class UButton;
class UCanvasPanel;

UCLASS()
class TINTINGO_API UCoreUI : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ButtonMilou;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> ButtonHadoc;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UCanvasPanel> Canvas;
};
