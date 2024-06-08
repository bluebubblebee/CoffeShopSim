// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"
#include "Kismet/GameplayStatics.h"


const FString USaveSubsystem::SAVE_DATA = "ShopSimSaveGame_";

USaveSubsystem::USaveSubsystem()
{}

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Warning, TEXT("[USaveSubsystem::Initialize] Called"));

	Super::Initialize(Collection);

	SaveGameList.Empty();
	SaveGameSlotToLoad.Empty();
	for (int i = 0; i < MaxSaveGames; i++)
	{
		FString intToString = FString::FromInt(i);
		FString SlotIndex = SAVE_DATA + intToString;

		if (UGameplayStatics::DoesSaveGameExist(SlotIndex, CurrentUserIndex))
		{
			SaveGameSlotToLoad.Add(SlotIndex);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("[USaveSubsystem::Initialize] Number Savegames %d "), SaveGameSlotToLoad.Num());
}

void USaveSubsystem::CreateNewSaveGame()
{

}

void USaveSubsystem::LoadSaveGames()
{
	NextSlotToLoad = 0;
	if (SaveGameSlotToLoad.Num() == 0)
	{
		LoadAllSaveGamesCompleted.Broadcast(true);
		return;
	}

	// Load the first one
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUObject(this, &USaveSubsystem::HandleLoadSaveSaveGameCompleted);
	UGameplayStatics::AsyncLoadGameFromSlot(SaveGameSlotToLoad[NextSlotToLoad], CurrentUserIndex, LoadedDelegate);
}

void USaveSubsystem::HandleLoadSaveSaveGameCompleted(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	if (LoadedGameData != nullptr)
	{
		UMainSaveGame* GameData = Cast<UMainSaveGame>(LoadedGameData);
		SaveGameList.Add(GameData);

		NextSlotToLoad += 1;
		if (NextSlotToLoad < SaveGameSlotToLoad.Num())
		{
			FAsyncLoadGameFromSlotDelegate LoadedDelegate;

			LoadedDelegate.BindUObject(this, &USaveSubsystem::HandleLoadSaveSaveGameCompleted);

			UGameplayStatics::AsyncLoadGameFromSlot(SaveGameSlotToLoad[NextSlotToLoad], CurrentUserIndex, LoadedDelegate);
		}
		else
		{
			LoadAllSaveGamesCompleted.Broadcast(true);
		}
	}
	else
	{
		LoadAllSaveGamesCompleted.Broadcast(false);
	}
}
