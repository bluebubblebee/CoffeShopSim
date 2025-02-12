// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EInputController : uint8
{
	VE_NONE						UMETA(DisplayName = "None"),
	VE_KEYBOARD					UMETA(DisplayName = "Keyboard"),
	VE_MOUSE_AND_KEYBOARD		UMETA(DisplayName = "Mouse and Keyboard"),
	VE_CONTROLLER				UMETA(DisplayName = "Controller")
};

UENUM(BlueprintType)
enum class EKeyDirection : uint8
{
	VE_UP				UMETA(DisplayName = "Up"),
	VE_DOWN				UMETA(DisplayName = "Down"),
	VE_LEFT				UMETA(DisplayName = "Left"),
	VE_RIGHT			UMETA(DisplayName = "Right"),
	VE_NONE				UMETA(DisplayName = "None")
};

class COFFEESHOPSIM_API InputDefinitions
{
public:
	InputDefinitions();
	~InputDefinitions();
};




