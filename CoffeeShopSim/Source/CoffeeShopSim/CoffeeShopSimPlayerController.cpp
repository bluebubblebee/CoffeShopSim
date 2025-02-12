
#include "CoffeeShopSimPlayerController.h"
#include "CoffeeShopSimCharacter.h"
#include "ShopSimHUD.h"
#include "CoffeeShopSim/Input/InputControllerComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/World.h"

ACoffeeShopSimPlayerController::ACoffeeShopSimPlayerController()
{
	InputControllerComponent = CreateDefaultSubobject<UInputControllerComponent>(TEXT("InputControllerComponent"));
	bShowMouseCursor = true;
}

void ACoffeeShopSimPlayerController::BeginPlay()
{
	APawn* const pawn = GetPawn();
	if (pawn != nullptr)
	{
		MyCharacter = Cast<ACoffeeShopSimCharacter>(pawn);
	}

	HUD = Cast<AShopSimHUD>(GetHUD());

	if (HUD != nullptr)
	{
		HUD->RegisterSimPlayerController(this);
	}

	if (!InputControllerComponent->OnInputControllerChanged.IsBound())
	{
		InputControllerComponent->OnInputControllerChanged.AddDynamic(this, &ACoffeeShopSimPlayerController::OnControllerChanged);
	}

	// Initialize Input Context
    ChangeMappingContextToInGame();
	Super::BeginPlay();
}

void ACoffeeShopSimPlayerController::OnControllerChanged(EInputController NewInputController)
{
	if (InputControllerComponent->CurrentPlatform != EPlatformType::VE_WINDOWS) return;

	if (InputControllerComponent->CurrentInput != NewInputController)
	{
		//HUD->OnInputControllerChanged(CurrentInput);
	}
}

void ACoffeeShopSimPlayerController::ChangeMappingContextToInGame()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem == nullptr)
	{
		return;
	}

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputControllerComponent->GetInGameMappingContext(), 0);	
}

void ACoffeeShopSimPlayerController::ChangeMappingContextToMenu()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem == nullptr)
	{
		return;
	}

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputControllerComponent->GetMenuMappingContext(), 0);	
}

void ACoffeeShopSimPlayerController::LockInput()
{
	bIsInputLocked = true;
}

void ACoffeeShopSimPlayerController::UnLockInput()
{
	bIsInputLocked = false;
}

void ACoffeeShopSimPlayerController::HandleMovement(const FVector2D& Value)
{
	if (bIsInputLocked || HUD->IsOnGameMenu()) return;

	if (MyCharacter != nullptr)
	{
		MyCharacter->MoveInput(Value);
	}
}

void ACoffeeShopSimPlayerController::HandleFaceTopButton()
{
	if (bIsInputLocked) return;
	if (HUD->IsOnGameMenu())
	{
		HUD->TopFaceButtonPress();
	}
}	

void ACoffeeShopSimPlayerController::HandleFaceRightButton()
{
	if (bIsInputLocked) return;
	if (HUD->IsOnGameMenu())
	{
		HUD->RightFaceButtonPress();
	}
}
	
void ACoffeeShopSimPlayerController::HandleFaceBottomButton()
{
	if (bIsInputLocked) return;

	if (HUD->IsOnGameMenu())
	{
		HUD->BottomFaceButtonPress();
		return;
	}
	
	if (MyCharacter != nullptr)
	{
		MyCharacter->Interact();
	}
}

void ACoffeeShopSimPlayerController::HandleFaceLeftButton()
{
	if (bIsInputLocked) return;
	if (HUD->IsOnGameMenu())
	{
		HUD->LeftFaceButtonPress();
	}
}

void ACoffeeShopSimPlayerController::HandleInputDirection(EKeyDirection Direction)
{
	if (bIsInputLocked) return;
	if (HUD->IsOnGameMenu())
	{
		HUD->NavigateInMenu(Direction);
	}
}

void ACoffeeShopSimPlayerController::HandleRightShoulderButtonInGame()
{
	if (bIsInputLocked) return;
	if (HUD->IsOnGameMenu())
	{
		HUD->RightShoulderButtonPress();
	}
}

void ACoffeeShopSimPlayerController::HandleLeftShoulderButtonInGame()
{
	if (bIsInputLocked) return;
	if (HUD->IsOnGameMenu())
	{
		HUD->LeftShoulderButtonPress();
	}
}

void ACoffeeShopSimPlayerController::HandleMainMenuButtonInGame()
{
	if (bIsInputLocked) return;
	if (HUD->IsOnGameMenu())
	{
		HUD->HideMainMenu();
		ChangeMappingContextToInGame();
	}
	else
	{
		
		HUD->ShowMainMenu();
		ChangeMappingContextToMenu();
	}	
}