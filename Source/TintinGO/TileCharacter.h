#pragma once

#include "CoreMinimal.h"
#include "PlacableBody.h"
#include "GameFramework/Pawn.h"
#include "TileCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Neutral = 0b0000 UMETA(DisplayName = "Neutral"),
	Ennemy1 = 0b0001 UMETA(DisplayName = "Ennemy1 (Not implemented)"),
	Ennemy2 = 0b0010 UMETA(DisplayName = "Ennemy2 (Not implemented)")
};

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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Inherited via IPlacableBody
	virtual void PlaceBody(/*ATile* tile*/) override;

	virtual void TriggerBody() override;

private:
	class UStaticMeshComponent* _staticMeshComponent = nullptr;
};
