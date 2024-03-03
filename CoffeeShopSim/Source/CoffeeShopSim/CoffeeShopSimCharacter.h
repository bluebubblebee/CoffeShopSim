// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interactable.h"
#include "Definitions.h"
#include "CoffeeShopSimCharacter.generated.h"

UCLASS(Blueprintable)
class ACoffeeShopSimCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACoffeeShopSimCharacter();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:

	void MoveForward(float Value);
	void MoveRight(float Value);

	void Interact();

public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnEnterInteractive(AActor* InteractiveActor, FName InteractiveName);	
	void OnEnterInteractive_Implementation(AActor* InteractiveActor, FName InteractiveName);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnLeaveInteractive(class AActor* InteractiveActor);
	void OnLeaveInteractive_Implementation(class AActor* InteractiveActor);

protected:

	// Reference to animator
	class UCharacterAnimInstance* Animator = nullptr;

public:

	void ChangeAnimation(FName Animation);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	TArray<TObjectPtr<class AActor>> InteractiveList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	AActor* CurrentInteractiveActor;

	//IInteractable* CurrentInteractive;	

	void SetCurrentInteractive(AActor* NewInteractive);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bHasItemOnHands = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FItem ItemOnHands;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnReceiveItem(FItem Item);
	void OnReceiveItem_Implementation(FItem Item);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void OnGiveItem();
	void OnGiveItem_Implementation();

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Order")
	void OnOpenShop();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Order")
	void OnCloseShop();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	int32 CurrentCoins = 0;

public:	

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Order")
	void OnOrderCompleted(int32 Coins);
	void OnOrderCompleted_Implementation(int32 Coins);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Order")
	void OnOrderItemCompleted(FName ItemID);
};

