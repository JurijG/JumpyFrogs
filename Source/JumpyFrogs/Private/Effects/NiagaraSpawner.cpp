// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Effects/NiagaraSpawner.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ANiagaraSpawner::ANiagaraSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	struct FConstructorStatics
	{
		//ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> TeleportIn_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> TeleportInWizard_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> TeleportOut_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> TeleportOutWizard_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> TeleportOutWizardSpell_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> WaterMagic_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> WaterMagicBuff_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> WaterSplash_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> WaterSplashRipple_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> RippleShort_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> JustBubbles_Obj;

		FConstructorStatics() //StaticMesh'/Game/EmptySlot/StaticMesh/EmptySlot.EmptySlot'
			: ///Script/Niagara.NiagaraSystem'/Game/Niagara/Teleporter/NS_TeleportIn.NS_TeleportIn'
			TeleportIn_Obj(TEXT("/Game/Niagara/Teleporter/NS_TeleportIn")),
			TeleportInWizard_Obj(TEXT("/Game/Niagara/Teleporter/NS_TeleportInWizard")),
			TeleportOut_Obj(TEXT("/Game/Niagara/Teleporter/NS_TeleportOut")),
			TeleportOutWizard_Obj(TEXT("/Game/Niagara/Teleporter/NS_TeleportOutWizard")),
			TeleportOutWizardSpell_Obj(TEXT("/Game/Niagara/Teleporter/NS_TeleportOutWizardSpell")),
			WaterMagic_Obj(TEXT("/Game/Water_Magic/VFX_Niagara/NS_Water_Magic_Area1")),
			WaterMagicBuff_Obj(TEXT("/Game/Water_Magic/VFX_Niagara/NS_Water_Magic_Buff")),
			WaterSplash_Obj(TEXT("/Game/Niagara/NS_Splash")),
			WaterSplashRipple_Obj(TEXT("/Game/Niagara/NS_SplashRipple")),
			RippleShort_Obj(TEXT("/Game/Niagara/NS_RippleShort")),
			JustBubbles_Obj(TEXT("/Game/Niagara/NS_JustBubbles"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	TeleportIn = ConstructorStatics.TeleportIn_Obj.Object;
	TeleportInWizard = ConstructorStatics.TeleportInWizard_Obj.Object;
	TeleportOut = ConstructorStatics.TeleportOut_Obj.Object;
	TeleportOutWizard = ConstructorStatics.TeleportOutWizard_Obj.Object;
	TeleportOutWizardSpell = ConstructorStatics.TeleportOutWizardSpell_Obj.Object;
	WaterMagic = ConstructorStatics.WaterMagic_Obj.Object;
	WaterMagicBuff = ConstructorStatics.WaterMagicBuff_Obj.Object;
	WaterSplash = ConstructorStatics.WaterSplash_Obj.Object;
	WaterSplashRipple = ConstructorStatics.WaterSplashRipple_Obj.Object;
	RippleShort = ConstructorStatics.RippleShort_Obj.Object;
	JustBubbles = ConstructorStatics.JustBubbles_Obj.Object;
}

void ANiagaraSpawner::SpawnNiagara_Implementation(ENiagaraFX NiagaraType, FVector SpawnLoc)
{

    // Example: Play Niagara at a location
    //UNiagaraSystem* TeleportEffect; // assign in editor or load asset
    //FVector SpawnLocation = FVector::ZeroVector;
    FRotator SpawnRotation = FRotator::ZeroRotator;
	FVector Scale = FVector::OneVector;
	UNiagaraSystem* EffectToPlay = WaterMagic;
	switch (NiagaraType)
	{
		case ENiagaraFX::TeleportOut: EffectToPlay = TeleportOut;  break;
		case ENiagaraFX::TeleportOutWizard: EffectToPlay = TeleportOutWizard;  break;
		case ENiagaraFX::TeleportOutWizardSpell: EffectToPlay = TeleportOutWizardSpell;  break;
		case ENiagaraFX::TeleportIn: EffectToPlay = TeleportIn;  break;
		case ENiagaraFX::TeleportInWizard: EffectToPlay = TeleportInWizard;  break;
		case ENiagaraFX::WaterMagic: EffectToPlay = WaterMagic; Scale *= 1.7f; break;
		case ENiagaraFX::WaterMagicBuff: EffectToPlay = WaterMagicBuff; Scale *= 4.f; break;
		case ENiagaraFX::WaterSplash: EffectToPlay = WaterSplash;  break;
		case ENiagaraFX::WaterSplashRipple: EffectToPlay = WaterSplashRipple;  break;
		case ENiagaraFX::RippleShort: EffectToPlay = RippleShort;  break;
		case ENiagaraFX::JustBubbles: EffectToPlay = JustBubbles;  break;
		//default: ENiagaraFX:::
	}


    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),        // World context
		EffectToPlay,    // Niagara system asset
		SpawnLoc,     // Location
        SpawnRotation,     // Rotation
		Scale //Scale
    );
}

//// Called when the game starts or when spawned
//void ANiagaraSpawner::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void ANiagaraSpawner::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

