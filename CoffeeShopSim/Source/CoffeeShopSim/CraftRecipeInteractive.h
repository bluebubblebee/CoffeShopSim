// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicInteractive.h"
#include "Interactable.h"
#include "Definitions.h"
#include "CraftRecipeInteractive.generated.h"

/**
 * 
 */
UCLASS()
class COFFEESHOPSIM_API ACraftRecipeInteractive : public ABasicInteractive, public IInteractable
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	int32 MaxIngredients = 3;

	UPROPERTY(BlueprintReadWrite, Category = "Interactive")
	TArray<FRecipeIngredient> AddedIngredients;

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "WorkStation")
	void OnItemDropped(const FItem& Item);

public:
	
	UFUNCTION(BlueprintCallable, Category = "Interactive")
	bool TryAddIngredients(const FItem& Item);

	UFUNCTION(BlueprintCallable, Category = "Interactive")
	bool IsRecipeReady();
};
