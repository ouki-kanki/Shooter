// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Engine/SkeletalMeshSocket.h"

// Sets default values
AShooterCharacter::AShooterCharacter() :
	BaseTurnRate(45.f),
	BaseLookUpRate(45.f)
	/**  
		TODO: have to check this!
		if baseLookupRate was a class or it was a constant
		this would make sense because with list initialization we avoid calling the default constructor but in this case i don't undestand why 
		we use list initialization,


	
	**/
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Crreates a camera boom (pulls in towards the character if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.f; // distance behind the character

	//in order to follow the controller
	CameraBoom->bUsePawnControlRotation = true;

	//Create FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // socketname is the socket at the end of the boom in which the camera will attach.

	// camera does not rotate relative to the arm 
	FollowCamera->bUsePawnControlRotation = false;

	// With this the controller only affect the camera
	bUseControllerRotationPitch = false; // don't use the controller pitch for the character mesh
	bUseControllerRotationYaw = false; // dont't use yaw
	bUseControllerRotationRoll = false; // don't use roll

	// Configure character movement
	// Rotate the character to the direction of movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f); // yaw value
	
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 1.f;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();


	int myInt{ 42 };

	// *// (int) num -> c style casting
	// braced initialization -> good practice because it will always initialize and prevent narrow convertion (the compiler will give error)
	// 
	// the % is called format specifier  %d for int, %f for floats.
	UE_LOG(LogTemp, Warning, TEXT("hello there, this is the int: %d"), myInt);

	float myFloat{ 3.14159f };
	UE_LOG(LogTemp, Warning, TEXT("hello there, this is the float: %f"), myFloat);

	double myDouble{ 0.0007565 };
	UE_LOG(LogTemp, Warning, TEXT("hello there, this is the double: %lf"), myDouble);

	char myChar{ 'J' };
	UE_LOG(LogTemp, Warning, TEXT("hello there, this is the char: %c"), myChar);

	wchar_t wideChar{ L'J' };
	UE_LOG(LogTemp, Warning, TEXT("hello there, this is the wideChar: %lc"), wideChar);

	bool myBool{ true };
	// bool can convert to int 
	UE_LOG(LogTemp, Warning, TEXT("hello there, this is the bool: %d"), myBool);

	// fsting is an object so we cannot pass fstring directly
	FString myString{ TEXT("MY String!!") };
	// the asterisk here is an overloaded operator and not pointer dereference. it convers the objext ot an old c style string
	UE_LOG(LogTemp, Warning, TEXT("hello there, this is the string: %s"), *myString);
	UE_LOG(LogTemp, Warning, TEXT("hello there, this is the string: %s"), *GetName());

}

void AShooterCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 }; // we don't need the pitch and the roll 

		const FVector Direction{ FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::X) };
		// the value input is from the input controller .(w) 1 for forward (s) -1 for backwards
		AddMovementInput(Direction, Value); // scale by value . (for backwards the value will be -1)
	}
}

void AShooterCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation{ Controller->GetControlRotation() };
		const FRotator YawRotation{ 0, Rotation.Yaw, 0 }; // we don't need the pitch and the roll 

		const FVector Direction{ FRotationMatrix{ YawRotation }.GetUnitAxis(EAxis::Y) }; // Y is the right vector 
		// the value input is from the input controller .(w) 1 for forward (s) -1 for backwards
		AddMovementInput(Direction, Value); // scale by value . (for backwards the value will be -1)
	}
}

void AShooterCharacter::TurnAtRate(float Rate)
{
	// BaseTurnRate is in degrees per second and DeltaTime is seconds per frame -- > thus Rate will be degrees per frame in this manner we can provide the controller input with the correct unit
	// this will affect the controllers yaw
	// GetWorld()->GetDeltaSeconds() will give the DeltaTime
	// Rate values are from 0 to 1 in relation of how much we are pressing the thumstick
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::FireWeapon()
{
	if (FireSound)
	{
		UGameplayStatics::PlaySound2D(this, FireSound);
	}

	const USkeletalMeshSocket* BarrelSocket = GetMesh()->GetSocketByName("BarrelSocket");

	if (BarrelSocket)
	{
		const FTransform SocketTransform = BarrelSocket->GetSocketTransform(GetMesh()); // this contains location rotation and scale data

		if (MuzzleFlash)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, SocketTransform);
		}
	}
}

void AShooterCharacter::AlterFireWeapon()
{
	if (LazerSound)
	{
		UGameplayStatics::PlaySound2D(this, LazerSound);
	}

	const USkeletalMeshSocket* BarrelSocket = GetMesh()->GetSocketByName("BarrelSocket");

	if (BarrelSocket)
	{
		const FTransform SocketTransform = BarrelSocket->GetSocketTransform(GetMesh()); // this contains location rotation and scale data

		if (LazerParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LazerParticle, SocketTransform);
		}
	}
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent); // the check macro checks if the playerinputComponent is valid

	// here we can bind the inputs from the controller to the respected functions

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRate", this, &AShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AShooterCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	PlayerInputComponent->BindAction("FireButton", IE_Pressed, this, &AShooterCharacter::FireWeapon);
	PlayerInputComponent->BindAction("AlterFireButton", IE_Pressed, this, &AShooterCharacter::AlterFireWeapon);
}

