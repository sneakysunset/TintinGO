#include "GameManager.h"

#include "GlobalGameManager.h"
#include "State.h"
#include "State_AwaitingInputs.h"
#include "UIManager.h"
#include "Kismet/GameplayStatics.h"

AGameManager* AGameManager::SingletonInstance = nullptr;

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
	_milouBoneThrowRange = 2;
	_milouBonesNumber = 0;
	_currentStateType = NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass());
}

AGameManager::~AGameManager()
{
	OnClickD.Clear();
	OnMilouBoneClick.Clear();
	OnBoneConsumed.Clear();
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	SingletonInstance = this;
	_currentStateType = NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass());
	_currentStateType->OnStateEnter();
	//Cast<UGlobalGameManager>(UGameplayStatics::GetGameInstance(GetWorld()))->OnLevelLoad();
	AUIManager::GetInstance()->CustomInit();
}

void AGameManager::ReceiveMilouUIClick()
{
	if(OnMilouBoneClick.IsBound())
	{
		OnMilouBoneClick.Execute();
	}
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsValid(this) && IsValid(_currentStateType) && _currentStateType != nullptr)
	{
		_currentStateType->OnStateTick(DeltaTime);
	}
}

void AGameManager::StateChange(UState* newState)
{
	_currentStateType->OnStateExit();
	_currentStateType = newState;
	_currentStateType->OnStateEnter();
}

AGameManager* AGameManager::GetInstance() 
{
	return SingletonInstance;
}

void AGameManager::GameOver() const
{
	UGameplayStatics::OpenLevel(GetWorld(), *UGameplayStatics::GetCurrentLevelName(GetWorld()), true);
}

void AGameManager::OnWin() const
{
	if(UGameplayStatics::GetCurrentLevelName(GetWorld()) == FString("Level_1"))
	{
		UGameplayStatics::OpenLevel(GetWorld(),  *FString("Level_2"), true);
	}
	else if(UGameplayStatics::GetCurrentLevelName(GetWorld()) == FString("Level_2"))
	{
		UGameplayStatics::OpenLevel(GetWorld(),  *FString("Level_3"), true);
	}
}

