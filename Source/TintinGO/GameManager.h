#pragma once

#include "Tile.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

DECLARE_DELEGATE(FOnClickDelegate);
DECLARE_DELEGATE(FUIMilouClick)

class State;

UCLASS()
class TINTINGO_API AGameManager : public AActor
{
	GENERATED_BODY()

public:	
	static AGameManager* GetInstance();
	FOnClickDelegate OnClickD;
	FUIMilouClick OnMilouBoneClick;

	AGameManager();
	State* _currentStateType;
	void StateChange(State* NewState);
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	UPROPERTY()
	ATile* _playerTargetTile;
	UPROPERTY(EditAnywhere, Category = "Tintin Parameters")
	float speed;
	ATile* hitTile;
	
	UFUNCTION(BlueprintCallable)
	void ReceiveMilouUIClick();
	
private:
	// Called when the game starts or when spawned
	static AGameManager* SingletonInstance;
};
