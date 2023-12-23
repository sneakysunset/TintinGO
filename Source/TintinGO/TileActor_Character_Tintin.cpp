#include "TileActor_Character_Tintin.h"

#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"


ATileActor_Character_Tintin* ATileActor_Character_Tintin::SingletonInstance = nullptr;

ATileActor_Character_Tintin* ATileActor_Character_Tintin::GetInstance() 
{
	return SingletonInstance;
}

ATileActor_Character_Tintin::ATileActor_Character_Tintin()
{
	PrimaryActorTick.bCanEverTick = true;
	SingletonInstance = this;
}

void ATileActor_Character_Tintin::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::SpawnSoundAtLocation(this, S_LevelStart, GetActorLocation());
	
	TInlineComponentArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);

	for (int i = 0; i < Components.Num(); i++)
	{
		 if(Components[i]->GetName() == TEXT("Tintin Throwing"))
		{
			_tintinMeshes.Add(ETintinState::Throwing, Components[i]);
		}
		else if(Components[i]->GetName() == TEXT("Tintin Running"))
		{
			_tintinMeshes.Add(ETintinState::Running, Components[i]);
		}
		else if(Components[i]->GetName() == TEXT("Os"))
		{
			bone = Components[i];
		}
	}

	SetTintinMesh(ETintinState::Running);
}


void ATileActor_Character_Tintin::SetTintinMesh(ETintinState state)
{
	for (auto key : _tintinMeshes)
	{
		if(key.Key == state)
		{
			key.Value->SetVisibility(true);
			if(key.Key == ETintinState::Throwing) bone->SetVisibility(true);
			else bone->SetVisibility(false);
		}
		else
		{
			key.Value->SetVisibility(false);
		}
	}
}

void ATileActor_Character_Tintin::RotateTintinToTargetTile(ATile* targetTile, float DeltaTime)
{
	if(_targetTile != targetTile)
	{
		_targetTile = targetTile;
		_interpolateValue = 0;
		const FVector TargetDirection = _targetTile->GetActorLocation() - GetActorLocation();
		FRotator TargetRotation = TargetDirection.Rotation();
		TargetRotation.Yaw += 90;
		_startRotation = GetActorRotation().Quaternion();
		_endRotation = TargetRotation.Quaternion();
	}

	if(_interpolateValue <= 1)
	{
		_interpolateValue += _rotationThrowSpeed * DeltaTime;
		const FQuat rot =  FQuat::Slerp(_startRotation, _endRotation, _interpolateValue);
		SetActorRotation(rot);
	}
}
