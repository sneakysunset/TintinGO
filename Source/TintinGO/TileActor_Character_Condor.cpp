

#include "TileActor_Character_Condor.h"

ATileActor_Character_Condor::ATileActor_Character_Condor()
{
	PrimaryActorTick.bCanEverTick = true;
	isWaitLastRound = true;
}

void ATileActor_Character_Condor::SetUpRotation(EAngle newAngle)
{
	angle = newAngle;
	float angleV = 0;
	switch(angle)
	{
	case EAngle::Right: angleV = 90; break;
	case EAngle::Up: angleV = 0; break;
	case EAngle::Left: angleV = 270; break;
	case EAngle::Down: angleV = 180; break;
	}
	SetActorRotation(FQuat::MakeFromEuler(FVector::UpVector * (angleV + _baseAngleOffset)).Rotator());
}

FRotator ATileActor_Character_Condor::GetTargetRotation(EAngle newAngle)
{
	angle = newAngle;
	float angleV = 0;
	switch(angle)
	{
	case EAngle::Right: angleV = 90; break;
	case EAngle::Up: angleV = 0; break;
	case EAngle::Left: angleV = 270; break;
	case EAngle::Down: angleV = 180; break;
	}
	return FQuat::MakeFromEuler(FVector::UpVector * (angleV + _baseAngleOffset)).Rotator();
}