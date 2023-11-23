#include "TileCharacter_Tintin.h"

ATileCharacter_Tintin* ATileCharacter_Tintin::SingletonInstance = nullptr;

ATileCharacter_Tintin* ATileCharacter_Tintin::GetInstance() 
{
	return SingletonInstance;
}

ATileCharacter_Tintin::ATileCharacter_Tintin()
{
	PrimaryActorTick.bCanEverTick = true;
	SingletonInstance = this;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;

	_currentTile = nullptr;
	currentMilouBonesNb = 0;
	currentHaddockBottleNb = 0;
}

void ATileCharacter_Tintin::CheckTileItems()
{
	check(_currentTile);
	for (AItem* item : _currentTile->ItemsList)
	{
		item->TriggerBody();
	}
}
