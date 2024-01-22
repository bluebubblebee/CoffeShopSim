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
					RecipeSelected = Recipe;

					PlayerCharacter->OnGiveItem();

					PlayerCharacter->ChangeAnimation("Interact");

					return true;
				}
			}
		}
	}

	return false;
}




bool AApplianceInteractive::GiveRecipeToPlayer_Implementation()
{	
	if (PlayerCharacter == nullptr) return false;
	
	if (ShopManager == nullptr) return false;
	
	bool bItemFound = false;
	FItem ItemResult = ShopManager->FindItem(RecipeSelected.ItemResult, bItemFound);
	
	if (bItemFound)
	{
		PlayerCharacter->OnReceiveItem(ItemResult);
		PlayerCharacter->ChangeAnimation("Idle");
		return true;
	}

	return false;
	
}