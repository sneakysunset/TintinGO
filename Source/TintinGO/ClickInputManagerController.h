
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClickInputManagerController.generated.h"

UCLASS()
class TINTINGO_API AClickInputManagerController : public APlayerController
{
	GENERATED_BODY()

	AClickInputManagerController();
	
public:
	virtual void SetupInputComponent() override;

	UPROPERTY()
		class UInputMappingContext* PawnMappingContext;
	UPROPERTY()
		class UInputAction* LeftClickAction;
};
