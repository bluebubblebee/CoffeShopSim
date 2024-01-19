// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopManager.h"
#include "Kismet/GameplayStatics.h"
#include "NPCCustomer.h"
#include "CoffeeShopSimCharacter.h"
#include "CoffeeShopSimGameMode.h"
#include "DoorInteractive.h"

AShopManager::AShopManager()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AShopManager::BeginPlay()
{
	Super::BeginPlay();	

	// Fetch reference to the player
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC != nullptr)
	{
		APawn* Pawn = PC->GetPawn();

		if (Pawn != nullptr)
		{
			Player = Cast<ACoffeeShopSimCharacter>(Pawn);
		}
	}


	// Send reference of this actor to GameMode
	ACoffeeShopSimGameMode* GameMode = (ACoffeeShopSimGameMode*)GetWorld()->GetAuthGameMode();
	if (GameMode != nullptr)
	{
		GameMode->RegisterShopManager(this);
	}	
}

void AShopManager::SetCurrentCustomer(class ANPCCustomer* Customer)
{
	CurrentCustomerAtCounter = Customer;
}


bool AShopManager::CheckIfCurrentOrderCompleted(FName ItemID)
{
	if (CurrentCustomerAtCounter == nullptr)
	{
		return false;
	}

	// Find the ItemID on the OrderItems in the CurrentOrder
	for (int i = 0; i < CurrentCustomerAtCounter->CurrentOrder.OrderItems.Num(); i++)
	{
		if (ItemID == CurrentCustomerAtCounter->CurrentOrder.OrderItems[i].ItemID)
		{
			// Mark this item as completed on the current order
			CurrentCustomerAtCounter->CurrentOrder.OrderItems[i].Completed = true;

			break;
		}
	}

	if (Player != nullptr)
	{
		Player->OnOrderItemCompleted(ItemID);
	}

	// Check if all items have been completed
	int itemsCompleted = 0;
	int Coins = 0;
	for (int i = 0; i < CurrentCustomerAtCounter->CurrentOrder.OrderItems.Num(); i++)
	{
		if (CurrentCustomerAtCounter->CurrentOrder.OrderItems[i].Completed)
		{
			itemsCompleted++;
			Coins += CurrentCustomerAtCounter->CurrentOrder.OrderItems[i].Coins;
		}
	}

	// Notify the customer and the player
	if (itemsCompleted == CurrentCustomerAtCounter->CurrentOrder.OrderItems.Num())
	{
		if (Player != nullptr)
		{
			Player->OnOrderCompleted(Coins);
		}

		CurrentCustomerAtCounter->OnOrderCompleted();

		CurrentCustomerAtCounter = nullptr;

		return true;
	}

	return false;
}


