#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CoreUI.h"
#include "Blueprint/UserWidget.h"
#include "UIManager.generated.h"

UCLASS()
class TINTINGO_API AUIManager : public AActor
{
	GENERATED_BODY()
	
/*
public:
	static AUIManager* GetInstance();
	// Sets default values for this actor's properties
	AUIManager();
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCoreUI> YourWidgetClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UCoreUI* _coreUI;

	static AUIManager* SingletonInstance;
public:	
	// Called every frame
	UFUNCTION()
	void ChangeTextValue(int32 newValue, FColor DisabledColor);

	UFUNCTION()
	void CustomInit();*/
};
