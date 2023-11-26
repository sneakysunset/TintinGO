// Fill out your copyright notice in the Description page of Project Settings.


#include "TileActor_Character_Tintin.h"


ATileActor_Character_Tintin* ATileActor_Character_Tintin::SingletonInstance = nullptr;

ATileActor_Character_Tintin* ATileActor_Character_Tintin::GetInstance() 
{
	return SingletonInstance;
}

ATileActor_Character_Tintin::ATileActor_Character_Tintin()
{
	PrimaryActorTick.bCanEverTick = true;
	SingletonInstance = this;

}
