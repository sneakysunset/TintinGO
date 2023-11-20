#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameManager.h"
#include "ClickInputManager.generated.h"

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


	void OnMouseClick();
		
private :
	AGameManager* _gameManager;
	UPROPERTY(EditAnywhere)
		class UCameraComponent* CameraComponent;
};
