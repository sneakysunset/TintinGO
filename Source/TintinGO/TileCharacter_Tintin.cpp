#include "TileCharacter_Tintin.h"

ATileCharacter_Tintin* ATileCharacter_Tintin::SingletonInstance = nullptr;

ATileCharacter_Tintin* ATileCharacter_Tintin::GetInstance() 
{
	return SingletonInstance;
}

ATileCharacter_Tintin::ATileCharacter_Tintin()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;

	_currentTile = nullptr;
	currentMilouBonesNb = 0;
	currentHaddockBottleNb = 0;
}