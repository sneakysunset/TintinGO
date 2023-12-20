// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor_Character.h"
#include "Components/SplineComponent.h"
#include "Engine/SplineMeshActor.h"
#include "TileActor_Character_Peruvien.generated.h"

class ASplineActor;

UENUM(BlueprintType)
enum class EPeruvienBehaviour : uint8
{
	Static = 0 UMETA(DisplayName = "Static"),
	Returning = 1 UMETA(DisplayName = "Returning"),
	FollowingTintin = 2 UMETA(DisplayName = "Following Tintin"),
	FollowingMilou = 4 UMETA(DisplayName = "Following Milou"),
	SearchingTintin = 8 UMETA(DisplayName = "SearchingTintin")
};

UCLASS()
class TINTINGO_API ATileActor_Character_Peruvien : public ATileActor_Character
{
	GENERATED_BODY()

	ATileActor_Character_Peruvien();
public:
	UPROPERTY(EditAnywhere)
	TArray<ATile*> PeruvienTilePath;

	virtual void SetUpRotation(EAngle newAngle) override;

	UPROPERTY()
	ATile* _startingTile;

	UPROPERTY()
	EAngle _startingAngle;

	UPROPERTY()
	EAngle _tintinAngle;
	
	UFUNCTION()
	bool Detection(ATile* detectTile) const;

	UPROPERTY(EditAnywhere)
	EPeruvienBehaviour _currentPBehaviour;
	
	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	TArray<ASplineMeshActor*> splineMeshs;

	UPROPERTY(EditAnywhere)
	UBlueprint* splineBP;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* exclamativeMark;
	
	UFUNCTION()
	void SetWidgetVisible(bool isVisible) const;

	UFUNCTION()
	void SetSplinePoints();
	void UpdateSplinePoint();

	UFUNCTION()
	void AddSplinePoint();

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMesh* splineMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UMaterialInterface* splineMaterial;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USplineComponent* PathSpline;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<USplineMeshComponent*> SplineMeshComponents;

	UPROPERTY()
	UStaticMeshComponent* splineStartPoint;
	
	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_detect;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_lostDetect;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_ReachMilou;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_PeruvienDetectTintin;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TSubclassOf<ASplineActor> _splineActor;

	UPROPERTY()
	float _timeToLateInit = .15;

	UPROPERTY()
	bool _hasLateInit;

	UPROPERTY()
	float _timePassed;
	
protected:
	virtual void BeginPlay() override;
	void LateInit();

	virtual void Tick(float DeltaSeconds) override;
};
