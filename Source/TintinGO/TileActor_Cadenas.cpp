#include "TileActor_Cadenas.h"


ATileActor_Cadenas::ATileActor_Cadenas()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor_Cadenas::BeginPlay()
{
	Super::BeginPlay();
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	for (const auto Mesh : Components)
	{
		if(Mesh->GetName() == "Mesh")
		{
			_staticMeshComponent = Mesh;
			_startHeight = _staticMeshComponent->GetComponentLocation().Z;
			_endHeight = _startHeight + _heightToGoUp;
		}
	}
}

void ATileActor_Cadenas::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CadenasAnimation(DeltaSeconds);
}

void ATileActor_Cadenas::UnlockCadenas() const
{
	_staticMeshComponent->SetVisibility(false);
}

void ATileActor_Cadenas::CadenasAnimation(float DeltaSeconds)
{
	_interpolateValue += _animationSpeed * DeltaSeconds;
	if(_interpolateValue >= 1) _interpolateValue = 0;
	const FVector position = FVector(_staticMeshComponent->GetComponentLocation().X, _staticMeshComponent->GetComponentLocation().Y, FMath::Lerp(_startHeight, _endHeight, _animCurve->FloatCurve.Eval(_interpolateValue)));
	_staticMeshComponent->SetWorldLocation(position);
}
