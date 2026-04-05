// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.
#include "Actors/WizardFrog.h"

AWizardFrog::AWizardFrog()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> WizardHat_Obj;
		ConstructorHelpers::FObjectFinder<UStaticMesh> MagicWand_Obj;
		FConstructorStatics()
			: WizardHat_Obj(TEXT("/Game/Meshes/Hat.Hat"))
			, MagicWand_Obj(TEXT("/Game/Meshes/Wand.Wand"))
		{
		}
	};
	
	static FConstructorStatics ConstructorStatics;

	WizardHatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WizardHatMesh"));
	WizardHatMesh->SetStaticMesh(ConstructorStatics.WizardHat_Obj.Object);
	WizardHatMesh->SetupAttachment(GetFrogMesh(), TEXT("b_HatSocket"));
	
	MagicWandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagicWandMesh"));
	MagicWandMesh->SetStaticMesh(ConstructorStatics.MagicWand_Obj.Object);
	MagicWandMesh->SetupAttachment(GetFrogMesh(), TEXT("b_WandSocket"));



}