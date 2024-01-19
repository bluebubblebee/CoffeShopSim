// Fill out your copyright notice in the Description page of Project Settings.


#include "CSAssetManager.h"
#include "Items/CSItem.h"

const FPrimaryAssetType	UCSAssetManager::PotionItemType = TEXT("Potion");
const FPrimaryAssetType	UCSAssetManager::BackeryItemType = TEXT("Backery");


UCSAssetManager& UCSAssetManager::Get()
{
	UCSAssetManager* This = Cast<UCSAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return *This;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid AssetManager in DefaultEngine.ini, must be UCSAssetManager!"));
		return *NewObject<UCSAssetManager>(); // never calls this
	}
}

void UCSAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}


UCSItem* UCSAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	// This does a synchronous load and may hitch
	UCSItem* LoadedItem = Cast<UCSItem>(ItemPath.TryLoad());

	if (bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}

	return LoadedItem;
}