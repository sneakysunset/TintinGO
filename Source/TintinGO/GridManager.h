#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

class AMainGameMode;

UCLASS()
class TINTINGO_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridManager();

    UFUNCTION(CallInEditor, Category = "GridManager")
    void InitializeGrid();

    UFUNCTION(CallInEditor, Category = "GridManager")
    void UpdateLinks();

    UPROPERTY(EditAnywhere)
    UBlueprint* _tileBP;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    bool _useEditorTick;


protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

    virtual bool ShouldTickIfViewportsOnly() const override;

private:
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
    int32 _rows;
    
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
    int32 _columns;

    UPROPERTY(EditAnywhere, Category = "Grid Generation")
    double _tileWidth;

    UFUNCTION(CallInEditor, Category = "Events")
    void BlueprintEditorTick(float DeltaTime);

	UPROPERTY()
	AMainGameMode* _gameManager;
};
