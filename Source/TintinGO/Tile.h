#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "TileCharacter.h"
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
		ETileType _tileType {ETileType::Neutral};

	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		bool _walkable = true;

	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		TArray<EItemType> _itemsType;

	TArray<AItem*> _itemsList;

	UPROPERTY(EditAnywhere, Category = "TileParameters")
		TArray<ECharacterType> _ennemies;

	TArray<ATileCharacter*> _ennemiesList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Editor Parameters")
		bool _useEditorTick = true;

	int32 _row;
	int32 _column;
	UMaterialInterface* _walkableMat;
	UMaterialInterface* _unwalkableMat;
	UMaterialInterface* _startPosMat;
	UMaterialInterface* _endPosMat;

	UFUNCTION(BlueprintCallable, CallInEditor)
		void AddItem();

	UFUNCTION(BlueprintCallable, CallInEditor)
		void AddCharacter();

private:
	class UStaticMeshComponent* _staticMeshComponent = nullptr;

	bool _walkableChecker = true;

	ETileType _tileTypeChecker {ETileType::Neutral};
	
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
		void BlueprintEditorTick(float DeltaTime);

};
