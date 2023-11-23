// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
class ATileActor;

class TINTINGO_API State_TActor : public State
{
public:
	State_TActor();
	State_TActor(ATileActor* tileActor);
	ATileActor* _tileActor;
};
