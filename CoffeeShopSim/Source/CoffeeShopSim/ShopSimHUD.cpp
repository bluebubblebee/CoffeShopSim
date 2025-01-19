// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopSimHUD.h"
#include "CoffeeShopSim/Input/InputNavigationInterface.h"
#include "Blueprint/UserWidget.h"

bool AShopSimHUD::IsOnGameMenu()
{
	if ((ActiveGameMenu != nullptr) && (CurrentMenu != EGameMenuType::VE_NONE))
	{
		return true;
	}
	return false;
}

void AShopSimHUD::SetActiveGameMenu(UUserWidget* Widget, EGameMenuType MenuType)
{
	if (Widget == nullptr)
	{
		ActiveGameMenu = nullptr;
		CurrentMenu = EGameMenuType::VE_NONE;
	}
	else
	{
		if (ActiveGameMenu != nullptr)
		{
			LastActiveGameMenu = ActiveGameMenu;
			LastActiveMenuType = CurrentMenu;
		}

		CurrentMenu = MenuType;
		ActiveGameMenu = Widget;
	}
}

void AShopSimHUD::TopFaceButtonPress()
{
	if (ActiveGameMenu == nullptr)
	{
		return;
	}
	
	if (ActiveGameMenu->GetClass()->ImplementsInterface(UInputNavigationInterface::StaticClass()))
	{
		IInputNavigationInterface::Execute_OnTopFaceButton(ActiveGameMenu);
	}	
}
void AShopSimHUD::RightFaceButtonPress()
{
	if (ActiveGameMenu == nullptr)
	{
		return;
	}
	
	if (ActiveGameMenu->GetClass()->ImplementsInterface(UInputNavigationInterface::StaticClass()))
	{
		IInputNavigationInterface::Execute_OnRightFaceButton(ActiveGameMenu);
	}	
}

void AShopSimHUD::BottomFaceButtonPress()
{
	if (ActiveGameMenu == nullptr)
	{
		return;
	}
	
	if (ActiveGameMenu->GetClass()->ImplementsInterface(UInputNavigationInterface::StaticClass()))
	{
		IInputNavigationInterface::Execute_OnBottomFaceButton(ActiveGameMenu);
	}	
}

void AShopSimHUD::LeftFaceButtonPress()
{
	if (ActiveGameMenu == nullptr)
	{
		return;
	}
	
	if (ActiveGameMenu->GetClass()->ImplementsInterface(UInputNavigationInterface::StaticClass()))
	{
		IInputNavigationInterface::Execute_OnLeftFaceButton(ActiveGameMenu);
	}	
	
}

void AShopSimHUD::RightShoulderButtonPress()
{
	if (ActiveGameMenu == nullptr)
	{
		return;
	}
	
	if (ActiveGameMenu->GetClass()->ImplementsInterface(UInputNavigationInterface::StaticClass()))
	{
		IInputNavigationInterface::Execute_OnRightShoulderButton(ActiveGameMenu);
	}	
}

void AShopSimHUD::LeftShoulderButtonPress()
{
	if (ActiveGameMenu == nullptr)
	{
		return;
	}
	
	if (ActiveGameMenu->GetClass()->ImplementsInterface(UInputNavigationInterface::StaticClass()))
	{
		IInputNavigationInterface::Execute_OnLeftShoulderButton(ActiveGameMenu);
	}	
}

void AShopSimHUD::NavigateInMenu(EKeyDirection Direction)
{
	if (ActiveGameMenu == nullptr)
	{
		return;
	}

	if (ActiveGameMenu->GetClass()->ImplementsInterface(UInputNavigationInterface::StaticClass()))
	{
		IInputNavigationInterface::Execute_OnDirectionNavigation(ActiveGameMenu, Direction);
	}	
}