// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CoffeeShopSim/Common/Definitions.h"
#include "ShopSimHUD.generated.h"

/**
 * 
 */
UCLASS()
class COFFEESHOPSIM_API AShopSimHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	EGameMenuType CurrentMenu = EGameMenuType::VE_NONE;
	
	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	EGameMenuType LastActiveMenuType;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	class UUserWidget* ActiveGameMenu = nullptr;		

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	class UUserWidget* LastActiveGameMenu = nullptr;

public:
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Menu")
	bool IsOnGameMenu();
	
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void SetActiveGameMenu(class UUserWidget* Widget, EGameMenuType MenuType);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu")
	void ShowMainMenu();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu")
	void HideMainMenu();

public:	
	void TopFaceButtonPress();
	void RightFaceButtonPress();
	void BottomFaceButtonPress();
	void LeftFaceButtonPress();
	void RightShoulderButtonPress();
	void LeftShoulderButtonPress();
	void NavigateInMenu(EKeyDirection Direction);

public:
	void RegisterSimPlayerController(ACoffeeShopSimPlayerController* PlayerController);

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Menu")
	class ACoffeeShopSimPlayerController* SimPlayerController;
};
