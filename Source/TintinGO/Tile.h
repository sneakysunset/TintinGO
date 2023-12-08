#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class AGridManager;

UENUM(BlueprintType)
enum class ETileType : uint8
{
	Neutral = 0b0000 UMETA(DisplayName = "Neutral"),
	StartingPosition = 0b0001 UMETA(DisplayName = "Starting Position"),
	EndingPosition = 0b0010 UMETA(DisplayName = "Ending Position")
};

UENUM(BlueprintType)
enum class ETileActorType : uint8
{
	Bone = 0 UMETA(DisplayName = "Milou's Bone"),
	Clue = 1 UMETA(DisplayName = "Clue"),
	Peruvien = 2 UMETA(DisplayName = "Peruvien [Ennemy]"),
	Condor = 4 UMETA(DisplayName = "Condor [Ennemy]")
};

UCLASS()
class TINTINGO_API ATile : public AActor
{
	GENERATED_BODY()

public:
	ATile();

	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
		ETileType _tileType {ETileType::Neutral};
	virtual void BeginPlay() override;
	
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
		TArray<ETileActorType> _TileItems;
	
	UPROPERTY()
		TArray<ATileActor*> _tileActors;

	UFUNCTION(CallInEditor , Category = "Spawn TileActors")
		void AddTileActors();
	
	UPROPERTY(EditAnywhere, Category = "Spawn TileActors")
		UBlueprint* _milouBoneBP;
	UPROPERTY(EditAnywhere, Category = "Spawn TileActors")
		UBlueprint* _peruvienBP;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Editor Parameters")
		bool _useEditorTick = true;

	UPROPERTY()
	int32 _row;
	UPROPERTY()
	int32 _column;
	UPROPERTY(EditAnywhere)
	int32 _step;
	UPROPERTY(EditAnywhere, Category = "TileMaterials")
	UMaterialInterface* _walkableMat;
	UPROPERTY(EditAnywhere, Category = "TileMaterials")
	UMaterialInterface* _unwalkableMat;
	UPROPERTY(EditAnywhere, Category = "TileMaterials")
	UMaterialInterface* _startPosMat;
	UPROPERTY(EditAnywhere, Category = "TileMaterials")
	UMaterialInterface* _endPosMat;
	UPROPERTY(EditAnywhere, Category = "TileMaterials")
	UMaterialInterface* _HighlightedMat;
	UPROPERTY(EditAnywhere, Category = "TileMaterials")
	UMaterialInterface* _HighlightedPathMat;
	void SetHighlighted(bool toHightlight) const;
	void SetHighlightedPath(bool toHightlight) const;
	UFUNCTION()
	FVector GetTileActorPosition(ATileActor* tileActor);
	float _positionCircleRadius = 1;
	AGridManager* _gridManager;
	UFUNCTION(BlueprintCallable, CallInEditor)
	void RefreshLinks();

private:
	class UStaticMeshComponent* _staticMeshComponent = nullptr;

	bool _walkableChecker = true;

	UMaterialInstanceDynamic* DynamicMat(UMaterialInterface* mat);

	ETileType _tileTypeChecker {ETileType::Neutral};
	
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
		void BlueprintEditorTick(float DeltaTime);

	void AddTintin();
	UPROPERTY(EditAnywhere)
	UBlueprint* _tintinBP;
	UPROPERTY(EditAnywhere)
	UBlueprint* _milouBP;
};
