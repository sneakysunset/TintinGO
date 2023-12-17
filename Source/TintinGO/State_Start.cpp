// Fill out your copyright notice in the Description page of Project Settings.


#include "State_Start.h"

#include "MainGameMode.h"
#include "State_AwaitingInputs.h"

void UState_Start::OnStateEnter()
{
	Super::OnStateEnter();
	_interpolateValue = 0;
	_startAlpha = 1;
	_endAlpha = 0;
}

void UState_Start::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);
	_interpolateValue += DeltaTime * _speed;

	_widget->FadeScreen->SetOpacity(FMath::Lerp(_startAlpha, _endAlpha, _curve->FloatCurve.Eval(_interpolateValue)));
	
	if(_interpolateValue >= 1)
	{
		_widget->FadeScreen->SetOpacity(_endAlpha);
		_gameManager->LateInit();
		_gameManager->StateChange(NewObject<UState_AwaitingInputs>(UState_AwaitingInputs::StaticClass()));
	}
}
