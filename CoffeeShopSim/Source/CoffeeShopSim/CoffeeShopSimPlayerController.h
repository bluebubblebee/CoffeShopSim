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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UInputControllerComponent* InputControllerComponent;
	
protected:

	UFUNCTION()
	void OnControllerChanged(EInputController NewInputController);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void HandleMovement(const FVector2D& Value);	

	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void HandleFaceTopButton();
	
	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void HandleFaceRightButton();
	
	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void HandleFaceBottomButton();

	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void HandleFaceLeftButton();

	UFUNCTION(BlueprintCallable, Category = "Inputs")
	void HandleInputDirection(EKeyDirection Direction);	

	UFUNCTION(BlueprintCallable, Category = "Input")
	void HandleMainMenuButtonInGame();
	
	UFUNCTION(BlueprintCallable, Category = "Input")
    void HandleRightShoulderButtonInGame();

    UFUNCTION(BlueprintCallable, Category = "Input")
    void HandleLeftShoulderButtonInGame();

    

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void ChangeMappingContextToInGame();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ChangeMappingContextToMenu();
	
	
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void LockInput();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void UnLockInput();

protected:

	// Reference to the pawn player
	class ACoffeeShopSimCharacter* MyCharacter;

	bool bIsInputLocked;

	UPROPERTY(BlueprintReadWrite, Category = "References")
	TObjectPtr<class AShopSimHUD> HUD;
	
};


