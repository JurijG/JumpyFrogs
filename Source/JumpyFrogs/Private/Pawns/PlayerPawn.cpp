// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Pawns/PlayerPawn.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MainPawnDummy"));
	RootComponent = DummyRoot;

	// Create a spring arm component for our chase camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	//SpringArm->RelativeRotation = FRotator(-90.f, 0.f, 0.f);
	SpringArm->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 1024.0f;
	//SpringArm->bEnableCameraLag = false;
	//SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;

	// Create the camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("JumpyFrogsCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	//Camera->SetRelativeRotation(FRotator(0.0f, -200.0f, -300.0f));
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
	//Camera->bUsePawnControlRotation = true;
	Camera->FieldOfView = 90.f;

	//this->SetActorLocation(FVector(250.f, 300.f, 200.f));
}


// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// set up gameplay key bindings
	check(InputComponent);
}

