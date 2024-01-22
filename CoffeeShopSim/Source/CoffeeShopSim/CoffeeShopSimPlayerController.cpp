
#include "CoffeeShopSimPlayerController.h"
#include "CoffeeShopSimCharacter.h"
#include "Engine/World.h"

ACoffeeShopSimPlayerController::ACoffeeShopSimPlayerController()
{
	bShowMouseCursor = true;
}


void ACoffeeShopSimPlayerController::BeginPlay()
{
	Super::BeginPlay();

	APawn* const pawn = GetPawn();
	if (pawn != nullptr)
	{
		MyCharacter = Cast<ACoffeeShopSimCharacter>(pawn);
	}
}


void ACoffeeShopSimPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ACoffeeShopSimPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACoffeeShopSimPlayerController::MoveRight);

	// Face button	
	InputComponent->BindAction("Interact", IE_Pressed, this, &ACoffeeShopSimPlayerController::Interact);
}


void ACoffeeShopSimPlayerController::LockInput()
{
	bIsInputLocked = true;
}

void ACoffeeShopSimPlayerController::UnLockInput()
{
	bIsInputLocked = false;
}


void ACoffeeShopSimPlayerController::MoveForward(float Value)
{
	if (bIsInputLocked) return;

	if (MyCharacter != nullptr)
	{
		MyCharacter->MoveForward(Value);
	}
}

void ACoffeeShopSimPlayerController::MoveRight(float Value)
{
	if (bIsInputLocked) return;

	if (MyCharacter != nullptr)
	{
		MyCharacter->MoveRight(Value);
	}
}


void ACoffeeShopSimPlayerController::Interact()
{
	if (bIsInputLocked) return;

	if (MyCharacter != nullptr)
	{
		MyCharacter->Interact();
	}

}
