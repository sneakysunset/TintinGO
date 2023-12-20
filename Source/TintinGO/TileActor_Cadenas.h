// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileActor.h"
#include "TileActor_Cadenas.generated.h"

UCLASS()
class TINTINGO_API ATileActor_Cadenas : public ATileActor
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
public:
	static ATileActor_Cadenas* GetInstance();
	static ATileActor_Cadenas* SingletonInstance;

	UPROPERTY()
	void UnlockCadenas();

	UStaticMeshComponent* _staticMeshComponent;
};
