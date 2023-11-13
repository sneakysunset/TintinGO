#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputManager.generated.h"

UCLASS()
class TINTINGO_API UInputManager : public UObject
{
	GENERATED_BODY()
	
public:
	UInputManager();
	~UInputManager();

	virtual void SetUpInputComponent() override;
};
