// Fill out your copyright notice in the Description page of Project Settings.


#include "State_LevelEnd.h"

#include "CoreUI.h"
#include "MainGameMode.h"

void UState_LevelEnd::OnStateEnter()
{
	Super::OnStateEnter();
	_interpolateValue = 0;
	_startAlpha = 0;
	_endAlpha = 1;
}

void UState_LevelEnd::OnStateTick(float DeltaTime)
{
	Super::OnStateTick(DeltaTime);
	_interpolateValue += DeltaTime * _speed;

	_widget->FadeScreen->SetOpacity(FMath::Lerp(_startAlpha, _endAlpha, _curve->FloatCurve.Eval(_interpolateValue)));
	
	if(_interpolateValue >= 1)
	{
		_widget->FadeScreen->SetOpacity(_endAlpha);
		_gameManager->LevelTransi();
	}
}