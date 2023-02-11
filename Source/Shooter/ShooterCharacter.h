// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// thx to forward delclaration we don't have to include the particular clas to the header, we will include it later to the .cpp file
	// with the keyword class we make a promise to the compiler that we will include the class later
	// UPROPERTY marks the property for garbage collection as well as it exposes it for blueprint
	// Visible Anywhere makes the property available in blueprint details and in the instance created in the editor 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))	
	// camera boom is used to attach a camera to the character, positioning the camera behind the character
	class USpringArmComponent* CameraBoom;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	// with the forceinline the call of the function will litterally replaced with the statement inside the body.

	// REturns CameraBoom subobject
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; };

	/** REturns FollowCamera subobject  */
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; };

};
