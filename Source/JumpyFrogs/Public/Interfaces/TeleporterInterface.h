// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TeleporterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTeleporterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JUMPYFROGS_API ITeleporterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	bool IsThisStart(UObject* InComponent) const;

	UFUNCTION(BlueprintNativeEvent)
	FVector GetStartLocation() const;

	UFUNCTION(BlueprintNativeEvent)
	FVector GetEndLocation() const;

	UFUNCTION(BlueprintNativeEvent)
	void Deactivate();
};
