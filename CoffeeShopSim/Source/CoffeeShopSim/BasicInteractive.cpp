// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicInteractive.h"
#include "Components/BoxComponent.h"
#include "CoffeeShopSimGameMode.h"
#include "CoffeeShopSimGameMode.h"


ABasicInteractive::ABasicInteractive()
{ 
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	//Trigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABasicInteractive::BeginOverlap);
	//Trigger->OnComponentEndOverlap.AddUniqueDynamic(this, &ABasicInteractive::EndOverlap);

	PrimaryActorTick.bCanEverTick = true;

}

void ABasicInteractive::BeginPlay()
{
	Super::BeginPlay();

	LockInteractive = false;	
}

void ABasicInteractive::Initialize(class AShopManager* Manager)
{
	ShopManager = Manager;
}



