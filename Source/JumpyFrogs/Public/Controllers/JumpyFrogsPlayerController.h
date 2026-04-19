// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "SharedData.h"
#include "JumpyFrogsPlayerController.generated.h"

/**
 * 
 */

class UInputAction;
class UInputMappingContext;
class AJumpVisualizer;

UCLASS()
class JUMPYFROGS_API AJumpyFrogsPlayerController : public APlayerController
{
	GENERATED_BODY()

	AJumpyFrogsPlayerController();
	void SetupInputComponent() override;

public:
	

	void EnableDisableInput(const bool bDisabled);

	void MouseOrTouchEnd();

	void ResetVizualizer();
protected:

	//void BeginPlay() override;

	void UpdateTouchOrClick();
	void UpdateJumpVisualizer();


	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_MouseClick;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_MouseRelease;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_TouchStart;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_TouchEnd;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* IMC_Default_MappingContext;

	

	bool CheckIfFrogAlreadyAdded(const FVector InFrogLoc);

	void OnMouseClicked();
	void ResetClickCount();
	void OnMousePulse();
	void OnMouseReleased();

	

	void OnTouchStart(const FInputActionValue& Value);
	void OnTouchEnd(const FInputActionValue& Value);

	
	//const bool IsTeleporterAlreadyMarked(const FVector TeleporterLoc);
	bool bWasRecentlyClicked = false;
	const bool IsSlotAlreadyMarked(const FVector SlotLoc);

	TArray<FVector> JumpPathLocations;
	//TArray<UObject*> MarkedSlots;

	TArray<FVector> MarkedSlots;
	//TMap<FVector, ESlotType> MappedJumps;

	//TArray<FVector> MarkedTeleporters;
	TArray<FVector> FrogsToRemoveLocations;

	UObject* SelectedFrog;
	AJumpVisualizer* JumpVisualizer = nullptr;
	bool bTeleporterAdded = false;
};
