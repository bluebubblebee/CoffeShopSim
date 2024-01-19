// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplianceInteractive.h"
#include "CoffeeShopSimCharacter.h"

void AApplianceInteractive::OnInteract_Implementation()
{	
}

bool AApplianceInteractive::TryToSelectRecipe_Implementation()
{
	if ((PlayerCharacter == nullptr) || (!PlayerCharacter->bHasItemOnHands)) return false;

	// Check list of recipes and find the one that corresponds with items on hands
	for (int i = 0; i < RecipeList.Num(); i++)
	{
		if (RecipeList[i].ItemNeeded == PlayerCharacter->ItemOnHands.ItemID)
		{
			RecipeSelected = RecipeList[i];

			PlayerCharacter->OnGiveItem();

			PlayerCharacter->ChangeAnimation("Interact");

			return true;

		}
	}

	return false;
}




bool AApplianceInteractive::GiveRecipeToPlayer_Implementation()
{	
	if (PlayerCharacter == nullptr) return false;
	
	PlayerCharacter->OnReceiveItem(RecipeSelected.ItemProduced);

	PlayerCharacter->ChangeAnimation("Idle");

	return true;
	
}