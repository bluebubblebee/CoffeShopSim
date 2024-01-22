// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicInteractive.h"
#include "Interactable.h"
#include "Definitions.h"
#include "ApplianceInteractive.generated.h"

/**
 * 
 */
UCLASS()
class COFFEESHOPSIM_API AApplianceInteractive : public ABasicInteractive, public IInteractable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	class ACoffeeShopSimGameMode* MainGameMode;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	TArray<FName> RecipeIDList;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	TArray<FRecipe> RecipeList;

	UPROPERTY(BlueprintReadOnly, Category = "Interactive")
	FRecipe RecipeSelected;

	UPROPERTY(BlueprintReadWrite, Category = "Interactive")
	bool IsPlayingMinigame;

	

public:

	// Interaface
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactive")
	void OnInteract();

	//Actual implementation of the Interact event
	void OnInteract_Implementation();

protected:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "WorkStation")
	void OnStartMinigame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "WorkStation")
	void OnUpdateMinigame();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "WorkStation")
	void OnCompleteMinigame();


protected:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactive")
	bool TryToSelectRecipe();

	bool TryToSelectRecipe_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactive")
	bool GiveRecipeToPlayer();

	bool GiveRecipeToPlayer_Implementation();

};
