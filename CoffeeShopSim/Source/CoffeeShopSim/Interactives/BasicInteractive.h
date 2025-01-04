// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicInteractive.generated.h"

UCLASS()
class COFFEESHOPSIM_API ABasicInteractive : public AActor
{
	GENERATED_BODY()


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive")
	class USceneComponent* RootScene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interactive")
	class UBoxComponent* Trigger;

	UPROPERTY(BlueprintReadWrite, Category = "Interactive")
	class ACoffeeShopSimCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Mode")
	class AShopManager* ShopManager;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	FName InteractiveName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	bool LockInteractive;
	
public:	

	ABasicInteractive();

	virtual void Initialize(class AShopManager* Manager);

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void OnPlayerEnterInteractive();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void OnPlayerLeaveInteractive();
};
