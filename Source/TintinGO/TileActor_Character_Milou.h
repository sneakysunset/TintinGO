// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor_Character.h"
#include "TileActor_Character_Milou.generated.h"


class ATileActor_MilouBone;

UENUM(BlueprintType)
enum class EMilouState : uint8
{
	Sitting UMETA(DisplayName = "Sitting"),
	Running UMETA(DisplayName = "Running"),
	Standing UMETA(DisplayName = "Standing")
};

UCLASS()
class TINTINGO_API ATileActor_Character_Milou : public ATileActor_Character
{
	GENERATED_BODY()
	
	ATileActor_Character_Milou();
	
public:
	static ATileActor_Character_Milou* GetInstance();
	static ATileActor_Character_Milou* SingletonInstance;

	UPROPERTY()
	ATileActor_MilouBone* _milouBoneToDrop;
	
	UPROPERTY()
	bool isBoundToTintin;

	UPROPERTY(EditAnywhere)
	TArray<ATile*> MilouTilePath;

	UPROPERTY()
	ATile* _previousCondorTile;
	
	UPROPERTY(EditAnywhere)
	float _boneSpeed;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_milouStartMoving;

	UFUNCTION()
	void SetMilouMesh(EMilouState state);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TMap<EMilouState , UStaticMeshComponent*> _milouMeshes;
};
