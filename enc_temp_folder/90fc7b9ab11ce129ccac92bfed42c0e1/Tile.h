// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Tile.generated.h"

UCLASS()
class TINTINGO_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	ATile(int32 row, int32 column, float width, int32 height);
	UPROPERTY(EditAnywhere)
	int32 _height;
	UPROPERTY(EditAnywhere)
	int32 _row;
	UPROPERTY(EditAnywhere)
	int32 _column;
	UPROPERTY(EditAnywhere)
	TArray<AItem*> _items;
	UFUNCTION(BlueprintCallable)
	void AddItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* _staticMeshComponent = nullptr;
};
