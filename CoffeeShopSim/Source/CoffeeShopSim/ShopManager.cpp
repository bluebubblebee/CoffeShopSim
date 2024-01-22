// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopManager.h"
#include "Kismet/GameplayStatics.h"
#include "Definitions.h"
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

FCustomer AShopManager::FindCustomer(FName CustomerID, bool& Found)
{
	Found = false;
	FCustomer Customer;

	if (ShopDatabase != nullptr)
	{
		for (int32 i = 0; i < ShopDatabase->CustomerList.Num(); i++)
		{
			if (ShopDatabase->CustomerList[i].CustomerID == CustomerID)
			{
				Found = true;
				return ShopDatabase->CustomerList[i];
			}
		}
	}

	return Customer;
}


FOrder AShopManager::FindCustomerOrder(FName OderID, bool& Found)
{
	Found = false;
	FOrder Order;

	if (ShopDatabase != nullptr)
	{
		for (int32 i = 0; i < ShopDatabase->OrderCustomerData.Num(); i++)
		{
			if (ShopDatabase->OrderCustomerData[i].OrderID == OderID)
			{
				Found = true;
				return ShopDatabase->OrderCustomerData[i];
			}
		}
	}

	return Order;

}

FItem AShopManager::FindItem(FName ItemID, bool& Found)
{
	Found = false;
	FItem Item;

	if (ShopDatabase != nullptr)
	{
		for (int32 i = 0; i < ShopDatabase->ItemData.Num(); i++)
		{
			if (ShopDatabase->ItemData[i].ItemID == ItemID)
			{
				Found = true;
				return  ShopDatabase->ItemData[i];
			}
		}
	}

	return Item;
}

FRecipe AShopManager::FindRecipe(FName RecipeID, bool& Found)
{
	Found = false;
	FRecipe Recipe;

	if (ShopDatabase != nullptr)
	{
		for (int32 i = 0; i < ShopDatabase->RecipeData.Num(); i++)
		{
			if (ShopDatabase->RecipeData[i].RecipeID == RecipeID)
			{
				Found = true;
				return ShopDatabase->RecipeData[i];
			}
		}
	}

	return Recipe;
}

void AShopManager::SetCurrentCustomer(class ANPCCustomer* Customer)
{
	CurrentCustomerAtCounter = Customer;

	if (CurrentCustomerAtCounter != nullptr)
	{
		bool bCustomerFound = false;
		CurrentCustomerAtCounter->CustomerInfo = FindCustomer(CurrentCustomerAtCounter->CustomerID, bCustomerFound);

		bool bOrderFound = false;
		CurrentCustomerAtCounter->CurrentOrder = FindCustomerOrder(CurrentCustomerAtCounter->CustomerOrderID, bOrderFound);
	}
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
		FItemOrder ItemOrder = CurrentCustomerAtCounter->CurrentOrder.OrderItems[i];
		if (ItemOrder.Completed)
		{
			bool bItemFound = false;
			FItem Item = FindItem(ItemOrder.ItemID, bItemFound);

			if (bItemFound)
			{
				itemsCompleted++;
				Coins += Item.Price;
			}
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


