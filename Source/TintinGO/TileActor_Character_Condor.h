#pragma once

#include "CoreMinimal.h"
#include "TileActor_Character.h"
#include "TileActor_Character_Condor.generated.h"

UCLASS()
class TINTINGO_API ATileActor_Character_Condor : public ATileActor_Character
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
	ATileActor_Character_Condor();
	
	virtual void SetUpRotation(EAngle newAngle) override;

	UFUNCTION()
	void SetCondorSitting(bool toSitting);
	
	UFUNCTION()
	FRotator GetTargetRotation(EAngle newAngle);

	UPROPERTY()
	UStaticMeshComponent* _condorFlyingMesh;
	
	UPROPERTY()
	UStaticMeshComponent* _condorSittingMesh;

	UPROPERTY()
	UStaticMeshComponent* _condorTige;
	
	UPROPERTY(EditAnywhere)
	float _rotateSpeed;

	UPROPERTY()
	FQuat _startRotation;

	UPROPERTY()
	FQuat _endRotation;
	
	UPROPERTY(EditAnywhere)
	int32 currentNestNb;

	UPROPERTY(EditAnywhere)
	bool isWaitLastRound;

	UPROPERTY(EditAnywhere)
	TArray<ATileActor_Character*> _characters;


	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_CondorAttack;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_CondorPickUpEnnemy;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_CondorPickUpMilou;
	
	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_CondorPickUpTintin;
};
