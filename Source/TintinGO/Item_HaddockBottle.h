// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_HaddockBottle.generated.h"

/**
 * 
 */
UCLASS()
class TINTINGO_API AItem_HaddockBottle : public AItem
{
	GENERATED_BODY()

public:
	AItem_HaddockBottle();
	virtual void TriggerBody() override;
};
