#pragma once

#include "CoreMinimal.h"
#include "State_TActor.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"


UCLASS()
class TINTINGO_API ATileActor : public AActor
{
	GENERATED_BODY()

	
public:
	virtual void OnEndTask();
	virtual void TriggerBody();

	UPROPERTY()
	UState_TActor* _currentState_TA;
	void ChangeState(UState_TActor* newState);
	
	virtual ATile* GetCurrentTile() const{return _currentTile;}
	virtual void SetCurrentTile(ATile* tile)
	{
		check(tile != nullptr);
		_currentTile = tile;
	}
	
	ATile* GetNextTile() const { return _nextTile;}
	void SetNextTile(ATile* tile){_nextTile = tile;}
	
	bool _isTaskOver;

	UPROPERTY(EditAnywhere)
	float _speed;
	
protected:
	ATile* _nextTile;
	UPROPERTY()
	ATile* _currentTile;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
