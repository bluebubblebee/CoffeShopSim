// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CSItem.h"
#include "CSMuffinItem.generated.h"

/**
 * 
 */
UCLASS()
class COFFEESHOPSIM_API UCSMuffinItem : public UCSItem
{
	GENERATED_BODY()

public:
	/** Constructor */
	UCSMuffinItem()
	{
		ItemType = UCSAssetManager::BackeryItemType;
	}
	
};
