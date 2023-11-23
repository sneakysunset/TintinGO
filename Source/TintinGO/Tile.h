#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlacableBody.h"
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
	bool _rightLink = true;
	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
	bool _leftLink = true;
	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
	bool _upLink = true;
	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
	bool _downLink = true;
	
	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		TArray<EPlacableBodyType> _placableBodies;

	UPROPERTY()
	TArray<AItem*> ItemsList;

	UPROPERTY()
	TArray<ATileCharacter*> TileCharacterList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Editor Parameters")
		bool _useEditorTick = true;

	UPROPERTY()
	int32 _row;
	UPROPERTY()
	int32 _column;
	UPROPERTY(EditAnywhere)
	int32 _step;
	UPROPERTY()
	UMaterialInterface* _walkableMat;
	UPROPERTY()
	UMaterialInterface* _unwalkableMat;
	UPROPERTY()
	UMaterialInterface* _startPosMat;
	UPROPERTY()
	UMaterialInterface* _endPosMat;
	UPROPERTY()
	UMaterialInterface* _HighlightedMat;
	UPROPERTY()
	UMaterialInterface* _HighlightedPathMat;
	void SetHighlighted(bool toHightlight);
	void SetHighlightedPath(bool toHightlight);
	UFUNCTION(BlueprintCallable, CallInEditor)
		void AddPlacableBodies();
private:
	class UStaticMeshComponent* _staticMeshComponent = nullptr;

	bool _walkableChecker = true;

	ETileType _tileTypeChecker {ETileType::Neutral};
	
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
		void BlueprintEditorTick(float DeltaTime);

	
};
