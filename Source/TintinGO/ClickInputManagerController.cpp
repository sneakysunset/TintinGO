#include "ClickInputManagerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"

void AClickInputManagerController::SetupInputComponent()
{
    PawnMappingContext = NewObject<UInputMappingContext>(this);

    LeftClickAction = NewObject<UInputAction>(this);
    LeftClickAction->ValueType = EInputActionValueType::Boolean;

    PawnMappingContext->MapKey(LeftClickAction, EKeys::LeftMouseButton);
}