// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveSubsystem.h"

#include "CoffeeShopSim/CoffeeShopSim.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"


const FString USaveSubsystem::SAVE_DATA = "ShopSimSaveGame_";

USaveSubsystem::USaveSubsystem()
{}

void USaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOGFMT(LogCoffeeShopSim, Log, "[USaveSubsystem::Initialize] Called");
	Super::Initialize(Collection);
}

void USaveSubsystem::CreateNewSaveGame()
{
	// Find the next available save game 
	FString NextAvailableSaveGame;
	bool bFound = false;
	for (int i = 0; i < MaxSaveGames; i++)
	{
		FString intToString = FString::FromInt(i);
		FString SaveGame = SAVE_DATA + intToString;

		if (!UGameplayStatics::DoesSaveGameExist(SaveGame, CurrentUserIndex))
		{
			bFound = true;
			NextAvailableSaveGame = SaveGame;
			break;
		}
	}

	// No save game available, return the function early
	if (!bFound)
	{
		SaveGameCreatedCompleted.Broadcast(false);
		return;
	}

	// Create the save game
	LastSaveGameCreated = Cast<UMainSaveGame>(UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass()));
	if (LastSaveGameCreated)
	{
		LastSaveGameCreated->SaveGameName = NextAvailableSaveGame;
		LastSaveGameCreated->CreationTime = FDateTime::Now();
		LastSaveGameCreated->Level = 1;
		LastSaveGameCreated->Coins = FMath::RandRange(10, 300);

		// Async save the new save game
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		SavedDelegate.BindUObject(this, &USaveSubsystem::HandleCreateNewGameCompleted);
		UGameplayStatics::AsyncSaveGameToSlot(LastSaveGameCreated, NextAvailableSaveGame, CurrentUserIndex, SavedDelegate);
	}
	else
	{
		// Call the event with false if anything went wrong with the creation
		SaveGameCreatedCompleted.Broadcast(false);
	}
}

void USaveSubsystem::HandleCreateNewGameCompleted(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOGFMT(LogCoffeeShopSim, Log, "[USaveSystemSubsystem::HandleCreateNewGameCompleted] CREATED  {SlotName} - UserIndex: {UserIndex}", SlotName, UserIndex);
		//UE_LOG(LogTemp, Warning, TEXT("[USaveSystemSubsystem::HandleCreateNewGameCompleted] CREATED  %s - UserIndex: %d"), *SlotName, UserIndex);
		SaveGameCreatedCompleted.Broadcast(true);
	}
	else
	{
		UE_LOGFMT(LogCoffeeShopSim, Log, "[USaveSystemSubsystem::HandleCreateNewGameCompleted] NOT CREATED  {SlotName} - UserIndex: {UserIndex}", SlotName, UserIndex);	
		//UE_LOG(LogTemp, Warning, TEXT("[USaveSystemSubsystem::HandleCreateNewGameCompleted] NOT CREATED %s - UserIndex: %d"), *SlotName, UserIndex);
		SaveGameCreatedCompleted.Broadcast(false);
	}
}

void USaveSubsystem::LoadSaveGames()
{
	SaveGameList.Empty();
	SaveGameSlotToLoad.Empty();
	for (int i = 0; i < MaxSaveGames; i++)
	{
		FString intToString = FString::FromInt(i);
		FString SaveGameName = SAVE_DATA + intToString;

		if (UGameplayStatics::DoesSaveGameExist(SaveGameName, CurrentUserIndex))
		{
			SaveGameSlotToLoad.Add(SaveGameName);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("[USaveSubsystem::Initialize] Number Savegames %d "), SaveGameSlotToLoad.Num());

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
	if (LoadedGameData == nullptr)
	{
		LoadAllSaveGamesCompleted.Broadcast(false);
		return;
	}
	
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