// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnimInstance.h"


void UCharacterAnimInstance::ChangeAnimation(FName NewAnimation)
{
	if (CurrentAnimation != NewAnimation)
	{
		CurrentAnimation = NewAnimation;
	}
}
