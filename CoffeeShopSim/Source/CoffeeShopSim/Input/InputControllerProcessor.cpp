
#include "InputControllerProcessor.h"
#include "InputControllerComponent.h"

void FInputControllerProcessor::Tick(const float DeltaTime, FSlateApplication& SlateApp, TSharedRef<ICursor> Cursor)
{
}

bool FInputControllerProcessor::HandleKeyDownEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	if (Controller != nullptr)
	{
		Controller->HandleKeyDownEvent(SlateApp, InKeyEvent);
	}
	return IInputProcessor::HandleKeyDownEvent(SlateApp, InKeyEvent);
}

bool FInputControllerProcessor::HandleKeyUpEvent(FSlateApplication& SlateApp, const FKeyEvent& InKeyEvent)
{
	if (Controller != nullptr)
	{
		Controller->HandleKeyUpEvent(SlateApp, InKeyEvent);
	}

	return IInputProcessor::HandleKeyUpEvent(SlateApp, InKeyEvent);
}

bool FInputControllerProcessor::HandleAnalogInputEvent(FSlateApplication& SlateApp, const FAnalogInputEvent& InAnalogInputEvent)
{
	if (Controller != nullptr)
	{
		//Controller->HandleAnalogInputEvent(SlateApp, InAnalogInputEvent);
	}

	return IInputProcessor::HandleAnalogInputEvent(SlateApp, InAnalogInputEvent);
}

bool FInputControllerProcessor::HandleMouseMoveEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	if (Controller != nullptr)
	{
		Controller->HandleMouseMoveEvent(SlateApp, MouseEvent);
	}

	return IInputProcessor::HandleMouseMoveEvent(SlateApp, MouseEvent);
}

bool FInputControllerProcessor::HandleMouseButtonDownEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	if (Controller != nullptr)
	{
		Controller->HandleMouseButtonDownEvent(SlateApp, MouseEvent);
	}

	return IInputProcessor::HandleMouseButtonDownEvent(SlateApp, MouseEvent);
}

bool FInputControllerProcessor::HandleMouseButtonUpEvent(FSlateApplication& SlateApp, const FPointerEvent& MouseEvent)
{
	if (Controller != nullptr)
	{
		//Controller->HandleMouseButtonUpEvent(SlateApp, MouseEvent);
	}

	return IInputProcessor::HandleMouseButtonUpEvent(SlateApp, MouseEvent);
}

bool FInputControllerProcessor::HandleMouseWheelOrGestureEvent(FSlateApplication& SlateApp, const FPointerEvent& InWheelEvent, const FPointerEvent* InGesture)
{
	if (Controller != nullptr)
	{
		//Controller->HandleMouseWheelOrGestureEvent(SlateApp, InWheelEvent, InGesture);
	}

	return IInputProcessor::HandleMouseWheelOrGestureEvent(SlateApp, InWheelEvent, InGesture);
}