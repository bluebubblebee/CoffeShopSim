// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicInteractive.h"
#include "Interactable.h"
#include "DoorInteractive.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegateDoorOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegateDoorClose);

UCLASS()
class COFFEESHOPSIM_API ADoorInteractive : public ABasicInteractive, public IInteractable
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	bool bIsOpen;

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FDelegateDoorOpen OnDoorOpened;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Events")
	FDelegateDoorClose OnDoorClosed;
};
