#pragma once

#include "CoreMinimal.h"
#include "PlacableBody.h"
#include "GameFramework/Pawn.h"
#include "TileCharacter.generated.h"

UCLASS()
class TINTINGO_API ATileCharacter : public APawn, public IPlacableBody
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATileCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	class UStaticMeshComponent* _staticMeshComponent = nullptr;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Inherited via IPlacableBody
	virtual void PlaceBody(/*ATile* tile*/) override;

	virtual void TriggerBody() override;
};
