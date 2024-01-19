// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicInteractive.h"
#include "Interactable.h"
#include "Definitions.h"
#include "PickupInteractive.generated.h"

/**
 * 
 */
UCLASS()
class COFFEESHOPSIM_API APickupInteractive : public ABasicInteractive, public IInteractable
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	FItem Item;

public:

	// Interaface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnInteract();

	//Actual implementation of the Interact event
	void OnInteract_Implementation();
	
};