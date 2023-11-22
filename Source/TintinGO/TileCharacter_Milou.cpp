#include "TileCharacter_Milou.h"

ATileCharacter_Milou* ATileCharacter_Milou::SingletonInstance = nullptr;

ATileCharacter_Milou::ATileCharacter_Milou()
{
	PrimaryActorTick.bCanEverTick = true;
	SingletonInstance = this;	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;
	_currentTile = nullptr;
}

ATileCharacter_Milou* ATileCharacter_Milou::GetInstance()
{
	return SingletonInstance;
}
