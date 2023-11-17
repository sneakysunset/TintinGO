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

UENUM(BlueprintType)
enum class EItemType : uint8
{
	BriefCase = 0 UMETA(DisplayName = "BriefCase"),
	Milou = 1 UMETA(DisplayName = "Milou"),
	Hadoc = 2 UMETA(DisplayName = "Hadoc")
};

UCLASS()
class TINTINGO_API ATile : public AActor
{
	GENERATED_BODY()

public:
	ATile();

	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		ETileType _tileType {ETileType::Neutral};

	
	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		bool _walkable = true;

	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		TArray<EItemType> _itemsToSpawn;
		TArray<AItem*> _items;


	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		int32 _itemsNb;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Editor Parameters")
		bool _useEditorTick = true;

	UPROPERTY()
	int32 _row;
	UPROPERTY()
	int32 _column;
	UPROPERTY()
	UMaterialInterface* _walkableMat;
	UPROPERTY()
	UMaterialInterface* _unwalkableMat;
	UPROPERTY()
	UMaterialInterface* _startPosMat;
	UPROPERTY()
	UMaterialInterface* _endPosMat;

	UFUNCTION(BlueprintCallable, CallInEditor)
		void AddItem();

private:
	class UStaticMeshComponent* _staticMeshComponent = nullptr;

	bool _walkableChecker = true;

	ETileType _tileTypeChecker {ETileType::Neutral};
	
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
		void BlueprintEditorTick(float DeltaTime);

};
