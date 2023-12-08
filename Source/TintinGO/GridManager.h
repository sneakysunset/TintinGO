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
	AGridManager();

    static AGridManager* GetInstance();

    UFUNCTION(CallInEditor, Category = "GridManager")
    void InitializeGrid();

    UFUNCTION(CallInEditor, Category = "GridManager")
    void UpdateLinks();

    UFUNCTION()
    ATile* WorldCoordinatesToTilePosition(const FVector& worldCoordinates);

    UPROPERTY(EditAnywhere)
    UBlueprint* _tileBP;

    UFUNCTION()
    void ChangeTile(UBarrier* barrier, ATile* previousTile, ATile* currentTile);

    UFUNCTION()
    void MarkStepsOnGrid(ATile* CenterTile);

    UFUNCTION()
    void SetStepOnAdjacentsRecursive(ATile* tile);
    
    UFUNCTION()
    void SetStepOnAdjacentTile(ATile* tile, FVector2D direction);

    UFUNCTION()
    bool TileIsAvailable(ATile* tile, FVector2D direction);

    UFUNCTION()
    TArray<ATile*> GetPath(ATile* endTile, bool getCurrentTile);

    UFUNCTION()
    ATile* GetNextTileInPath(ATile* tile);

    UFUNCTION()
    ATile* GetTile(int32 i, int32 j);
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool _useEditorTick;
    
    UPROPERTY()
    TArray<FTileArray> _gridTiles;
    
    UPROPERTY()
    TArray<ATileActor_Character_Peruvien*> _peruviens;
    
protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual bool ShouldTickIfViewportsOnly() const override;
    
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
