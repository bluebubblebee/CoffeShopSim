// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definitions.generated.h"


UENUM(BlueprintType)
enum class ECustomerStatus : uint8
{
	VE_None 			     UMETA(DisplayName = "None"),
	VE_StandBy 				 UMETA(DisplayName = "StandBy"),
	VE_GoToCounter 		     UMETA(DisplayName = "GoToCounter"),
	VE_GoToWaitingArea	     UMETA(DisplayName = "GotoWaitingArea"),
	VE_AtWaitingArea 		 UMETA(DisplayName = "AtWaitingArea"),
	VE_ExitShop 		     UMETA(DisplayName = "ExitShop")
};

UENUM(BlueprintType)
enum class EOrderStatus : uint8
{
	VE_None 			     UMETA(DisplayName = "None"),
	VE_WaitingOrder 		 UMETA(DisplayName = "WaitingOrder"),
	VE_OrderCompleted 		 UMETA(DisplayName = "OrderCompleted"),
};


//// Items ///////
USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class AActor> ItemClass;

	FItem(){}
	

};

USTRUCT(BlueprintType)
struct FRecipe
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemNeeded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FItem ItemProduced;

	FRecipe(){}
};


//// Customer ///////
USTRUCT(BlueprintType)
struct FCustomer
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName CustomerID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* CustomerProfile;

};


USTRUCT(BlueprintType)
struct FItemOrder
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Coins;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* ItemCompletedIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool Completed;

};


USTRUCT(BlueprintType)
struct FOrder
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName OrderID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<FItemOrder> OrderItems;
};

/**
 * 
 */
class COFFEESHOPSIM_API Definitions
{
public:
	Definitions();
	~Definitions();
};