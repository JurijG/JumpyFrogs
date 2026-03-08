// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Controllers/JumpyFrogsPlayerController.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
//#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Actors/JumpVisualizer.h"
#include "Interfaces/FrogInterface.h"
#include "Interfaces/EmptySlotInterface.h"
#include "Interfaces/GameModeInterface.h"
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
        EnhancedInput->BindAction(IA_MouseClick, ETriggerEvent::Triggered, this, &AJumpyFrogsPlayerController::OnMousePulse);
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

void AJumpyFrogsPlayerController::UpdateJumpVisualizer()
{
    UE_LOG(LogTemp, Warning, TEXT("UpdateJumpVisualizer"));

    if (!bMoveInAction)
    {
        FHitResult Hit;
        if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
        {
            if (AActor* HitActor = Hit.GetActor())
            {
                UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitActor->GetName());
                UWorld* World = GetWorld();
                if (World)
                {
                    if (JumpVisualizer == nullptr)
                    {
                        if (HitActor->Implements<UFrogInterface>())
                        {
                            SelectedFrog = HitActor;
                            JumpVisualizer = GetWorld()->SpawnActor<AJumpVisualizer>(HitActor->GetActorLocation(), FRotator(0.0f, 0.f, 0.0f));
                            FVector StartLocation = JumpVisualizer->GetActorLocation();

                            JumpPathLocations.Empty();
                            JumpPathLocations.Add(StartLocation);
                            JumpPathLocations.Add(StartLocation);
                            JumpPathLocations.Add(StartLocation);
                        }
                    }
                    else
                    {
                        FVector StartOfCurve = JumpPathLocations[0];
                        FVector Midpoint = (StartOfCurve + Hit.Location) / 2.0f;
                        Midpoint.Z += FVector::Distance(StartOfCurve, Hit.Location) / 5.f;

                        JumpPathLocations[1] = Midpoint;
                        JumpPathLocations[2] = Hit.Location;

                        /*JumpPathLocations[JumpPathLocations.Num() - 1] = Hit.Location;*/
                        JumpVisualizer->SetTraceNiagaraVectorArray(JumpPathLocations);
                        if (HitActor->Implements<UEmptySlotInterface>())
                        {
                            FVector SlotLocation = HitActor->GetActorLocation();
                            if (!IsSlotAlreadyMarked(SlotLocation))
                            {
                                if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
                                {
                                    if (GM->Implements<UGameModeInterface>())
                                    {
                                        //if we already have pre planned jump, get last marked slot location, so we take the previous Jump end location for next move, where frog will be located after jump is executed
                                        FVector StartLocation = MarkedSlots.Num() > 0 ? MarkedSlots[MarkedSlots.Num() - 1] : JumpVisualizer->GetActorLocation();
                                        //check if move is valid, if frog is in the inbetween position
                                        //UE_LOG(LogTemp, Warning, TEXT("Distance : %s"), *FString::SanitizeFloat(FVector::Distance(StartLocation, SlotLocation))); 
                                        //UE_LOG(LogTemp, Warning, TEXT("Distance from frog to emptyslot: %s"), *FString::SanitizeFloat(FVector::Distance(StartLocation, SlotLocation)));
                                        if (FVector::Distance(StartLocation, SlotLocation) < 503.f && IGameModeInterface::Execute_IsMoveValidCheck(GM, (StartLocation + SlotLocation) / 2))
                                        {
                                            MarkedSlots.Add(SlotLocation);
                                            JumpPathLocations[2] = SlotLocation;
                                            JumpVisualizer->AddDestinationRing(SlotLocation, JumpPathLocations);
                                            JumpPathLocations[0] = SlotLocation;
                                            JumpPathLocations[1] = SlotLocation;
                                            //JumpPathLocations[2] = SlotLocation;
                                            /*JumpPathLocations[JumpPathLocations.Num() - 1] = SlotLocation;
                                            JumpPathLocations.Add(SlotLocation);
                                            JumpPathLocations.Add(SlotLocation);*/

                                            //JumpVisualizer->SetTraceNiagaraVectorArray(JumpPathLocations);
                                        }
                                    }
                                }
                            }
                        }
                        //else
                        //{
                        //    FVector StartOfCurve = JumpPathLocations[0];
                        //    FVector Midpoint = (StartOfCurve + Hit.Location) / 2.0f;
                        //    Midpoint.Z += FVector::Distance(StartOfCurve, Hit.Location) / 5.f;

                        //    JumpPathLocations[1] = Midpoint;
                        //    FVector MouseLoc = Hit.Location;
                        //    MouseLoc.Z -= 50.f;
                        //    JumpPathLocations[2] = MouseLoc;

                        //    /*JumpPathLocations[JumpPathLocations.Num() - 1] = Hit.Location;*/
                        //    JumpVisualizer->SetTraceNiagaraVectorArray(JumpPathLocations);
                        //}
                    }
                }
            }
            else if (JumpVisualizer != nullptr)
            {
                FVector Midpoint = (JumpPathLocations[0] + Hit.Location) / 2.0f;
                Midpoint.Z += FVector::Distance(JumpPathLocations[0], Hit.Location) / 5.f;

                JumpPathLocations[1] = Midpoint;
                JumpPathLocations[2] = Hit.Location;

                /*JumpPathLocations[JumpPathLocations.Num() - 1] = Hit.Location;*/
                JumpVisualizer->SetTraceNiagaraVectorArray(JumpPathLocations);
            }
        }
    }
    /*else if (JumpVisualizer != nullptr)
    {*/
        //float MouseX, MouseY;
        //if (GetMousePosition(MouseX, MouseY))
        //{
        //    UE_LOG(LogTemp, Warning, TEXT("Cursor Screen Position: X=%f Y=%f"), MouseX, MouseY);

        //    FVector ProjectedLoc = FVector(MouseX, MouseY, 200.f);
        //    FVector Midpoint = (JumpPathLocations[0] + ProjectedLoc) / 2.0f;
        //    Midpoint.Z += FVector::Distance(JumpPathLocations[0], ProjectedLoc) / 2.f;
        //    //Midpoint.Z = JumpPathLocations[1].Z;

        //    JumpPathLocations[1] = Midpoint;
        //    JumpPathLocations[2] = ProjectedLoc;
        //    /*JumpPathLocations[JumpPathLocations.Num() - 1] = Hit.Location;*/
        //    JumpVisualizer->SetTraceNiagaraVectorArray(JumpPathLocations);
        //}

        //FVector WorldLocation, WorldDirection;
        //if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
        //{
        //    // WorldLocation = camera position
        //    // WorldDirection = ray from camera through cursor

        //    // Example: project onto a plane Z = 0
        //    float t = -WorldLocation.Z / WorldDirection.Z; // intersection with Z=0 plane
        //    FVector CursorWorld = WorldLocation + t * WorldDirection;
        //    WorldLocation.Z = 200.f;
        //    FVector Midpoint = (JumpPathLocations[0] + WorldLocation) / 2.0f;
        //    Midpoint.Z += FVector::Distance(JumpPathLocations[0], WorldLocation) / 2.f;
        //    //Midpoint.Z = JumpPathLocations[1].Z;

        //    JumpPathLocations[1] = Midpoint;
        //    JumpPathLocations[2] = WorldLocation;
        //    /*JumpPathLocations[JumpPathLocations.Num() - 1] = Hit.Location;*/
        //    JumpVisualizer->SetTraceNiagaraVectorArray(JumpPathLocations);
        //}
    //}
  
}

void AJumpyFrogsPlayerController::OnMouseClicked()
{
    UE_LOG(LogTemp, Warning, TEXT("OnMouseClicked"));
    
  
}

void AJumpyFrogsPlayerController::OnMousePulse()
{
    UE_LOG(LogTemp, Warning, TEXT("OnMousePulse"));
    UpdateJumpVisualizer();
}
 
void AJumpyFrogsPlayerController::OnMouseReleased()
{
    UE_LOG(LogTemp, Warning, TEXT("OnMouseReleased"));
    //set all remaining slots bHasVisualizerRing to false;
   /* for (UObject* Slot : MarkedSlots)
    {
        if (!IsValid(Slot)) continue;
        IEmptySlotInterface::Execute_SetHasVisualizerRing(Slot, false);
    }*/
    //execute frog jump(s)
    if (SelectedFrog && MarkedSlots.Num() > 0)
    {
        bMoveInAction = true;
        IFrogInterface::Execute_Jump(SelectedFrog, MarkedSlots);
       
        ////Spawn EmptySlots in places where frogs dissapear
        //if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
        //{
        //    if (GM->Implements<UGameModeInterface>())
        //    {
        //        IGameModeInterface::Execute_RemoveFrogsAndAddSlots(GM, JumpVisualizer->GetActorLocation(), MarkedSlots);
        //    }
        //}
    }
    SelectedFrog = nullptr;
    MarkedSlots.Empty();

    if (JumpVisualizer != nullptr)
    {
        JumpVisualizer->Destroy();
        JumpVisualizer = nullptr;
    }


  
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

bool AJumpyFrogsPlayerController::IsSlotAlreadyMarked(const FVector SlotLoc)
{
    for (FVector MarkedSlotLoc : MarkedSlots)
    {
        if (MarkedSlotLoc == SlotLoc)
        {
            return true;
        }
    }
    return false;
}
//
//bool AJumpyFrogsPlayerController::SpawnJumpVisualizer_Implementation()
//{
//    //World->SpawnActor<AActor>(ActorClass, Placeholder->GetActorLocation(), SpawnRotation);
//    //SpawnActor<ABomber>(FVector(1250.0f, 1000.f, 600.f), FRotator(0.0f, 0.f, 0.0f));
//    UWorld* World = GetWorld();
//    if (World)
//    {
//        VRTeleportVisualizer = GetWorld()->SpawnActor<AVRTeleportVisualizer>(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.f, 0.0f));
//        if (VRTeleportVisualizer)
//        {
//            return true;
//        }
//    }
//    return false;
//}