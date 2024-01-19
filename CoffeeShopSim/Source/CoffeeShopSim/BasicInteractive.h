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


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	FName InteractiveName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactive")
	bool LockInteractive;
	
public:	

	ABasicInteractive();

protected:

	virtual void BeginPlay() override;


	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult);



	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void OnPlayerEnterInteractive();
	

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void OnPlayerLeaveInteractive();



};
