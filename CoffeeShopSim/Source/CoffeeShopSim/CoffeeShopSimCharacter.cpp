// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoffeeShopSimCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "CharacterAnimInstance.h"


ACoffeeShopSimCharacter::ACoffeeShopSimCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}


void ACoffeeShopSimCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetMesh() != nullptr)
	{
		Animator = Cast<UCharacterAnimInstance>(GetMesh()->GetAnimInstance());
	}
}

void ACoffeeShopSimCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}


void ACoffeeShopSimCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void ACoffeeShopSimCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}

}

void ACoffeeShopSimCharacter::Interact()
{
	if (CurrentInteractive != nullptr)
	{
		// Execute the interact event
		IInteractable::Execute_OnInteract(CurrentInteractiveActor);
	}
}

void ACoffeeShopSimCharacter::OnEnterInteractive_Implementation(AActor* InteractiveActor, FName InteractiveName)
{
	if (InteractiveActor != nullptr)
	{
		bool IsInterface = UKismetSystemLibrary::DoesImplementInterface(InteractiveActor, UInteractable::StaticClass());
		if (IsInterface)
		{
			CurrentInteractiveActor = InteractiveActor;

			CurrentInteractive = Cast<IInteractable>(InteractiveActor);
		}
	}
}

void ACoffeeShopSimCharacter::OnLeaveInteractive_Implementation()
{
	CurrentInteractive = nullptr;
	CurrentInteractiveActor = nullptr;
}


void ACoffeeShopSimCharacter::ChangeAnimation(FName AnimationName)
{	
	if (Animator != nullptr)
	{
		Animator->ChangeAnimation(AnimationName);
	}	
}

void ACoffeeShopSimCharacter::OnReceiveItem_Implementation(FItem Item)
{
	if (!bHasItemOnHands)
	{
		bHasItemOnHands = true;

		ItemOnHands = Item;

		if (Animator != nullptr)
		{
			Animator->SetAlphaRightArm(true);
			Animator->SetAlphaLeftArm(true);
		}
	}
}

void ACoffeeShopSimCharacter::OnGiveItem_Implementation()
{
	if (bHasItemOnHands)
	{
		bHasItemOnHands = false;

		if (Animator != nullptr)
		{
			Animator->SetAlphaRightArm(false);
			Animator->SetAlphaLeftArm(false);
		}
	}
}


void ACoffeeShopSimCharacter::OnOrderCompleted_Implementation(int32 Coins)
{
	CurrentCoins += Coins;
}
