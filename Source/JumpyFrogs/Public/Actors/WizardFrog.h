// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Frog.h"
#include "WizardFrog.generated.h"

/**
 * 
 */

//class UNiagaraComponent;

UCLASS()
class JUMPYFROGS_API AWizardFrog : public AFrog
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWizardFrog();
	void CastSpell();

protected:
	TObjectPtr<UStaticMeshComponent> WizardHatMesh;
	UStaticMesh* MagicWandMesh;
	//TObjectPtr<UStaticMeshComponent> MagicWand;
	UAnimMontage* CastingSpell;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UNiagaraComponent* WaterMagic;*/

	bool IsAWizard_Implementation() const override;

	void AttachWand_Implementation() override;
};
