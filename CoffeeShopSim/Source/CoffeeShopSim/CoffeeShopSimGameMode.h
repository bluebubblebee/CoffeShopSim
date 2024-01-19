// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CoffeeShopSimGameMode.generated.h"

UCLASS(minimalapi)
class ACoffeeShopSimGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACoffeeShopSimGameMode();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode")
	class AShopManager* ShopManager;

public:
	UFUNCTION(BlueprintCallable, Category = "Game Mode")
	void RegisterShopManager(class AShopManager* Reference);
};



