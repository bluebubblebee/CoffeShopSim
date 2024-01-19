// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicInteractive.h"
#include "Interactable.h"
#include "Definitions.h"
#include "DropInteractive.generated.h"

/**
 * 
 */
UCLASS()
class COFFEESHOPSIM_API ADropInteractive : public ABasicInteractive, public IInteractable
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	int32 MaxItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	TArray<FItem> ItemsOnInteractive;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "WorkStation")
	void OnItemDropped(const FItem& Item);

public:

	// Interaface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnInteract();

	//Actual implementation of the Interact event
	void OnInteract_Implementation();	
};
