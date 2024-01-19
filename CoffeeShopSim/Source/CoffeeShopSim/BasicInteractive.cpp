// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicInteractive.h"
#include "Components/BoxComponent.h"
#include "CoffeeShopSimCharacter.h"


ABasicInteractive::ABasicInteractive()
{ 
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	Trigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABasicInteractive::BeginOverlap);
	Trigger->OnComponentEndOverlap.AddUniqueDynamic(this, &ABasicInteractive::EndOverlap);

	PrimaryActorTick.bCanEverTick = true;

}


void ABasicInteractive::BeginPlay()
{
	Super::BeginPlay();

	LockInteractive = false;
	
}

void ABasicInteractive::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	PlayerCharacter = Cast<ACoffeeShopSimCharacter>(OtherActor);

	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->OnEnterInteractive(this, InteractiveName);

		OnPlayerEnterInteractive();
	}
}




void ABasicInteractive::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->OnLeaveInteractive();

		OnPlayerLeaveInteractive();
	}
}



