// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Controllers/JumpyFrogsPlayerController.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
//#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


//
// Script / EnhancedInput.InputMappingContext'/Game/IA_DefaultMappingContext.IA_DefaultMappingContext'
// Script / EnhancedInput.InputAction'/Game/IA_MouseClick.IA_MouseClick'
// Script / EnhancedInput.InputAction'/Game/IA_MouseRelease.IA_MouseRelease'

///Script/EnhancedInput.InputAction'/Game/Input/IA_TouchEnd.IA_TouchEnd'
// Script / EnhancedInput.InputAction'/Game/Input/IA_TouchStart.IA_TouchStart'

AJumpyFrogsPlayerController::AJumpyFrogsPlayerController()
{
    bShowMouseCursor = true;       // Show the cursor
    //bEnableClickEvents = true;     // Enable OnClicked events
    //bEnableMouseOverEvents = true; // Enable hover events

    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinderOptional<UInputMappingContext> IMC_DefaultObj;
        ConstructorHelpers::FObjectFinderOptional<UInputAction> IA_MouseClickObj;
        ConstructorHelpers::FObjectFinderOptional<UInputAction> IA_MouseReleaseObj;
        ConstructorHelpers::FObjectFinderOptional<UInputAction> IA_TouchStartObj;
        ConstructorHelpers::FObjectFinderOptional<UInputAction> IA_TouchEndObj;
        FConstructorStatics()
            : IMC_DefaultObj(TEXT("/Game/Input/IA_DefaultMappingContext"))
            , IA_MouseClickObj(TEXT("InputAction'/Game/Input/IA_MouseClick'"))
            , IA_MouseReleaseObj(TEXT("/Game/Input/IA_MouseRelease"))
            , IA_TouchStartObj(TEXT("/Game/Input/IA_TouchStart"))
            , IA_TouchEndObj(TEXT("/Game/Input/IA_MouseRelease"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;

    if (ConstructorStatics.IA_MouseClickObj.Succeeded())
    {
        IA_MouseClick = ConstructorStatics.IA_MouseClickObj.Get();
    }
    if (ConstructorStatics.IA_MouseReleaseObj.Succeeded())
    {
        IA_MouseRelease = ConstructorStatics.IA_MouseReleaseObj.Get();
    }
    if (ConstructorStatics.IA_TouchStartObj.Succeeded())
    {
        IA_TouchStart = ConstructorStatics.IA_TouchStartObj.Get();
    }
    if (ConstructorStatics.IA_TouchEndObj.Succeeded())
    {
        IA_TouchEnd = ConstructorStatics.IA_TouchEndObj.Get();
    }
    if (ConstructorStatics.IMC_DefaultObj.Succeeded())
    {
        IMC_Default_MappingContext = ConstructorStatics.IMC_DefaultObj.Get();
    }
}

void AJumpyFrogsPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    /*InputComponent->BindAction("LeftClick", IE_Pressed, this, &AJumpyFrogsPlayerController::OnClicked);
    InputComponent->BindAction("LeftClick", IE_Released, this, &AJumpyFrogsPlayerController::OnReleased);*/

    //InputComponent->BindTouch(IE_Pressed, this, &AJumpyFrogsPlayerController::OnTouchStart);
    //InputComponent->BindTouch(IE_Released, this, &AJumpyFrogsPlayerController::OnTouchEnd);

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInput->BindAction(IA_MouseClick, ETriggerEvent::Started, this, &AJumpyFrogsPlayerController::OnMouseClicked);
        EnhancedInput->BindAction(IA_MouseRelease, ETriggerEvent::Completed, this, &AJumpyFrogsPlayerController::OnMouseReleased);
        EnhancedInput->BindAction(IA_TouchStart, ETriggerEvent::Started, this, &AJumpyFrogsPlayerController::OnTouchStart);
        EnhancedInput->BindAction(IA_TouchEnd, ETriggerEvent::Completed, this, &AJumpyFrogsPlayerController::OnTouchEnd);
        
    }
 
}

void AJumpyFrogsPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
    {
        if (!IMC_Default_MappingContext) return;
        Subsystem->AddMappingContext(IMC_Default_MappingContext, 0);
        /* if (!IMC_Hands_MappingContext) return;
            Subsystem->AddMappingContext(IMC_Hands_MappingContext, 1);*/
    }
}
void AJumpyFrogsPlayerController::OnMouseClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnMouseClicked"));
    FHitResult Hit;

    if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
    {
        if (AActor* HitActor = Hit.GetActor())
        {
            UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitActor->GetName());
        }
    }
}
 
void AJumpyFrogsPlayerController::OnMouseReleased()
{

    UE_LOG(LogTemp, Warning, TEXT("OnMouseReleased"));
}
void AJumpyFrogsPlayerController::OnTouchStart(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("OnTouchBegin"));
    // Value.Get<bool>() returns true if pressed
    if (Value.Get<bool>())
    {
        FHitResult Hit;
        GetHitResultUnderFinger(ETouchIndex::Touch1, ECC_Visibility, false, Hit);
        if (Hit.GetActor())
        {
            UE_LOG(LogTemp, Warning, TEXT("Touch Start: %s"), *Hit.GetActor()->GetName());
        }
    }
}
void AJumpyFrogsPlayerController::OnTouchEnd(const FInputActionValue& Value)
{
    UE_LOG(LogTemp, Warning, TEXT("OnTouchEnd"));
   
}