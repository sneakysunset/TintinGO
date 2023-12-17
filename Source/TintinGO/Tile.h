#pragma once

#include "CoreMinimal.h"
#include "TileActor_Character.h"
#include "TileActor_MilouBone.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class ATileActor_MilouBone;
class AGridManager;
class ATileActor_Character_Milou;
class ATileActor_Character_Tintin;
class ATileActor_Character_Peruvien;
class ATileActor_Character_Condor;
class ATileActor_Clue;
class ATileActor_MilouBone;


UENUM(BlueprintType)
enum class ETileType : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	StartingPosition UMETA(DisplayName = "Starting Position"),
	EndingPosition UMETA(DisplayName = "Ending Position"),
	NestPosition UMETA(DisplayName = "Nest")
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
	ETileActorType actorType = ETileActorType::Bone;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAngle angle = EAngle::Up;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 clueIndex = 0;
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
	EAngle _nestDirection = EAngle::Left;
	
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

	UPROPERTY(EditAnywhere, Category = "Tile Parameters")
	EAngle _tintinAngle;
	
	UPROPERTY()
	TArray<ATileActor*> _tileActors;

	UPROPERTY()
	AGridManager* _gridManager;
	
	UFUNCTION(CallInEditor , Category = "Spawn TileActors")
	void AddTileActors();
	
	UFUNCTION()
	void SpawnMilouBone();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Editor Parameters")
	bool _useEditorTick = true;

	UPROPERTY()
	int32 _row;
	
	UPROPERTY()
	int32 _column;
	
	UPROPERTY(EditAnywhere)
	int32 _step;
	
	UPROPERTY(EditDefaultsOnly, Category = "TileMaterials")
	UMaterialInterface* _walkableMat;
	
	UPROPERTY(EditDefaultsOnly, Category = "TileMaterials")
	UMaterialInterface* _unwalkableMat;
	
	UPROPERTY(EditDefaultsOnly, Category = "TileMaterials")
	UMaterialInterface* _startPosMat;
	
	UPROPERTY(EditDefaultsOnly, Category = "TileMaterials")
	UMaterialInterface* _endPosMat;
	
	UPROPERTY(EditDefaultsOnly, Category = "TileMaterials")
	UMaterialInterface* _nestMat;
	
	UPROPERTY(EditDefaultsOnly, Category = "TileMaterials")
	UMaterialInterface* _HighlightedMat;
	
	UPROPERTY(EditDefaultsOnly, Category = "TileMaterials")
	UMaterialInterface* _HighlightedPathMat;

	UPROPERTY(EditDefaultsOnly, Category = "TileMaterials")
	UMaterialInterface* _InBoneRangeMat;

	UPROPERTY(EditDefaultsOnly, Category = "TileMaterials")
	USoundBase* _Sound_OnTileHover;

	UPROPERTY(EditDefaultsOnly, Category = "TileMaterials")
	USoundBase* _Sound_OnTileClick;


	
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
	AMainGameMode* _gameManager;
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void RefreshLinks();

private:
	UPROPERTY()
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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileActor_Character_Tintin> _tintinBP;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileActor_Character_Milou> _milouBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileActor_Character_Condor> _condorBP;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileActor_MilouBone> _milouBoneBP;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileActor_Character_Peruvien> _peruvienBP;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATileActor_Clue> _clueBP;
	
protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

};
