#include "TileActor.h"

#include "State_TActor_Neutral.h"

ATileActor::ATileActor()
{
	PrimaryActorTick.bCanEverTick = true;
	_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Cube.Cube"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;
}

void ATileActor::OnEndTask()
{
	this->Destroy();
}

void ATileActor::TriggerBody()
{
	_isTaskOver = true;
}

// Called when the game starts or when spawned
void ATileActor::BeginPlay()
{
	Super::BeginPlay();
	_currentState_TA = new State_TActor_Neutral(this);
}

// Called every frame
void ATileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

