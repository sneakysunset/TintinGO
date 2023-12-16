#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ClickInputManager.generated.h"


class AMainGameMode;

UCLASS()
class TINTINGO_API AClickInputManager : public APawn
{
	GENERATED_BODY()

public:
	AClickInputManager();
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	APlayerController* pController;

	void OnMouseClick();
		
private :
	UPROPERTY()
	AMainGameMode* _gameManager;
};
