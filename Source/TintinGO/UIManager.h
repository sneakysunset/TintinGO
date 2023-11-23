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
	
public:	
	// Sets default values for this actor's properties
	AUIManager();
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UCoreUI> YourWidgetClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
