// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/SaveGame.h"
#include "ShopGameInstance.generated.h"



UCLASS()
class COFFEESHOPSIM_API UMainSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SaveGameName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime CreationTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Coins;
};

/**
 * 
 */
UCLASS()
class COFFEESHOPSIM_API UShopGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
};
