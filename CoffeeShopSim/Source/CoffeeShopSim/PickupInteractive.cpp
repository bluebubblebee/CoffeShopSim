// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupInteractive.h"
#include "CoffeeShopSimCharacter.h"
#include "ShopManager.h"

void APickupInteractive::Initialize(class AShopManager* Manager)
{
	Super::Initialize(Manager);

	if (ShopManager != nullptr)
	{
		bool bFoundItem = false;
		Item = ShopManager->FindItem(ItemID, bFoundItem);
	}
}


void APickupInteractive::OnInteract_Implementation()
{
	if ((PlayerCharacter == nullptr) || (PlayerCharacter->bHasItemOnHands)) return;

	if (PlayerCharacter != nullptr)
	{
		if (PlayerCharacter->bHasItemOnHands)
		{
			return;
		}
		else
		{

			PlayerCharacter->OnReceiveItem(Item);

			PlayerCharacter->ChangeAnimation("Idle");

		}
	}
}

