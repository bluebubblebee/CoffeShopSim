// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupInteractive.h"
#include "CoffeeShopSimCharacter.h"

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

