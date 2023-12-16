#include "State.h"
#include "GameManager.h"
#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"


void UState::OnStateEnter()
{
}

void UState::OnStateTick(float DeltaTime)
{

}

void UState::OnStateExit()
{
	this->ConditionalBeginDestroy();
}
