// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor_Character.h"
#include "TileActor_Character_Peruvien.generated.h"

class AGridManager;

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

	UPROPERTY()
	ATile* _startingTile;

	UPROPERTY()
	EAngle _startingAngle;

	EAngle _tintinAngle;
	
	UFUNCTION()
	bool Detection(ATile* detectTile) const;

	UPROPERTY(EditAnywhere)
	EPeruvienBehaviour _currentPBehaviour;
	
protected:
	virtual void BeginPlay() override;

};
