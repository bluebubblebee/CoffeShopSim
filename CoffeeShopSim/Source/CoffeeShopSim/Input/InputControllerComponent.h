// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoffeeShopSim/Common/Definitions.h"
#include "InputDefinitions.h"
#include "InputControllerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputControllerChangedDelegate, EInputController, ControllerType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COFFEESHOPSIM_API UInputControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInputControllerComponent();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), Category = "Input")
	class UInputMappingContext* InGameMappingContextDefault;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"), Category = "Input")
	class UInputMappingContext* MenuMappingContextDefault;

protected:

	UPROPERTY()
	class APlayerController* OwnerPlayerController = nullptr;

	TSharedPtr<class FInputControllerProcessor> SharedPtrInputProcessor = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;	

public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPROPERTY(BlueprintReadOnly, Category = "InputControllerComponent")
	EInputController CurrentInput = EInputController::VE_CONTROLLER;

	UPROPERTY(BlueprintReadOnly, Category = "InputControllerComponent")
	EPlatformType CurrentPlatform;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadOnly, Category = "InputControllerComponent")
	FOnInputControllerChangedDelegate OnInputControllerChanged;
	
public:
	UFUNCTION(BlueprintCallable, Category = "InputControllerComponent")
	class UInputMappingContext* GetInGameMappingContext();

	UFUNCTION(BlueprintCallable, Category = "InputControllerComponent")
	class UInputMappingContext* GetMenuMappingContext();

public:
	
	void HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent);
	void HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent);
	void HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent);
	void HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent);
	
private:
	
	EInputController GetKeyInputType(const FKey Key);
	void HandleInputChange(const EInputController NewInput);
	static bool IsControllerKeyboardMouse(EInputController Controller);
	static bool IsControllerGamepad(EInputController Controller);
};
