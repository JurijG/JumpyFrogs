// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Actors/LilyPad.h"
#include "Components/BoxComponent.h"

// Sets default values
ALilyPad::ALilyPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("LillyPadsRoot"));
	RootComponent = DummyRoot;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UMaterial> LilyPadGreenMatAsset;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMeshAsset;
		FConstructorStatics()
			: LilyPadGreenMatAsset(TEXT("/Game/LilyPads/Materials/WaterLily_Pad_Green")),
			  PlaneMeshAsset(TEXT("/Game/LilyPads/LilyPadMesh"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	LilyPadBaseMat = ConstructorStatics.LilyPadGreenMatAsset.Get();
	PlaneMesh = ConstructorStatics.PlaneMeshAsset.Get();

	////UDataTable* LillyPadsDataTable;
	////LillyPadsDataTable = ConstructorStatics.LillyPadsDataTable_DT.Get();
	////ScoringDataTable = ConstructorStatics.ScoringDataTable_BP.Get();
	//// Create static mesh component
	//LilyPad = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LilyPadsMesh"));
	//RootComponent = LilyPad;
	//LilyPadsMesh->SetStaticMesh(ConstructorStatics.LilyPadsMeshObj.Get());
	//LilyPadsMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	//LilyPadsMesh->SetRelativeLocation(FVector(8.0f, 8.0f, 200.0f));
	//LilyPadsMesh->SetMaterial(0, ConstructorStatics.LilyPadGreenMat.Get());

}

//void ALilyPad::SpawnLilyPads(TArray<FVector>& Locations)
//{
//	for (FVector Location : Locations)
//	{
//		AddLilyPad(Location);
//	}
//}
void ALilyPad::AddLilyPad(FVector2D Location)
{
	FVector SpawnLoc = FVector(Location.X, Location.Y, 200.f);
	UStaticMeshComponent* PadMesh = NewObject<UStaticMeshComponent>(this);
	if (PlaneMesh)
	{
		PadMesh->SetStaticMesh(PlaneMesh);
	}
	PadMesh->SetCollisionProfileName(TEXT("NoCollision"));
	PadMesh->SetGenerateOverlapEvents(false);
	PadMesh->SetupAttachment(RootComponent);
	
	PadMesh->SetRelativeLocation(SpawnLoc);
	PadMesh->SetRelativeRotation(FRotator(0.f, FMath::RandRange(0.f, 359.f), 0.f));
	UMaterialInstanceDynamic* MID = UMaterialInstanceDynamic::Create(LilyPadBaseMat, this);
	uint8 Index = FMath::RandRange(0, 15);
	//Index = 3;
	MID->SetScalarParameterValue("U", Index % 4 * 0.25f);
	MID->SetScalarParameterValue("V", Index / 4 * 0.25f);
	PadMesh->SetMaterial(0, MID);
	PadMesh->RegisterComponent();
	PadMesh->TranslucencySortPriority = 1;
	Pads.Add(PadMesh);
}

// Called when the game starts or when spawned
//void ALilyPad::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

// Called every frame
//void ALilyPad::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

