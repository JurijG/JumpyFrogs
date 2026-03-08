// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FrogInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFrogInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JUMPYFROGS_API IFrogInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void Jump(const TArray<FVector>& InMarkedSlots);

	UFUNCTION(BlueprintNativeEvent)
	void DestroyFrog();

	UFUNCTION(BlueprintNativeEvent)
	void JumpAway();

	UFUNCTION(BlueprintNativeEvent)
	void PlayNextAnimation();
};
