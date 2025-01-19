#include "InputNavigationInterface.h"

void IInputNavigationInterface::OnInitialize_Implementation(EPlatformType Platform, EInputController CurrentInput) {}

void IInputNavigationInterface::OnControllerConnectionChange_Implementation() {}

void IInputNavigationInterface::OnControllerChanged_Implementation(EInputController Controller) {}

void IInputNavigationInterface::OnTopFaceButton_Implementation() {}
void IInputNavigationInterface::OnRightFaceButton_Implementation() {}
void IInputNavigationInterface::OnBottomFaceButton_Implementation() {}
void IInputNavigationInterface::OnLeftFaceButton_Implementation() {}
void IInputNavigationInterface::OnRightShoulderButton_Implementation() {}
void IInputNavigationInterface::OnLeftShoulderButton_Implementation() {}

void IInputNavigationInterface::OnDirectionNavigation_Implementation(EKeyDirection Direction) {}
