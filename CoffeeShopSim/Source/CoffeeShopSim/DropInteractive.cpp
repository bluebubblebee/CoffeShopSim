// Fill out your copyright notice in the Description page of Project Settings.


#include "DropInteractive.h"
#include "CoffeeShopSimCharacter.h"

void ADropInteractive::OnInteract_Implementation()
{
	if (LockInteractive) return;

	if ((PlayerCharacter == nullptr) || (!PlayerCharacter->bHasItemOnHands)) return;

	if (ItemsOnInteractive.Num() >= MaxItems) return;	

	PlayerCharacter->OnGiveItem();
	PlayerCharacter->ChangeAnimation("Idle");

	ItemsOnInteractive.Add(PlayerCharacter->ItemOnHands);
	OnItemDropped(PlayerCharacter->ItemOnHands);

	return;
		
}
