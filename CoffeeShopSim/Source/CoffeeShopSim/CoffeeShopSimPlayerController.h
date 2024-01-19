// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CoffeeShopSimPlayerController.generated.h"

UCLASS()
class ACoffeeShopSimPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACoffeeShopSimPlayerController();

	virtual void BeginPlay() override;

protected:


	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float Value);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void Interact();


public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void LockInput();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void UnLockInput();

protected:

	// Reference to the pawn player
	class ACoffeeShopSimCharacter* MyCharacter;

	bool bIsInputLocked;
	
};


