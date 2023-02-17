// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UShooterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	//this is like the tick function on the Actor class
	// blueprintCallable so we can call the function from the event graph
	// the base class has a nativeUpdateAnimation but we will use our own
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float Deltatime);

	// this is like the begin play in the Actor class
	virtual void NativeInitializeAnimation() override;

	// the anineinstance and the blueprint must have a reference to the character

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class AShooterCharacter* ShooterCharacter;

	// The speed of the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;
	
	// whether or not the character is in the air
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	// Whether or not the character is moving
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;

	
};
