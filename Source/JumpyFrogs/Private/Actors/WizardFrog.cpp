// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.
#include "Actors/WizardFrog.h"

//#include "NiagaraComponent.h"
//#include "NiagaraFunctionLibrary.h"
//#include "NiagaraSystem.h"

AWizardFrog::AWizardFrog()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> WizardHat_Obj;
		ConstructorHelpers::FObjectFinder<UStaticMesh> MagicWand_Obj;
		//ConstructorHelpers::FObjectFinder<UNiagaraSystem> WaterMagic_Obj;
		FConstructorStatics()
			: WizardHat_Obj(TEXT("/Game/Meshes/Hat.Hat"))
			, MagicWand_Obj(TEXT("/Game/Meshes/Wand.Wand"))
			//, WaterMagic_Obj(TEXT("/Game/Water_Magic/VFX_Niagara/NS_Water_Magic_Area1.NS_Water_Magic_Area1"))
		{
		}
	};
	
	static FConstructorStatics ConstructorStatics;
	///Script/Niagara.NiagaraSystem'/Game/NiagaraExamples/FX_Player/NS_Player_Teleport_In.NS_Player_Teleport_In'
	WizardHatMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WizardHatMesh"));
	WizardHatMesh->SetStaticMesh(ConstructorStatics.WizardHat_Obj.Object);
	WizardHatMesh->SetupAttachment(GetFrogMesh(), TEXT("b_HatSocket"));
	
	MagicWandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MagicWandMesh"));
	MagicWandMesh->SetStaticMesh(ConstructorStatics.MagicWand_Obj.Object);
	MagicWandMesh->SetupAttachment(GetFrogMesh(), TEXT("b_WandSocket"));

	//// Create Niagara component
	//WaterMagic = CreateDefaultSubobject<UNiagaraComponent>(TEXT("WaterMagic"));
	//WaterMagic->SetAsset(ConstructorStatics.WaterMagic_Obj.Object);
	//// Attach to root (or any component you want)
	//WaterMagic->SetupAttachment(RootComponent);
	//// Optional: auto-activate
	//WaterMagic->bAutoActivate = true;

	//NiagaraEffect->Activate();
	//NiagaraEffect->Deactivate();

}