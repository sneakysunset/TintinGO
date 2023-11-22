#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "GridManager.generated.h"

USTRUCT(BlueprintType)
struct FTileArray
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<class ATile*> Tiles;
};

UCLASS()
class TINTINGO_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridManager();

    static AGridManager* GetInstance();

    UFUNCTION(BlueprintCallable, Category = "Grid")
        void InitializeGrid();

    ATile* WorldCoordinatesToTilePosition(const FVector& worldCoordinates);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual bool ShouldTickIfViewportsOnly() const override;

    void MarkStepsOnGrid(ATile* CenterTile);
    void SetStepOnAdjacentsRecursive(ATile* tile);
    void SetStepOnAdjacentTile(ATile* tile, FVector2D direction);
    bool TileIsAvailable(ATile* tile, FVector2D direction);
    TArray<ATile*> GetPath(ATile* endTile);
    ATile* GetNextTileInPath(ATile* tile);
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
      bool _initializeGrid;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool _useEditorTick;
    // Add more functions as needed
    UPROPERTY()
    TArray<FTileArray> _gridTiles;

private:
    static AGridManager* SingletonInstance;
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
        int32 _rows;
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
        int32 _columns;
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
        double _tileWidth;
    UPROPERTY(EditAnywhere, Category = "TileMaterials")
        UMaterialInterface* _walkable_TileMaterial;
    UPROPERTY(EditAnywhere, Category = "TileMaterials")
        UMaterialInterface* _startPos_TileMaterial;
    UPROPERTY(EditAnywhere, Category = "TileMaterials")
        UMaterialInterface* _endPos_TileMaterial;
    UPROPERTY(EditAnywhere, Category = "TileMaterials")
        UMaterialInterface* _unwalkable_TileMaterial;
    UPROPERTY(EditAnywhere, Category = "TileMaterials")
        UMaterialInterface* _highlighted_TileMaterial;

    UFUNCTION(CallInEditor, Category = "Events")
        void BlueprintEditorTick(float DeltaTime);
};
