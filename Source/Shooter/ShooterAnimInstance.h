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
	// the base class has a nativeUpdateAnimation but we will ues our own
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float Deltatime);

	// this is like the begin play in the Actor class
	virtual void NativeInitializeAnimation() override;

	// the anineinstance and the blueprint must have a reference to the character

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class AShooterCharacter* ShooterCharacter;
	
};
