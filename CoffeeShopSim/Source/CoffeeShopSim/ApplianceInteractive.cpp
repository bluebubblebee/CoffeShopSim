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
	if (ShopManager == nullptr) return false;

	if ((PlayerCharacter == nullptr) || (!PlayerCharacter->bHasItemOnHands)) return false;

	for (int i = 0; i < RecipeIDList.Num(); i++)
	{
		bool bFoundRecipe = false;
		FRecipe Recipe = ShopManager->FindRecipe(RecipeIDList[i], bFoundRecipe);

		if (bFoundRecipe)
		{
			for (int j = 0; j < Recipe.RequiredIngredients.Num(); j++)
			{
				if (Recipe.RequiredIngredients[i].ID == PlayerCharacter->ItemOnHands.ItemID)
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
	
	if (ShopManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[GiveRecipeToPlayer]: ShopManager hasn't been initialize for %s"), *InteractiveName.ToString());
		return false;
	}
	
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