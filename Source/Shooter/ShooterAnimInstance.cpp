// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"

void UpdateAnimationProperties(float Deltatime)
{

}


void UShooterAnimInstance::NativeInitializeAnimation()
{
	// 
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}
