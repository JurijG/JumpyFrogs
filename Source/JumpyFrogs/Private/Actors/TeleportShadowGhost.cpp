// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Actors/TeleportShadowGhost.h"

// Sets default values
ATeleportShadowGhost::ATeleportShadowGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>		 FrogMesh_Obj;	
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> Mat_ShadowOpacity_Inst_Obj;

		FConstructorStatics()
			:
			FrogMesh_Obj(TEXT("/Game/Frog/FrogIdlePose")),
			Mat_ShadowOpacity_Inst_Obj(TEXT("/Game/Frog/Materials/Mat_ShadowOpacity_Inst"))
		{
		}
	};

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TeleportShadowGhost"));
	RootComponent = DummyRoot;

	static FConstructorStatics ConstructorStatics;

	FrogStartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrogStartMesh"));
	FrogStartMesh->SetStaticMesh(ConstructorStatics.FrogMesh_Obj.Get());
	FrogStartMesh->SetMaterial(0, ConstructorStatics.Mat_ShadowOpacity_Inst_Obj.Get());
	FrogStartMesh->SetupAttachment(DummyRoot);
	FrogStartMesh->SetVisibility(false); // optional if using shadow-only trick
	FrogStartMesh->SetCastShadow(true);
	FrogStartMesh->bCastHiddenShadow = true;

	FrogEndMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrogEndMesh"));
	FrogEndMesh->SetStaticMesh(ConstructorStatics.FrogMesh_Obj.Get());
	FrogEndMesh->SetMaterial(0, ConstructorStatics.Mat_ShadowOpacity_Inst_Obj.Get());
	FrogEndMesh->SetupAttachment(DummyRoot);
	FrogEndMesh->SetVisibility(false); // optional if using shadow-only trick
	FrogEndMesh->SetCastShadow(true);
	FrogEndMesh->bCastHiddenShadow = true;

	


}
//
//void ATeleportShadowGhost::UpdateScale()
//{
//	StartScale -= FVector(0.04);
//	EndScale += FVector(0.04);
//	
//	if (EndScale.X > 0.5f && EndScale.X <= 1.f )
//	{
//		//FrogStartMesh->SetRelativeScale3D(StartScale);
//		FrogEndMesh->SetRelativeScale3D(EndScale);
//		//FrogStartMesh->bCastHiddenShadow = true;
//		//FrogStartMesh->SetCastShadow(true);
//		FrogEndMesh->bCastHiddenShadow = true;
//		FrogEndMesh->SetCastShadow(true);
//	}
//	if (StartScale.X > 0.5f)
//	{
//		FrogStartMesh->SetRelativeScale3D(StartScale);
//		FrogStartMesh->bCastHiddenShadow = true;
//		FrogStartMesh->SetCastShadow(true);
//	}
//	else
//	{
//		FrogStartMesh->SetCastShadow(false);
//	}
//}
void ATeleportShadowGhost::UpdateOpacity()
{
	StartOpacity -= 0.04;
	EndOpacity += 0.04;

	StartMID->SetScalarParameterValue(TEXT("ShadowAlpha"), StartOpacity);
	EndMID->SetScalarParameterValue(TEXT("ShadowAlpha"), EndOpacity);

	//// Fade out start mesh, fade in end mesh
	//FrogStartMesh->SetScalarParameterValueOnMaterials(TEXT("ShadowAlpha"), StartOpacity);
	//FrogEndMesh->SetScalarParameterValueOnMaterials(TEXT("ShadowAlpha"), EndOpacity);
}
void ATeleportShadowGhost::SetRelativeEndLocation(FVector FrogEndMeshLoc)
{
	FrogEndMesh->SetRelativeLocation(FrogEndMeshLoc);
}

// Called when the game starts or when spawned
void ATeleportShadowGhost::BeginPlay()
{
	Super::BeginPlay();

	StartMID = FrogStartMesh->CreateDynamicMaterialInstance(0);
	EndMID = FrogEndMesh->CreateDynamicMaterialInstance(0);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATeleportShadowGhost::UpdateOpacity, 0.04f, true);
}
// Called every frame
//void ATeleportShadowGhost::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	// Increment elapsed time
//	ElapsedTime += DeltaTime;
//
//	// Alpha goes from 0 to 1 over 1 second
//	//const float Alpha = FMath::Clamp(ElapsedTime / 0.5f, 0.2f, 1.1f);
//
//	// Lerp scales
//	/*FVector StartScale = FMath::Lerp(FVector(1.f), FVector(0.2f), Alpha);
//	FVector EndScale = FMath::Lerp(FVector(0.2f), FVector(1.f), Alpha);*/
//
//	if (StartScale.X > 0.5f)
//	{
//		FrogStartMesh->bCastHiddenShadow = true;
//		FrogStartMesh->SetCastShadow(true);
//		FrogEndMesh->bCastHiddenShadow = true;
//		FrogEndMesh->SetCastShadow(true);
//		FrogStartMesh->SetRelativeScale3D(StartScale);
//		FrogEndMesh->SetRelativeScale3D(EndScale);
//	}
//	
//
//	// Optional: If using shadow-only material with fade parameter
//	/*float StartFade = FMath::Lerp(1.f, 0.f, Alpha);
//	float EndFade = 1.f - StartFade;*/
//
//	/*FrogStartMesh->SetScalarParameterValueOnMaterials("ShadowFade", StartFade);
//	FrogEndMesh->SetScalarParameterValueOnMaterials("ShadowFade", EndFade);*/
//
//	// Destroy actor when done
//	/*if (Alpha >= 1.f)
//	{
//		Destroy();
//	}*/
//}
//
