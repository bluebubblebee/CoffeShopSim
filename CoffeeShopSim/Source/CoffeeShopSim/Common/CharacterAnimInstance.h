// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class COFFEESHOPSIM_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
	float Speed;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
	float AlphaLeftArm = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
	float AlphaRigthArm = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Settings")
	FName CurrentAnimation = "IDLE";


public:

	void SetAlphaRightArm(bool Value) { AlphaRigthArm = Value; }
	void SetAlphaLeftArm(bool Value) { AlphaLeftArm = Value; }

	void ChangeAnimation(FName NewAnimation);
	
};
