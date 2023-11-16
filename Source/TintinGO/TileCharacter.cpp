#include "TileCharacter.h"
// Sets default values
ATileCharacter::ATileCharacter()
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>meshFinder(TEXT("/Engine/BasicShapes/Capsule.Capsule"));
	_staticMeshComponent->SetStaticMesh(meshFinder.Object);

	RootComponent = _staticMeshComponent;
}

// Called when the game starts or when spawned
void ATileCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATileCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATileCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATileCharacter::PlaceBody(/*ATile* tile*/)
{

}

void ATileCharacter::TriggerBody()
{
}

