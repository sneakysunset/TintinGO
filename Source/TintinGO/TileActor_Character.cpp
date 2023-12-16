#include "TileActor_Character.h"


void ATileActor_Character::SetUpRotation(EAngle newAngle)
{
	angle = newAngle;
	float angleV = 0;
	switch(angle)
	{
	case EAngle::Right: break;
	case EAngle::Up: angleV = 90; break;
	case EAngle::Left: angleV = 180; break;
	case EAngle::Down: angleV = 270; break;
	}
	SetActorRotation(FQuat::MakeFromEuler(FVector::UpVector * (angleV + _baseAngleOffset)).Rotator());
}

void ATileActor_Character::OnEndTask()
{
	Super::OnEndTask();
}

void ATileActor_Character::BeginPlay()
{
	Super::BeginPlay();
}
