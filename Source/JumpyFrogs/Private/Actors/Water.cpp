// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Actors/Water.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AWater::AWater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> WatMesh;
		//ConstructorHelpers::FObjectFinderOptional<UMaterial> WatMat;
		//ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> WatMatInst;

		FConstructorStatics()
			: WatMesh(TEXT("/Game/Water/WaterPlane"))
			//, WatMat(TEXT("/Game/Water/PondLake_Mat"))
			//, WatMatInst(TEXT("/Game/Water/PondLake_Mat_Inst"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	//WaterDummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("WaterDummy"));
	//RootComponent = WaterDummyRoot;
	 
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->bHiddenInGame = false;
	Box->SetBoxExtent(FVector(2048.f, 2048.f, 5.f));
	Box->SetCollisionProfileName(TEXT("EmptySlotProfile"));

	RootComponent = Box;
	
	// Create static mesh component
	WaterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water plane"));
	WaterMesh->SetStaticMesh(ConstructorStatics.WatMesh.Get());
	WaterMesh->SetupAttachment(Box);
	//WaterMesh->SetMaterial(0, ConstructorStatics.WatMat.Get());
	WaterMesh->bCastDynamicShadow = false;
	WaterMesh->bAffectDynamicIndirectLighting = true;
	//WaterMesh->translucent = true;
}

// Called when the game starts or when spawned
void AWater::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

