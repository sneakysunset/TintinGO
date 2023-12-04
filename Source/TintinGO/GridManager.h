#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
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
    UPROPERTY(EditAnywhere)
    UBlueprint* _tintinBP;
    UPROPERTY(EditAnywhere)
    UBlueprint* _milouBP;
    void MarkStepsOnGrid(ATile* CenterTile);
    void SetStepOnAdjacentsRecursive(ATile* tile);
    void SetStepOnAdjacentTile(ATile* tile, FVector2D direction);
    bool TileIsAvailable(ATile* tile, FVector2D direction);
    TArray<ATile*> GetPath(ATile* endTile);
    ATile* GetNextTileInPath(ATile* tile);
    ATile* GetTile(int32 i, int32 j);
    ATile* _endTile;
    ATile* GetEndTile() const{return _endTile;}
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool _useEditorTick;
    // Add more functions as needed
    UPROPERTY()
    TArray<FTileArray> _gridTiles;
    UPROPERTY()
    TArray<ATileActor_Character_Peruvien*> _peruviens;

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
