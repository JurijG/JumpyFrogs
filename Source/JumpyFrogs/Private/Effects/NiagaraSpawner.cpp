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
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> TeleportOut_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> WaterMagic_Obj;

		FConstructorStatics() //StaticMesh'/Game/EmptySlot/StaticMesh/EmptySlot.EmptySlot'
			: ///Script/Niagara.NiagaraSystem'/Game/Niagara/Teleporter/NS_TeleportIn.NS_TeleportIn'
			TeleportIn_Obj(TEXT("/Game/Niagara/Teleporter/NS_TeleportIn")),
			TeleportOut_Obj(TEXT("/Game/Niagara/Teleporter/NS_TeleportOut")),
			WaterMagic_Obj(TEXT("/Game/Water_Magic/VFX_Niagara/NS_Water_Magic_Area1"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	TeleportIn = ConstructorStatics.TeleportIn_Obj.Object;
	TeleportOut = ConstructorStatics.TeleportOut_Obj.Object;
	WaterMagic = ConstructorStatics.WaterMagic_Obj.Object;
}

void ANiagaraSpawner::SpawnNiagara_Implementation(ENiagaraFX NiagaraType, FVector SpawnLoc)
{

    // Example: Play Niagara at a location
    //UNiagaraSystem* TeleportEffect; // assign in editor or load asset
    //FVector SpawnLocation = FVector::ZeroVector;
    FRotator SpawnRotation = FRotator::ZeroRotator;
	UNiagaraSystem* EffectToPlay = WaterMagic;
	switch (NiagaraType)
	{
		case ENiagaraFX::TeleportOut: EffectToPlay = TeleportOut;  break;
		case ENiagaraFX::TeleportIn: EffectToPlay = TeleportIn;  break;
		case ENiagaraFX::WaterMagic: EffectToPlay = WaterMagic;  break;
		//default: ENiagaraFX:::
	}


    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),        // World context
		EffectToPlay,    // Niagara system asset
		SpawnLoc,     // Location
        SpawnRotation      // Rotation
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

