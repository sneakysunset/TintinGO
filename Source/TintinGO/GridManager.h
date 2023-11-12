// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.h"
#include "GridManager.generated.h"
UCLASS()
class TINTINGO_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridManager();

    UFUNCTION(BlueprintCallable, Category = "Grid")
        void InitializeGrid();

    UFUNCTION(BlueprintCallable, Category = "Grid")
        void OccupyCell(int32 Row, int32 Col);

    UFUNCTION(BlueprintCallable, Category = "Grid")
        void ReleaseCell(int32 Row, int32 Col);

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual bool ShouldTickIfViewportsOnly() const override;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
      bool _initializeGrid;
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        bool _useEditorTick;
    // Add more functions as needed
    TArray<TArray<ATile*>> _gridTiles;

private:

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

    UFUNCTION(CallInEditor, Category = "Events")
        void BlueprintEditorTick(float DeltaTime);
};
