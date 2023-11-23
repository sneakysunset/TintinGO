// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State_TActor.h"

/**
 * 
 */
class TINTINGO_API State_TActor_Move : public State_TActor
{
public:
	State_TActor_Move();
	State_TActor_Move(ATileActor* tileActor);
};
