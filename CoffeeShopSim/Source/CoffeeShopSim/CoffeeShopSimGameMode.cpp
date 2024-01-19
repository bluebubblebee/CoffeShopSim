// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoffeeShopSimGameMode.h"
#include "CoffeeShopSimPlayerController.h"
#include "CoffeeShopSimCharacter.h"

#include "ShopManager.h"
#include "UObject/ConstructorHelpers.h"

ACoffeeShopSimGameMode::ACoffeeShopSimGameMode()
{
	PlayerControllerClass = ACoffeeShopSimPlayerController::StaticClass();
}


void ACoffeeShopSimGameMode::RegisterShopManager(class AShopManager* Reference)
{
	ShopManager = Reference;
}