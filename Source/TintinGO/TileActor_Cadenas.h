#pragma once

#include "CoreMinimal.h"
#include "TileActor.h"
#include "TileActor_Cadenas.generated.h"

UCLASS()
class TINTINGO_API ATileActor_Cadenas : public ATileActor
{
	GENERATED_BODY()

	ATileActor_Cadenas();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
public:
	UFUNCTION()
	void UnlockCadenas() const;

	UFUNCTION()
	void CadenasAnimation(float DeltaSeconds);
	
	UPROPERTY()
	UStaticMeshComponent* _staticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	float _heightToGoUp;

	UPROPERTY(EditDefaultsOnly)
	float _animationSpeed;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* _animCurve;
	
	UPROPERTY()
	float _startHeight;

	UPROPERTY()
	float _endHeight;
	
	UPROPERTY()
	float _interpolateValue;
};
