// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
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
	bool bMoveInAction = false;

protected:
	void BeginPlay() override;

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

	
	void OnMouseClicked();
	void OnMousePulse();
	void OnMouseReleased();
	void OnTouchStart(const FInputActionValue& Value);
	void OnTouchEnd(const FInputActionValue& Value);

	bool IsSlotAlreadyMarked(const FVector SlotLoc);

	TArray<FVector> JumpPathLocations;
	//TArray<UObject*> MarkedSlots;
	TArray<FVector> MarkedSlots;
	UObject* SelectedFrog;
	AJumpVisualizer* JumpVisualizer = nullptr;
};
