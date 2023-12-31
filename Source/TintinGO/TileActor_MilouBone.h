#pragma once

#include "CoreMinimal.h"
#include "TileActor.h"
#include "TileActor_MilouBone.generated.h"

UCLASS()
class TINTINGO_API ATileActor_MilouBone : public ATileActor
{
	GENERATED_BODY()

public:
	ATileActor_MilouBone();

	UFUNCTION()
	virtual void OnEndTask() override;

	UPROPERTY(EditDefaultsOnly, Category = "AudioFile")
	USoundBase* S_BoneTrigger;

	UPROPERTY(EditDefaultsOnly, Category = "AudioFile")
	USoundBase* S_BoneLand;

	UPROPERTY(EditDefaultsOnly, Category = "AudioFile")
	USoundBase* S_BoneThrow;
	
	UFUNCTION()
	void OnDestroyBone();
};
