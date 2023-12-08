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
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnEndTask() override;
};
