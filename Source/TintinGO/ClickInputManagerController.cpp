#include "ClickInputManagerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"


AClickInputManagerController::AClickInputManagerController()
{
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Default;
    
}

//Generate my inputs mapping and actions UObjects.
void AClickInputManagerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    PawnMappingContext = NewObject<UInputMappingContext>(this);
    LeftClickAction = NewObject<UInputAction>(this);
    LeftClickAction->ValueType = EInputActionValueType::Boolean;

    PawnMappingContext->MapKey(LeftClickAction, EKeys::LeftMouseButton);
}


