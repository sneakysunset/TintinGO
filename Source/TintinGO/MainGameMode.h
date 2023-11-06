#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tile.h"
#include "MainGameMode.generated.h"

UCLASS()
class TINTINGO_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
public :
	AMainGameMode();
	virtual ~AMainGameMode() = default;
	UFUNCTION(BlueprintPure, Category = "GridGeneration")
		virtual int32 GetRows() const;
	UFUNCTION(BlueprintPure, Category = "GridGeneration")
		virtual int32 GetColumns() const;
	UFUNCTION(BluePrintCallable, Category = "GridGeneration")
		virtual void SetRows(int32 rows);
	UFUNCTION(BluePrintCallable, Category = "GridGeneration")
		virtual void SetColumns(int32 columns);

	virtual void StartPlay();

	UFUNCTION(BlueprintNativeEvent, Category = "GridGeneration", DisplayName = "Start Play")
		void StartPlayEvent();
	//UPROPERTY(EditAnywhere)
	//static int32 _rows;
	//UPROPERTY(EditAnywhere)
	//static int32 _columns;
	//UPROPERTY(EditAnywhere)
	//static float _tileWidth;
	//static TArray<TArray<Tile*>> _tileGrid;
	//static void GenerateGrid();
};
