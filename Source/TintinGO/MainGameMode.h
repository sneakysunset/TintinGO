#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

UCLASS()
class TINTINGO_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
public :
	AMainGameMode();
	virtual ~AMainGameMode() = default;
};
