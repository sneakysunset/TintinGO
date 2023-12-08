

#include "TileActor_Character_Condor.h"

ATileActor_Character_Condor* ATileActor_Character_Condor::SingletonInstance = nullptr;

ATileActor_Character_Condor* ATileActor_Character_Condor::GetInstance() 
{
	return SingletonInstance;
}

ATileActor_Character_Condor::ATileActor_Character_Condor()
{
	PrimaryActorTick.bCanEverTick = true;
	SingletonInstance = this;
	isWaitLastRound = true;
}