#include "ClickInputManager.h"
#include "ClickInputManagerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MainGameMode.h"

AClickInputManager::AClickInputManager()
{
	PrimaryActorTick.bCanEverTick = true;
}



void AClickInputManager::BeginPlay()
{
	Super::BeginPlay();
    _gameManager = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
}

void AClickInputManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClickInputManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	

    UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    AClickInputManagerController* FPC = Cast<AClickInputManagerController>(Controller);
    pController = Cast<APlayerController>(Controller);
    check(EIC && FPC);
   
    EIC->BindAction(FPC->LeftClickAction, ETriggerEvent::Started, this, &AClickInputManager::OnMouseClick);

    ULocalPlayer* LocalPlayer = FPC->GetLocalPlayer();
    check(LocalPlayer);
    UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    check(Subsystem);
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(FPC->PawnMappingContext, 0);
}


void AClickInputManager::OnMouseClick()
{
	if(_gameManager->OnClickD.IsBound())
	{
		_gameManager->OnClickD.Execute();
	}
    //State* state = _gameManager->_states[_gameManager->_currentStateType];
    //state->ReceiveLeftMouseClick();
}
	