// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Actors/Frog.h"
//#include "Particles/ParticleSystemComponent.h"
//#include "Components/CapsuleComponent.h"
//#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AFrog::AFrog()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<USkeletalMesh> FrogMeshObj;
		ConstructorHelpers::FClassFinder<UAnimInstance> FrogAnimBPObj;
		/*ConstructorHelpers::FObjectFinderOptional<USkeletalMesh> skelMeshLOD1;
		ConstructorHelpers::FObjectFinderOptional<USkeletalMesh> skelMeshLOD2;
		ConstructorHelpers::FObjectFinderOptional<USkeletalMesh> skelMeshLOD0NoBones;*/
		//ConstructorHelpers::FObjectFinderOptional<UStaticMesh> ClickMesh;

		ConstructorHelpers::FObjectFinderOptional<UMaterial> InvisMat;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> OrangeMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GreenMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> RedEyeMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> StrawberryMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BombFrogMaterial;
	
		//ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> RedBombFrogMaterial;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpRightObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdRightObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdLeftObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdRightObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdLeftObj;

		FConstructorStatics()
			: FrogMeshObj(TEXT("/Game/Frog/SkelMesh/FrogSkelMesh"))
			, FrogAnimBPObj(TEXT("/Game/Frog/Animations/FrogAnimBP"))
			/*, skelMeshLOD1(TEXT("/Game/Frog/SkelMesh/Frog_SkeletalMesh_Final_LOD1"))
			, skelMeshLOD2(TEXT("/Game/Frog/SkelMesh/Frog_SkeletalMesh_LOD2"))
			, skelMeshLOD0NoBones(TEXT("/Game/Frog/SkelMesh/Frog_SkeletalMesh_LOD0_NoBones"))*/
			//, ClickMesh(TEXT("/Game/EmptySlot/StaticMesh/EmptySlot"))

			, InvisMat(TEXT("/Game/EmptySlot/Materials/Invisible_Mat"))
			, BlueMaterial(TEXT("/Game/Frog/Materials/BlueDartFrog_mat"))
			, OrangeMaterial(TEXT("/Game/Frog/Materials/OrangeFrog_Mat"))
			, GreenMaterial(TEXT("/Game/Frog/Materials/GreenFrog_Mat"))
			, RedEyeMaterial(TEXT("/Game/Frog/Materials/RedEyeTreeFrog_Mat"))
			, StrawberryMaterial(TEXT("/Game/Frog/Materials/StrawberryFrog_Mat"))
			, BombFrogMaterial(TEXT("/Game/Frog/Materials/BombFrog_Mat"))
			//, RedBombFrogMaterial(TEXT("/Game/Frog/Materials/RedBombFrog_Mat"))
			
			
			,JumpRightObj(TEXT("/Game/Frog/Animations/JumpRight_Montage"))
			,JumpLeftObj(TEXT("/Game/Frog/Animations/JumpLeft_Montage"))
			,JumpFwdRightObj(TEXT("/Game/Frog/Animations/JumpFwdRight_Montage"))
			,JumpFwdLeftObj(TEXT("/Game/Frog/Animations/JumpFwdLeft_Montage"))
			,JumpBwdRightObj(TEXT("/Game/Frog/Animations/JumpBwdRight_Montage"))
			,JumpBwdLeftObj(TEXT("/Game/Frog/Animations/JumpBwdLeft_Montage"))


		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	
	
	FrogMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FrogMesh"));
	FrogMesh->SetSkeletalMesh(ConstructorStatics.FrogMeshObj.Object);
	if (ConstructorStatics.FrogAnimBPObj.Class != NULL)
	{
		FrogMesh->SetAnimInstanceClass(ConstructorStatics.FrogAnimBPObj.Class);
	}

	JumpAnims.Add(ConstructorStatics.JumpRightObj.Object);
	JumpAnims.Add(ConstructorStatics.JumpLeftObj.Object);
	JumpAnims.Add(ConstructorStatics.JumpFwdRightObj.Object);
	JumpAnims.Add(ConstructorStatics.JumpFwdLeftObj.Object);
	JumpAnims.Add(ConstructorStatics.JumpBwdRightObj.Object);
	JumpAnims.Add(ConstructorStatics.JumpBwdLeftObj.Object);

	MatBlue = ConstructorStatics.BlueMaterial.Get();
	MatOrange = ConstructorStatics.OrangeMaterial.Get();
	MatGreen = ConstructorStatics.GreenMaterial.Get();
	MatRedEye = ConstructorStatics.RedEyeMaterial.Get();
	MatStrawberry = ConstructorStatics.StrawberryMaterial.Get();
	MatBombFrog = ConstructorStatics.BombFrogMaterial.Get();
	//RedMatBombFrog = ConstructorStatics.RedBombFrogMaterial.Get();


	//FrogLOD0 = ConstructorStatics.skelMesh.Get();
	//FrogLOD0NoBones = ConstructorStatics.skelMeshLOD0NoBones.Get();
	//FrogLOD1 = ConstructorStatics.skelMeshLOD1.Get();
	//FrogLOD2 = ConstructorStatics.skelMeshLOD2.Get(); //no bones

	//GetMesh()->SetSkeletalMesh(ConstructorStatics.skelMeshLOD2.Get());
	//GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -80.0f));
	//GetMesh()->bCastDynamicShadow = false;

	//ClToMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrogClickTouchBox"));
	//ClToMesh->SetStaticMesh(ConstructorStatics.ClickMesh.Get());

	//ClToMesh->SetMaterial(0, ConstructorStatics.InvisMat.Get());
	////ClToMesh->SetRelativeLocation(FVector(0.f, 0.f, -10.0f));
	//ClToMesh->SetupAttachment(GetMesh());//EmptySlotMesh->AttachTo(DummyRoot);
	//ClToMesh->OnClicked.AddDynamic(this, &AJumpyFrogCharacter::FrogClicked);
	//ClToMesh->OnInputTouchBegin.AddDynamic(this, &AJumpyFrogCharacter::OnFingerPressedFrog);
	//ClToMesh->bCastDynamicShadow = false;

	//// load the animation blueprint
	//const ConstructorHelpers::FClassFinder<UAnimInstance> FrogAnimBP(TEXT("/Game/Frog/Animations/Frog_AnimationBP"));
	//if (FrogAnimBP.Class != NULL)
	//{
	//	FrogMesh->SetAnimInstanceClass(FrogAnimBP.Class);
	//}

}

// Called when the game starts or when spawned
void AFrog::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFrog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

