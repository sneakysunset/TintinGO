#include "TileActor_Character_Peruvien.h"

#include "MainGameMode.h"
#include "SplineActor.h"
#include "Tile.h"
#include "Components/SplineMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


ATileActor_Character_Peruvien::ATileActor_Character_Peruvien(): _startingTile(nullptr), _startingAngle(),
                                                                _currentPBehaviour()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATileActor_Character_Peruvien::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParams;
	FVector Location = FVector(0.0f, 0.0f, 0.0f); // Example location
	FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f); // Example rotation

	ASplineActor* actor = GetWorld()->SpawnActor<ASplineActor>(_splineActor, Location, Rotation, SpawnParams);
	PathSpline = actor->MySplineComponent;
	
	_currentPBehaviour = EPeruvienBehaviour::Static;
	PlayerController = GetWorld()->GetFirstPlayerController();
	
	TInlineComponentArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);

	for (int i = 0; i < Components.Num(); i++)
	{
		if(Components[i]->GetName() == "Exclamation Mark")
		{
			exclamativeMark = Components[i];
			exclamativeMark->SetVisibility(false);
		}
		else if(Components[i]->GetName() == "Pathfind")
		{
			splineStartPoint = Components[i];
		}
	}
}

void ATileActor_Character_Peruvien::LateInit()
{
	_gameManager->SetTilesPeruvienColor(true, angle, GetCurrentTile());
}

void ATileActor_Character_Peruvien::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	if(IsValid(CameraManager) && IsValid(exclamativeMark))
	{
		const FVector CameraLocation = CameraManager->GetCameraLocation();

		FVector Direction = CameraLocation - exclamativeMark->GetComponentLocation();
		Direction.Z = 0;
		Direction.Normalize();

		FRotator LookAtRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		//LookAtRotation.Yaw += 90.0f;

		exclamativeMark->SetWorldRotation(LookAtRotation);
	}

	if(!_hasLateInit)
	{
		_timePassed += DeltaSeconds;
		if(_timePassed > _timeToLateInit)
		{
			_hasLateInit = true;
			LateInit();
		}
	}
}

void ATileActor_Character_Peruvien::SetUpRotation(EAngle newAngle)
{
	angle = newAngle;
	float angleV = 0;
	switch(angle)
	{
	case EAngle::Right: angleV = 180; break;
	case EAngle::Up: angleV = 90; break;
	case EAngle::Left: angleV = 0; break;
	case EAngle::Down: angleV = 270; break;
	}
	SetActorRotation(FQuat::MakeFromEuler(FVector::UpVector * (angleV + _baseAngleOffset)).Rotator());
}

bool ATileActor_Character_Peruvien::Detection(ATile* detectTile) const
{
	if(detectTile == GetCurrentTile()) return true;
	int32 distance;
	switch(angle)
	{
		case EAngle::Right:
			distance =detectTile->_column - GetCurrentTile()->_column;
			if(distance >= 0 && distance <= 2 && detectTile->_row == GetCurrentTile()->_row)
			{
				if(GetCurrentTile()->_rightLink && detectTile->_leftLink) return true;
			}
		return false;
		case EAngle::Left:
			distance = detectTile->_column - GetCurrentTile()->_column;
			if(distance <= 0 && distance >= -2 && detectTile->_row == GetCurrentTile()->_row)
			{
				if(GetCurrentTile()->_leftLink && detectTile->_rightLink) return true;
			}
		return false;
		case EAngle::Up:
			distance = detectTile->_row - GetCurrentTile()->_row;
			if(distance >= 0 && distance <= 2 && detectTile->_column == GetCurrentTile()->_column)
			{
				if(GetCurrentTile()->_upLink && detectTile->_downLink) return true;
			}
		return false;
		case EAngle::Down:
			distance = detectTile->_row - GetCurrentTile()->_row;
			if(distance <= 0 && distance >= -2 && detectTile->_column == GetCurrentTile()->_column)
			{
				if(GetCurrentTile()->_downLink && detectTile->_upLink) return true;
			}
			return false;
		default:
			return false;
	}
}

void ATileActor_Character_Peruvien::SetSplinePoints()
{
	// Create a spline mesh component for each segment of the spline
	for (int32 i = 0; i < PathSpline->GetNumberOfSplinePoints() - 1; ++i)
	{
		USplineMeshComponent* SplineMeshComponent = NewObject<USplineMeshComponent>(this);
		SplineMeshComponent->RegisterComponent();
		SplineMeshComponent->SetMobility(EComponentMobility::Movable);
		SplineMeshComponent->AttachToComponent(PathSpline, FAttachmentTransformRules::KeepRelativeTransform);
		SplineMeshComponent->SetStaticMesh(splineMesh);
		SplineMeshComponent->SetMaterial(0, splineMaterial);
		SplineMeshComponent->SetStartScale(.03f * FVector2D::One());
		SplineMeshComponent->SetEndScale(.03f * FVector2D::One());
		// Set the spline points for this segment
		FVector Start = PathSpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		FVector StartTangent = PathSpline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World);
		FVector End = PathSpline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::World);
		FVector EndTangent = PathSpline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::World);

		SplineMeshComponent->SetStartAndEnd(Start, StartTangent, End, EndTangent);
		SplineMeshComponents.Add(SplineMeshComponent);
		// Other settings for the spline mesh (material, etc.) can be configured here
	}
}

void ATileActor_Character_Peruvien::UpdateSplinePoint()
{
	//PathSpline->SetLocationAtSplinePoint(0, );
}

void ATileActor_Character_Peruvien::AddSplinePoint()
{
	PathSpline->ClearSplinePoints();
	for (auto meshComp : SplineMeshComponents)
	{
		meshComp->DestroyComponent();
	}
	SplineMeshComponents.Empty(true);
	bool firstTile = true;
	for (auto tile : PeruvienTilePath)
	{
		if(firstTile)
		{
			firstTile = false;
			FVector location = FVector(tile->GetActorLocation());
			PathSpline->AddSplinePoint(location, ESplineCoordinateSpace::World, true);
			continue;
		}
		if(tile != GetCurrentTile())
		{
			FVector location = FVector(tile->GetActorLocation() + FVector::UpVector * 40);
			PathSpline->AddSplinePoint(location, ESplineCoordinateSpace::World, true);
		}
	}
	PathSpline->AddSplinePoint( splineStartPoint->GetComponentLocation() ,ESplineCoordinateSpace::World, true);
	SetSplinePoints();
}

void ATileActor_Character_Peruvien::SetWidgetVisible(bool isVisible) const
{
	if(isVisible && !exclamativeMark->IsVisible())
	{
		UGameplayStatics::SpawnSoundAtLocation(this, S_detect, GetActorLocation());
		exclamativeMark->SetVisibility(true);
	}
	else if(!isVisible && exclamativeMark->IsVisible())
	{
		UGameplayStatics::SpawnSoundAtLocation(this, S_lostDetect, GetActorLocation());
		exclamativeMark->SetVisibility(false);
	}
}
