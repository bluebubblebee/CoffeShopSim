// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShopManager.generated.h"

UCLASS()
class COFFEESHOPSIM_API AShopManager : public AActor
{
	GENERATED_BODY()	
public:	

	AShopManager();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shop Manager")
	class UShopData* ShopDatabase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shop Manager")
	class UCustomerData* CustomerDatabase;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Shop Manager")
	class ACoffeeShopSimCharacter* Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Manager")
	TArray<class ANPCCustomer*> CustomerPoolList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Manager")
	TArray<class ABasicInteractive*> InteractiveList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Manager")
	class ADoorInteractive* DoorInteractive;

	UPROPERTY(BlueprintReadWrite, Category = "Shop Manager")
	class ANPCCustomer* CurrentCustomerAtCounter;	

public:
	UFUNCTION(BlueprintCallable, Category = "Customer Order")
	FItem FindItem(FName ItemID, bool& Found);

	UFUNCTION(BlueprintCallable, Category = "Customer Order")
	FRecipe FindRecipe(FName RecipeID, bool& Found);

	UFUNCTION(BlueprintCallable, Category = "Customer Order")
	FRecipe FindRecipeByIngredients(const TArray<FRecipeIngredient>& IngredientList, ERecipeType RecipeType, bool& Found);
	

public:

	UFUNCTION(BlueprintCallable, Category = "Customer Order")
	FCustomer FindCustomer(FName CustomerID, bool& Found);

	UFUNCTION(BlueprintCallable, Category = "Customer Order")
	FOrder FindCustomerOrder(FName OderID, bool& Found);

public:
	UFUNCTION(BlueprintCallable, Category = "Customer Order")
	void SetCurrentCustomer(class ANPCCustomer* Customer);

	UFUNCTION(BlueprintCallable, Category = "Customer Order")
	bool CheckIfCurrentOrderCompleted(FName ItemID);
};
