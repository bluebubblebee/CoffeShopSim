// Fill out your copyright notice in the Description page of Project Settings.

#include "InputControllerComponent.h"
#include "InputControllerProcessor.h"
#include "Kismet/GameplayStatics.h"

UInputControllerComponent::UInputControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bTickEvenWhenPaused = true;
}

void UInputControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPlayerController = Cast<APlayerController>(GetOwner());
	if (OwnerPlayerController == nullptr)
	{
		return;
	}

	CurrentPlatform = EPlatformType::VE_WINDOWS;
	CurrentInput = EInputController::VE_CONTROLLER;

	FString PlatformName = UGameplayStatics::GetPlatformName();
	if (PlatformName == "Windows")
	{
		CurrentPlatform = EPlatformType::VE_WINDOWS;
		CurrentInput = EInputController::VE_MOUSE_AND_KEYBOARD;
	}else
	{
		CurrentPlatform = EPlatformType::VE_STEAM_DECK;
		CurrentInput = EInputController::VE_CONTROLLER;
	}

	if (OwnerPlayerController != nullptr && OwnerPlayerController->IsLocalPlayerController() && !SharedPtrInputProcessor.IsValid())
	{
		SharedPtrInputProcessor = MakeShareable(new FInputControllerProcessor());
		SharedPtrInputProcessor->SetController(this);
		FSlateApplication::Get().RegisterInputPreProcessor(SharedPtrInputProcessor);

		//IPlatformInputDeviceMapper& PlatformInputMapper = IPlatformInputDeviceMapper::Get();
		//if (!PlatformInputMapper.GetOnInputDeviceConnectionChange().IsBoundToObject(this))
		//{
			//PlatformInputMapper.GetOnInputDeviceConnectionChange().AddUObject(this, &UInputControllerComponent::OnControllerConnectionChanged);
		//}
	}

	//bHasBeenInitialized = true;
}

void UInputControllerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (OwnerPlayerController != nullptr && OwnerPlayerController->IsLocalPlayerController())
	{
		FSlateApplication::Get().UnregisterInputPreProcessor(SharedPtrInputProcessor);
	}

	//IPlatformInputDeviceMapper::Get().GetOnInputDeviceConnectionChange().RemoveAll(this);
	Super::EndPlay(EndPlayReason);
}


// Called every frame
void UInputControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInputControllerComponent::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	const EInputController NewInputType = GetKeyInputType(InKeyEvent.GetKey());
	if (NewInputType != CurrentInput)
	{
		HandleInputChange(NewInputType);
	}
}

void UInputControllerComponent::HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	const EInputController NewInputType = GetKeyInputType(InKeyEvent.GetKey());
	if (NewInputType != CurrentInput)
	{
		HandleInputChange(NewInputType);
	}
}

void UInputControllerComponent::HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	if ((IsControllerKeyboardMouse(CurrentInput)) && (MouseEvent.GetCursorDelta().SizeSquared() > 0.0f))
	{	
		HandleInputChange(EInputController::VE_MOUSE_AND_KEYBOARD);
	}
}

void UInputControllerComponent::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	if (IsControllerKeyboardMouse(CurrentInput))
	{
		HandleInputChange(EInputController::VE_MOUSE_AND_KEYBOARD);
	}
}

EInputController UInputControllerComponent::GetKeyInputType(const FKey Key)
{
	if (Key.IsGamepadKey())
	{
		return EInputController::VE_CONTROLLER;
	}
	
	return EInputController::VE_MOUSE_AND_KEYBOARD;		
}

void UInputControllerComponent::HandleInputChange(const EInputController NewInput)
{
	if (CurrentPlatform != EPlatformType::VE_WINDOWS)
	{
		// We keep controller for a platform that's not Windows
		CurrentInput = EInputController::VE_CONTROLLER;
		return;
	}

	if (CurrentInput != NewInput)
	{
		CurrentInput = NewInput;
		OnInputControllerChanged.Broadcast(CurrentInput);
	}
}

bool UInputControllerComponent::IsControllerKeyboardMouse(EInputController Controller)
{
	if ((Controller == EInputController::VE_KEYBOARD) || (Controller == EInputController::VE_MOUSE_AND_KEYBOARD))
	{
		return true;
	}
	
	return false;
}

bool UInputControllerComponent::IsControllerGamepad(EInputController Controller)
{
	if (Controller == EInputController::VE_CONTROLLER)
	{
		return true;
	}

	return false;
}