#pragma once

#include "CoreMinimal.h"
#include "TileActor_Character.h"
#include "TileActor_MilouBone.h"
#include "GameFramework/Actor.h"
class AGridManager;
#include "Tile.generated.h"



UENUM(BlueprintType)
enum class ETileType : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	StartingPosition UMETA(DisplayName = "Starting Position"),
	EndingPosition UMETA(DisplayName = "Ending Position"),
	NestPosition UMETA(DisplayName = "Nest")
};

UENUM(BlueprintType)
enum class ENestDirection : uint8
{
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right"),
	Top UMETA(DisplayName = "Top"),
	Down UMETA(DisplayName = "Down")
};

UENUM(BlueprintType)
enum class ETileActorType : uint8
{
	Bone UMETA(DisplayName = "Milou's Bone"),
	Clue UMETA(DisplayName = "Clue"),
	Peruvien UMETA(DisplayName = "Peruvien [Ennemy]"),
	Condor UMETA(DisplayName = "Condor [Ennemy]")
};

USTRUCT(BlueprintType)
struct FItemToSpawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETileActorType actorType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAngle angle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 clueIndex;
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
	ENestDirection _nestDirection = ENestDirection::Left;
	
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
	TArray<FItemToSpawn> _TileItems;
	
	UPROPERTY()
	TArray<ATileActor*> _tileActors;

	UFUNCTION(CallInEditor , Category = "Spawn TileActors")
	void AddTileActors();
	
	UPROPERTY(EditAnywhere, Category = "Spawn TileActors")
	UBlueprint* _milouBoneBP;
	
	UPROPERTY(EditAnywhere, Category = "Spawn TileActors")
	UBlueprint* _peruvienBP;

	UPROPERTY(EditAnywhere, Category = "Spawn TileActors")
	UBlueprint* _clueBP;

	UFUNCTION()
	void SpawnMilouBone();

	UPROPERTY()
	ATileActor_MilouBone* milouBoneToDrop;
	
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
	UMaterialInterface* _nestMat;
	
	UPROPERTY(EditAnywhere, Category = "TileMaterials")
	UMaterialInterface* _HighlightedMat;
	
	UPROPERTY(EditAnywhere, Category = "TileMaterials")
	UMaterialInterface* _HighlightedPathMat;

	UPROPERTY(EditAnywhere, Category = "TileMaterials")
	UMaterialInterface* _InBoneRangeMat;
	
	UFUNCTION()
	void SetHighlighted(bool toHightlight);

	UFUNCTION()
	void SetTilesInBoneRangeMat(bool toBone);

	UFUNCTION()
	void SetHighlightedPath(bool toHightlight);
	
	UFUNCTION()
	FVector GetTileActorPosition(ATileActor* tileActor);
	
	UFUNCTION()
	void RefreshTileBackgroundRenderer(int alpha);

	UPROPERTY()
	float _positionCircleRadius = 1;

	UPROPERTY()
	AGridManager* _gridManager;
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void RefreshLinks();

private:
	class UStaticMeshComponent* _staticMeshComponent = nullptr;

	UPROPERTY()
	bool _walkableChecker = true;

	UFUNCTION()
	UMaterialInstanceDynamic* DynamicMat(UMaterialInterface* mat, int backgroundAlpha) const;
	
	UPROPERTY()
	int _currentBackgroundAlpha;

	UPROPERTY()
	ETileType _tileTypeChecker {ETileType::Neutral};

	UFUNCTION()
	virtual bool ShouldTickIfViewportsOnly() const override;

	UFUNCTION(CallInEditor)
	void BlueprintEditorTick(float DeltaTime);
	
	UFUNCTION()
	void AddTintin();

	void AddCondor();

	UPROPERTY(EditAnywhere)
	UBlueprint* _tintinBP;
	
	UPROPERTY(EditAnywhere)
	UBlueprint* _milouBP;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBlueprint* _condorBP;
};
