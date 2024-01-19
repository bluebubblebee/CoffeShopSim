// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Styling/SlateBrush.h"
#include "../CSAssetManager.h"
#include "CSItem.generated.h"

/**
 * 
 */
UCLASS()
class COFFEESHOPSIM_API UCSItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UCSItem()
		: Price(0)
	{}


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
		FPrimaryAssetType ItemType;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FText ItemName;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FText ItemDescription;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		FSlateBrush ItemIcon;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		int32 Price;


	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	
};
