// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameModeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JUMPYFROGS_API IGameModeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	bool IsMoveValidCheck(FVector Location);

	UFUNCTION(BlueprintNativeEvent)
	void RemoveFrogAddSlot(const FVector StartFrogLoc, const  FVector EndFrogLoc);

	UFUNCTION(BlueprintNativeEvent)
	void RemoveFrogsAndAddSlots(FVector SelectedFrogLoc, TArray<FVector>& InMarkedSlots);

	UFUNCTION(BlueprintNativeEvent)
	void FrogJumpingEnded();
};
