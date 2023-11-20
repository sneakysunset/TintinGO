#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "TileCharacter.h"
#include "TileCharacter_Tintin.generated.h"


UCLASS()
class TINTINGO_API ATileCharacter_Tintin : public ATileCharacter
{
	GENERATED_BODY()
	

public:
	static ATileCharacter_Tintin* GetInstance();
	static ATileCharacter_Tintin* SingletonInstance;
	ATile* _currentTile;
	float speed;
};