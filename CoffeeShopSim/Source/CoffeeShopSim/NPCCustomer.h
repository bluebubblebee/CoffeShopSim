

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Definitions.h"
#include "NPCCustomer.generated.h"

UCLASS()
class COFFEESHOPSIM_API ANPCCustomer : public ACharacter
{
	GENERATED_BODY()

public:

	ANPCCustomer();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cutomer Info")
	FCustomer CustomerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cutomer Info")
	FOrder CurrentOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cutomer Info")
	ECustomerStatus CustomerStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cutomer Info")
	EOrderStatus OrderStatus;

public: 
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Order")
	void OnOrderCompleted();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Order")
	void OnGotoCounter(AActor* CounterLocation, AActor* ObjectToLookAt);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Order")
	void OnGotoWaitLocation(FVector WaitLocation, AActor* ObjectToLookAt);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Order")
	void OnExitShop();
};
