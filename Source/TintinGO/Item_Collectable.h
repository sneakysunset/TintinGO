// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Item_Collectable.generated.h"

UCLASS()
class TINTINGO_API AItem_Collectable : public AItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_Collectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnTriggered() override;

};
