// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputDefinitions.h"
#include "CoffeeShopSim/Common/Definitions.h"
#include "InputNavigationInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInputNavigationInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COFFEESHOPSIM_API IInputNavigationInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "InputNavigation")
	void OnInitialize(EPlatformType Platform, EInputController CurrentInput);
	virtual void OnInitialize_Implementation(EPlatformType Platform, EInputController CurrentInput);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu")
	void OnControllerConnectionChange();
	virtual void OnControllerConnectionChange_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu")
	void OnControllerChanged(EInputController Controller);
	virtual void OnControllerChanged_Implementation(EInputController Controller);

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu")
	void OnDirectionNavigation(EKeyDirection Direction);
	virtual void OnDirectionNavigation_Implementation(EKeyDirection Direction);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu")
	void OnTopFaceButton();
	virtual void OnTopFaceButton_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu")
	void OnRightFaceButton();
	virtual void OnRightFaceButton_Implementation();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu")
	void OnBottomFaceButton();
	virtual void OnBottomFaceButton_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu")
	void OnLeftFaceButton();
	virtual void OnLeftFaceButton_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu")
	void OnRightShoulderButton();
	virtual void OnRightShoulderButton_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Menu")
	void OnLeftShoulderButton();
	virtual void OnLeftShoulderButton_Implementation();
};
