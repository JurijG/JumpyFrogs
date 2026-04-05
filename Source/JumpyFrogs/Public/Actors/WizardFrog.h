// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Frog.h"
#include "WizardFrog.generated.h"

/**
 * 
 */
UCLASS()
class JUMPYFROGS_API AWizardFrog : public AFrog
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWizardFrog();

protected:
	TObjectPtr<UStaticMeshComponent> WizardHatMesh;
	TObjectPtr<UStaticMeshComponent> MagicWandMesh;
};
