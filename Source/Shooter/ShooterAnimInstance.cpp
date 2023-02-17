// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// like the tick method 
void UShooterAnimInstance::UpdateAnimationProperties(float Deltatime)
{
	// every given frame in shooterCharacter is null it will try to get it again 
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if (ShooterCharacter) // check if the cast was successfull
	{
		// Get the lateral speed of the character from velocity
		FVector Velocity{ ShooterCharacter->GetVelocity() }; // this is a local variable
		
		Velocity.Z = 0; // we don't need velocity on the z axis
		Speed = Velocity.Size(); // speed is the magnitude of the Fvector // magnitude normally is calculated with the pythagoream theorem sqr((x2 - x1) + (y2 - y1))


		// Check if the character is the air
		bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling(); // this returns a boolean that is true if the character is falling

		// We have to check if the character is accelarating.Normally  Acceleration is the change in velocity 
		// if a character is moving with a constant speed the accelaration is 0. but hear for simplicity we will accept that if the character is moving we have acceleration 
		// from the shootercharacter we get character movement component which has the getCurrentAcceleration which gives back a vector 
		// The Accelaration is a vector so in order to we can check for the size of the vector (magnitude)
		if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		} 
		else
		{
			bIsAccelerating = false;
		}


	}
}


// like the begin play 
void UShooterAnimInstance::NativeInitializeAnimation()
{
	// have to cast the pawn to shootercharacter
	// will store the pawn address to ShooterCharacter pointer
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}
