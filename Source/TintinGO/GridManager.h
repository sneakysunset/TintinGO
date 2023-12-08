#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "Barrier.h"
#include "GridManager.generated.h"

class ATileActor_Character_Peruvien;

USTRUCT(BlueprintType)
struct FTileArray
{
    GENERATED_BODY()

    UPROPERTY()
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

    UFUNCTION(CallInEditor, Category = "GridManager")
        void InitializeGrid();

    UFUNCTION(CallInEditor, Category = "GridManager")
    void UpdateLinks();
    
    ATile* WorldCoordinatesToTilePosition(const FVector& worldCoordinates);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual bool ShouldTickIfViewportsOnly() const override;

    UPROPERTY(EditAnywhere)
    UBlueprint* _tileBP;
    
    void ChangeTile(UBarrier* barrier, ATile* previousTile, ATile* currentTile);
    void MarkStepsOnGrid(ATile* CenterTile);
    void SetStepOnAdjacentsRecursive(ATile* tile);
    void SetStepOnAdjacentTile(ATile* tile, FVector2D direction);
    bool TileIsAvailable(ATile* tile, FVector2D direction);

    TArray<ATile*> GetPath(ATile* endTile);
    ATile* GetNextTileInPath(ATile* tile);
    ATile* GetTile(int32 i, int32 j);
    ATile* GetEndTile() const{return _endTile;}
    
    ATile* _endTile;
    ATile* _nest1Tile;
    ATile* _endNest1Tile;
    ATile* _nest2Tile;
    ATile* _endNest2Tile;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool _useEditorTick;
    // Add more functions as needed
    UPROPERTY()
    TArray<FTileArray> _gridTiles;
    UPROPERTY()
    TArray<ATileActor_Character_Peruvien*> _peruviens;
    UPROPERTY()
    TArray<ATileActor_Character_Condor*> _condors;

private:
    static AGridManager* SingletonInstance;
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
        int32 _rows;
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
        int32 _columns;
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
        double _tileWidth;

    UFUNCTION(CallInEditor, Category = "Events")
        void BlueprintEditorTick(float DeltaTime);

};
