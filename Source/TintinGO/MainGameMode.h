#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Barrier.h"
#include "GridManager.h"
#include "MainGameMode.generated.h"

class ATileActor_Character_Peruvien;
class ATileActor_Character_Condor;
class UState;

DECLARE_DYNAMIC_DELEGATE(FOnClickDelegate);
DECLARE_DYNAMIC_DELEGATE(FUIMilouClick);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBoneConsumed, int32, NewBoneNumber, FColor, DisabledColor);


USTRUCT(BlueprintType)
struct FTileArray
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<class ATile*> Tiles;
};

UCLASS()
class TINTINGO_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AMainGameMode();
	virtual ~AMainGameMode() override;

public:	
    UFUNCTION(CallInEditor, Category = "GridManager")
    void InitializeGrid();

    UFUNCTION(CallInEditor, Category = "GridManager")
    void UpdateLinks();

    UFUNCTION()
    ATile* WorldCoordinatesToTilePosition(const FVector& worldCoordinates);

    UFUNCTION()
        void LateInit();

	float timePassed = 0;
	bool hasLateInit = false;

    UPROPERTY(EditAnywhere)
    UBlueprint* _tileBP;

	UPROPERTY()
	APlayerController* pc;

	UFUNCTION()
    static void ChangeTile(UBarrier* barrier, ATile* previousTile, ATile* currentTile);

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
    ATile* GetEndTile() const{return _endTile;}

    UPROPERTY()
    ATile* _endTile;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool _useEditorTick;


    UPROPERTY()
    TArray<FTileArray> _gridTiles;
    
    UPROPERTY()
    TArray<ATileActor_Character_Peruvien*> _peruviens;

    UPROPERTY()
    TArray<ATileActor_Character_Condor*> _condors;

    UPROPERTY()
    TArray<ATileActor_Clue*> _clues;
    
    UPROPERTY()
    TArray<ATile*> _nests;
    
protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    virtual bool ShouldTickIfViewportsOnly() const override;

public:
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
    int32 _rows;
    
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
    int32 _columns;

    UPROPERTY(EditAnywhere, Category = "Grid Generation")
    double _tileWidth;

    UFUNCTION(CallInEditor, Category = "Events")
    void BlueprintEditorTick(float DeltaTime);

	UFUNCTION()
    void GameOver() const;

	UFUNCTION()
	void OnWin() const;

	FOnClickDelegate OnClickD;
    FUIMilouClick OnMilouBoneClick;
    FOnBoneConsumed OnBoneConsumed;

    UPROPERTY()
    UState* _currentStateType;
	
    UFUNCTION()
    void StateChange(UState* NewState);
	
    UPROPERTY(EditAnywhere, Category = "Milou Parameters")
    int32 _milouBoneThrowRange;
	
    UPROPERTY()
    int32 _milouBonesNumber;
	
    UFUNCTION(BlueprintCallable)
    void ReceiveMilouUIClick();

    UPROPERTY(EditAnywhere)
    int32 _clueNumber;

    UPROPERTY(EditAnywhere)
    float _inTileMoveSpeed;
	
    UPROPERTY(EditAnywhere)
    float _rotateSpeed;

    UPROPERTY(EditAnywhere)
    EAngle _tintinAngle;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCoreUI> YourWidgetClass;

	UPROPERTY()
	UCoreUI* _coreUI;

	UFUNCTION()
	void ChangeTextValue(int32 newValue, FColor DisabledColor);
};
