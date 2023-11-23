#include "Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;
}

void AItem::BeginPlay()
{
    Super::BeginPlay();
}

void AItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AItem::OnTriggered()
{

}

void AItem::PlaceBody()
{
}

void AItem::TriggerBody()
{
	isTaskOver = true;
}


void AItem::OnEndTask()
{
	this->Destroy();
}

