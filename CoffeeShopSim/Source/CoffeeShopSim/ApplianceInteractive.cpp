// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplianceInteractive.h"
#include "CoffeeShopSimCharacter.h"
#include "ShopManager.h"
#include "CoffeeShopSimGameMode.h"

void AApplianceInteractive::OnInteract_Implementation()
{	
}

bool AApplianceInteractive::TryToSelectRecipe_Implementation()
{
	MainGameMode = Cast<ACoffeeShopSimGameMode>(GetWorld()->GetAuthGameMode());

	if ((MainGameMode == nullptr) || (MainGameMode->ShopManager == nullptr)) return false;

	if ((PlayerCharacter == nullptr) || (!PlayerCharacter->bHasItemOnHands)) return false;

	for (int i = 0; i < RecipeIDList.Num(); i++)
	{
		bool bFoundRecipe = false;
		FRecipe Recipe = MainGameMode->ShopManager->FindRecipe(RecipeIDList[i], bFoundRecipe);

		if (bFoundRecipe)
		{
			for (int j = 0; j < Recipe.RequiredItems.Num(); j++)
			{
				if (Recipe.RequiredItems[i] == PlayerCharacter->ItemOnHands.ItemID)
				{
					PlayerCharacter->OnGiveItem();

					PlayerCharacter->ChangeAnimation("Interact");

					return true;
				}
			}
		}


		/*if (RecipeList[i].ItemNeeded == PlayerCharacter->ItemOnHands.ItemID)
		{
			RecipeSelected = RecipeList[i];

			PlayerCharacter->OnGiveItem();

			PlayerCharacter->ChangeAnimation("Interact");

			return true;

		}*/
	}


	

	// Check list of recipes and find the one that corresponds with items on hands
	/*for (int i = 0; i < RecipeList.Num(); i++)
	{
		if (RecipeList[i].ItemNeeded == PlayerCharacter->ItemOnHands.ItemID)
		{
			RecipeSelected = RecipeList[i];

			PlayerCharacter->OnGiveItem();

			PlayerCharacter->ChangeAnimation("Interact");

			return true;

		}
	}*/

	return false;
}




bool AApplianceInteractive::GiveRecipeToPlayer_Implementation()
{	
	if (PlayerCharacter == nullptr) return false;
	
	PlayerCharacter->OnReceiveItem(RecipeSelected.ItemProduced);

	PlayerCharacter->ChangeAnimation("Idle");

	return true;
	
}