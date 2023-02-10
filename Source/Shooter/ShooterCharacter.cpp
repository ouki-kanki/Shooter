// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("hello there"));

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

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

