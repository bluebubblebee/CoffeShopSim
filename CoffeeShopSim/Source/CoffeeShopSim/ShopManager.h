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

public:
	UPROPERTY(BlueprintReadWrite, Category = "Shop Manager")
	class ACoffeeShopSimCharacter* Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Manager")
	TArray<class ANPCCustomer*> CustomerPoolList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop Manager")
	class ADoorInteractive* DoorInteractive;

	UPROPERTY(BlueprintReadWrite, Category = "Shop Manager")
	class ANPCCustomer* CurrentCustomerAtCounter;	

public:
	UFUNCTION(BlueprintCallable, Category = "Customer Order")
	void SetCurrentCustomer(class ANPCCustomer* Customer);

	UFUNCTION(BlueprintCallable, Category = "Customer Order")
	bool CheckIfCurrentOrderCompleted(FName ItemID);
};
