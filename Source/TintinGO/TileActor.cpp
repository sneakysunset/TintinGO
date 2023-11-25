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

void ATileActor::ChangeState(UState_TActor* newState)
{
	_currentState_TA->OnStateExit();
	_currentState_TA = newState;
	newState->_tileActor = this;
	_currentState_TA->OnStateEnter();
}

// Called when the game starts or when spawned
void ATileActor::BeginPlay()
{
	Super::BeginPlay();
	_currentState_TA = NewObject<UState_TActor_Neutral>(UState_TActor_Neutral::StaticClass());
}

// Called every frame
void ATileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_currentState_TA->OnStateTick(DeltaTime);
}

