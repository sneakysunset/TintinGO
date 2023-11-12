// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "Tile.generated.h"


UENUM(BlueprintType)
enum class ETileType : uint8
{
	Neutral = 0b0000 UMETA(DisplayName = "Neutral"),
	StartingPosition = 0b0001 UMETA(DisplayName = "Starting Position"),
	EndingPosition = 0b0010 UMETA(DisplayName = "Ending Position")
};

UCLASS()
class TINTINGO_API ATile : public AActor
{
	GENERATED_BODY()

public:


	ATile();

	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		ETileType _tileType {
		ETileType::Neutral
	};
	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		bool _walkable = true;
	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		TArray<AItem*> _items;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Editor Parameters")
		bool _useEditorTick = true;

	int32 _row;
	int32 _column;
	UMaterialInterface* _walkableMat;
	UMaterialInterface* _unwalkableMat;
	UMaterialInterface* _startPosMat;
	UMaterialInterface* _endPosMat;

	UFUNCTION(BlueprintCallable)
		void AddItem();
protected:
	class UStaticMeshComponent* _staticMeshComponent = nullptr;

	bool _walkableChecker = true;

	ETileType _tileTypeChecker {ETileType::Neutral};
	
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
		void BlueprintEditorTick(float DeltaTime);

};
