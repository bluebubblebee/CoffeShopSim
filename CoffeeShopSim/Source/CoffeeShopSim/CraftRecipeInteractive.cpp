// Fill out your copyright notice in the Description page of Project Settings.

#include "CraftRecipeInteractive.h"
#include "ShopManager.h"


bool ACraftRecipeInteractive::TryAddIngredients(const FItem& Item)
{	
	if (ShopManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[TryAddIngredients]: ShopManager hasn't been initialize for %s"), *InteractiveName.ToString());
		return false;
	}

	// Find item
	if (AddedIngredients.Num() == MaxIngredients) return false;

	bool bNewIngredient = true;
	for (int32 i = 0; i < AddedIngredients.Num(); i++)
	{
		if (AddedIngredients[i].ID == Item.ItemID)
		{
			bNewIngredient = false;
			AddedIngredients[i].Quantity += 1;

			UE_LOG(LogTemp, Warning, TEXT("[CraftRecipeInteractive::TryAddIngredients]: Add ingredient: %s - Quantity: %d"), *AddedIngredients[i].ID.ToString(), AddedIngredients[i].Quantity);
		}
	}

	if (bNewIngredient)
	{
		FRecipeIngredient NewIngredient;
		NewIngredient.ID = Item.ItemID;
		NewIngredient.Quantity = 1;
		AddedIngredients.Add(NewIngredient);
		UE_LOG(LogTemp, Warning, TEXT("[CraftRecipeInteractive::TryAddIngredients]: Add new ingredient: %s"), *Item.ItemID.ToString());
	}
	return true;
}

bool ACraftRecipeInteractive::IsRecipeReady()
{
	if (ShopManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[ACraftRecipeInteractive]: ShopManager hasn't been initialize for %s"), *InteractiveName.ToString());
		return false;
	}

	if (PlayerCharacter == nullptr) return false;

	bool bFoundRecipe = false;
	FRecipe Recipe = ShopManager->FindRecipeByIngredients(AddedIngredients, ERecipeType::VE_PrepareRecipe, bFoundRecipe);

	if (bFoundRecipe)
	{
		UE_LOG(LogTemp, Warning, TEXT("[CraftRecipeInteractive::TryAddIngredients]: Recipe %s is Ready - Result: %s"), *Recipe.RecipeID.ToString(), *Recipe.ItemResult.ToString());

		bool bItemFound = false;
		FItem ItemResult = ShopManager->FindItem(Recipe.ItemResult, bItemFound);

		if (bItemFound)
		{
			AddedIngredients.Empty();

			PlayerCharacter->OnReceiveItem(ItemResult);
			PlayerCharacter->ChangeAnimation("Idle");
			return true;
		}
	}

	return false;
}