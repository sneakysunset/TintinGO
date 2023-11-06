#pragma once

#include "CoreMinimal.h"

class TINTINGO_API Tile
{
public:
	enum Direction {LEFT, RIGHT, UP, DOWN};
	Tile();
	~Tile();
	float _height;
	TMap<Direction, int32> _adjacentTileIndexs;
};
