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
	if (CurrentInteractiveActor != nullptr)
	{
		// Execute the interact event
		UE_LOG(LogTemp, Warning, TEXT("[Interact]: %s"), *CurrentInteractiveActor->GetName());
		IInteractable::Execute_OnInteract(CurrentInteractiveActor);
	}	
}

void ACoffeeShopSimCharacter::OnEnterInteractive_Implementation(AActor* InteractiveActor, FName InteractiveName)
{	
	if (InteractiveActor == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("[OnEnterInteractive] Called: %s"), *InteractiveName.ToString());
	
	bool bIsInteractive = UKismetSystemLibrary::DoesImplementInterface(InteractiveActor, UInteractable::StaticClass());
	if (bIsInteractive)
	{
		InteractiveList.AddUnique(InteractiveActor);
		if (InteractiveList.Num() == 1)
		{
			SetCurrentInteractive(InteractiveActor);
		}

		UE_LOG(LogTemp, Warning, TEXT("[OnEnterInteractive] InteractiveActor %s IsInteractive - InteractiveList.Num():%d"), *InteractiveActor->GetName(), InteractiveList.Num());

		for (int i = 0; i < InteractiveList.Num(); i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("[OnEnterInteractive] InteractiveList[i]: %s"), *InteractiveList[i]->GetName());
		}

		//CurrentInteractiveActor = InteractiveActor;
		//CurrentInteractive = Cast<IInteractable>(InteractiveActor);
	}	
}

void ACoffeeShopSimCharacter::OnLeaveInteractive_Implementation(class AActor* InteractiveActor)
{	

	if (InteractiveActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[OnLeaveInteractive] InteractiveActor is null"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[OnLeaveInteractive] Leaving...: %s"), *InteractiveActor->GetName());

	for (int i = 0; i < InteractiveList.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("[OnLeaveInteractive] InteractiveList[i]: %s"), *InteractiveList[i]->GetName());

		if (InteractiveList[i] == InteractiveActor)
		{
			if (CurrentInteractiveActor == InteractiveActor)
			{
				if (1 < InteractiveList.Num())
				{
					if (i == 0)
					{
						SetCurrentInteractive(InteractiveList[1]);
					}
					else
					{
						SetCurrentInteractive(InteractiveList[i - 1]);
					}
				}
			}

			InteractiveList.RemoveAt(i);

			break;
		}

	}

	if (0 == InteractiveList.Num())
	{
		SetCurrentInteractive(nullptr);		
	}

	for (int i = 0; i < InteractiveList.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("[OnLeaveInteractive] - END InteractiveList[i]: %s"), *InteractiveList[i]->GetName());
	}

	//CurrentInteractive = nullptr;
	//CurrentInteractiveActor = nullptr;
}

void ACoffeeShopSimCharacter::SetCurrentInteractive(AActor* NewInteractive)
{
	CurrentInteractiveActor = NewInteractive;

	if (NewInteractive != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[SetCurrentInteractive]: %s"), *NewInteractive->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[SetCurrentInteractive] NewInteractive is Null "));
	}
	
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
