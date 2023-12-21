// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor_Character.h"
#include "TileActor_Character_Tintin.generated.h"

UENUM(BlueprintType)
enum class ETintinState : uint8
{
	Running UMETA(DisplayName = "Running"),
	Throwing UMETA(DisplayName = "Throwing")
};

UCLASS()
class TINTINGO_API ATileActor_Character_Tintin : public ATileActor_Character
{
	GENERATED_BODY()
	ATileActor_Character_Tintin();
public:
	static ATileActor_Character_Tintin* GetInstance();
	static ATileActor_Character_Tintin* SingletonInstance;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	TArray<USoundBase*> S_throwBoneArray;
	
	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	TArray<USoundBase*> S_pickUpMilou;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_LevelStart;

	UFUNCTION()
	void SetTintinMesh(ETintinState state);

	UFUNCTION()
	void RotateTintinToTargetTile(ATile* targetTile, float DeltaTime);

	UPROPERTY()
	ATile* _targetTile;

	UPROPERTY()
	float _interpolateValue;

	UPROPERTY(EditDefaultsOnly, Category = TintinRotationThrow)
	float _rotationThrowSpeed;

	UPROPERTY()
	FQuat _startRotation;

	UPROPERTY()
	FQuat _endRotation;
	
	UPROPERTY()
	UStaticMeshComponent* bone;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TMap<ETintinState , UStaticMeshComponent*> _tintinMeshes;

};
