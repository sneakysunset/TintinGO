#pragma once

#include "Tile.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

/*DECLARE_DYNAMIC_DELEGATE(FOnClickDelegate);
DECLARE_DYNAMIC_DELEGATE(FUIMilouClick);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBoneConsumed, int32, NewBoneNumber, FColor, DisabledColor);*/
//DECLARE_DELEGATE(FOnClickDelegate)
//DECLARE_DELEGATE(FUIMilouClick)

class UState;

UCLASS()
class TINTINGO_API AGameManager : public AActor
{
	GENERATED_BODY()

public:	
	/*static AGameManager* GetInstance();
	void GameOver() const;
	void OnWin() const;
	//FOnClickDelegate OnClickD;
	//FUIMilouClick OnMilouBoneClick;
	//FOnBoneConsumed OnBoneConsumed;

	AGameManager();
	
	virtual ~AGameManager() override;
	
	UPROPERTY()
	UState* _currentStateType;
	
	UFUNCTION()
	void StateChange(UState* NewState);
	
	UPROPERTY(EditAnywhere, Category = "Milou Parameters")
	int32 _milouBoneThrowRange;
	
	UPROPERTY()
	int32 _milouBonesNumber;
	
	UFUNCTION(BlueprintCallable)
	void ReceiveMilouUIClick();

	UPROPERTY(EditAnywhere)
	int32 _clueNumber;

	UPROPERTY(EditAnywhere)
	float _inTileMoveSpeed;
	
	UPROPERTY(EditAnywhere)
	float _rotateSpeed;

	UPROPERTY(EditAnywhere)
	EAngle _tintinAngle;
	
	
protected:
	virtual void Tick(float DeltaTime) override;
	
	virtual void BeginPlay() override;
	
private:
	// Called when the game starts or when spawned
	static AGameManager* SingletonInstance;*/
};
