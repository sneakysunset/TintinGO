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
	UPROPERTY(EditAnywhere)
	static int32 _rows;
	UPROPERTY(EditAnywhere)
	static int32 _columns;
	UPROPERTY(EditAnywhere)
	static float _tileWidth;
	static TArray<TArray<Tile*>> _tileGrid;
	static void GenerateGrid();
};
