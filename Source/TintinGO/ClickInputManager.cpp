#include "ClickInputManager.h"
#include "State.h"
#include "State_AwaitingInputs.h"
AClickInputManager::AClickInputManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AClickInputManager::BeginPlay()
{
	Super::BeginPlay();
    _gameManager = AGameManager::GetInstance();
	
}

void AClickInputManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClickInputManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("MouseClick", IE_Pressed, this, &AClickInputManager::OnMouseClick);
}


void AClickInputManager::OnMouseClick()
{
    FVector2D MouseScreenPosition;
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    PlayerController->GetMousePosition(MouseScreenPosition.X, MouseScreenPosition.Y);

    // Get mouse position in world space
    FVector MouseWorldPosition;
    FVector MouseWorldDirection;
    PlayerController->DeprojectScreenPositionToWorld(MouseScreenPosition.X, MouseScreenPosition.Y, MouseWorldPosition, MouseWorldDirection);

    // Perform ray cast
    FHitResult HitResult;
    FVector Start = MouseWorldPosition;
    FVector End = MouseWorldPosition + MouseWorldDirection * 5000.f; // Adjust the length of the ray as needed
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this); // Ignore the pawn itself

    // Perform the ray cast
    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
    {
        // Hit something, you can access HitResult to get information about the hit
        FVector HitLocation = HitResult.Location;
        UState* state = _gameManager->_states[_gameManager->_currentStateIndex];
        if(State_AwaitingInputs* AwaitingInputsState = Cast<State_AwaitingInputs>(state))
        {
            AwaitingInputsState->ReceiveLeftMouseClick(HitLocation);
        }
        // Do something with HitLocation
    }
}
