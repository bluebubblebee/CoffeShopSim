// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ActorPoolingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UActorPoolingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COFFEESHOPSIM_API IActorPoolingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void PoolBeginPlay();

	UFUNCTION(BlueprintNativeEvent)
	void PoolEndPlay();
};
