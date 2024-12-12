// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SaveGameDefinitions.h"
#include "SaveSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSaveSubsystemSaveGameCreated, bool, Success);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSaveSubsystemLoadAllSaveGames, bool, Success);

UCLASS()
class COFFEESHOPSIM_API USaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USaveSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Save System")
	FSaveSubsystemSaveGameCreated SaveGameCreatedCompleted;

	UFUNCTION(BlueprintCallable, Category = "Save System")
	void CreateNewSaveGame();

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Save System")
	FSaveSubsystemLoadAllSaveGames LoadAllSaveGamesCompleted;

	UFUNCTION(BlueprintCallable, Category = "Save System")
	void LoadSaveGames();

public:

	static const FString SAVE_DATA;
	static const int32 MaxSaveGames = 5;

protected:

	UFUNCTION()
	void HandleLoadSaveSaveGameCompleted(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

	UFUNCTION()
	void HandleCreateNewGameCompleted(const FString& SlotName, const int32 UserIndex, bool bSuccess);

private:

	int32 CurrentUserIndex = 0;
	int32 NextSlotToLoad = 0;

	TArray<FString> SaveGameSlotToLoad;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Save System")
	TArray<TObjectPtr<UMainSaveGame>> SaveGameList;

	UPROPERTY(BlueprintReadOnly, Category = "Save System")
	TObjectPtr<UMainSaveGame> LastSaveGameCreated;
};
