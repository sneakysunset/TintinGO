#pragma once

#include "CoreMinimal.h"
#include "State_TActor.h"
#include "Tile.h"
#include "GameFramework/Actor.h"
#include "TileActor.generated.h"


UCLASS()
class TINTINGO_API ATileActor : public AActor
{
	GENERATED_BODY()

	
public:
	virtual void OnEndTask();
	virtual void TriggerBody();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	UState_TActor* _currentState_TA;
	void ChangeState(UState_TActor* newState);
	
	virtual ATile* GetCurrentTile() const{return _currentTile;}
	virtual void SetCurrentTile(ATile* tile)
	{
		if(IsValid(_currentTile) && _currentTile->_tileActors.Contains(this))
		{
			_currentTile->_tileActors.Remove(this);
		}
		_currentTile = tile;
		
		if(IsValid(tile) && !tile->_tileActors.Contains(this))
		{
			tile->_tileActors.Add(this);
		}
	}
	bool _isTaskOver;

	UPROPERTY(EditAnywhere)
	float _speed;
	
protected:
	UPROPERTY()
	ATile* _currentTile;
	virtual void BeginPlay() override;

public:	
	
};
