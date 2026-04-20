// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Actors/Frog.h"
//#include "Particles/ParticleSystemComponent.h"
//#include "Components/CapsuleComponent.h"
//#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Interfaces/GameModeInterface.h"
//#include "SharedData.h"
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

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpRightShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpRightShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpRightShortObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftShortObj;

	/*	ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdRightShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdRightShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdRightShortObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdLeftShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdLeftShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdLeftShortObj;*/

		ConstructorHelpers::FObjectFinder<UAnimMontage> ErrorObj;
		

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdRightShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdRightShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdRightShortObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdLeftShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdLeftShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdLeftShortObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownRightToDownLeftObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownRightShortInToDownLeftObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownRightShortInToRightObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownLeftToDownRightObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownLeftShortInToDownRightObj;

		

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownLeftShortInToLeftObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownRightToRightObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownLeftToLeftObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownRightToLeftObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownRightShortInToLeftObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownLeftToRightObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownLeftShortInToRightObj;
		

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpRightToDownRightObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpRightShortInToDownRightObj;	

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftToDownLeftObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftShortInToDownLeftObj;

		
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpRightToDownLeftObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpRightShortInToDownLeftObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftToDownRightObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftShortInToDownRightObj;

		//ConstructorHelpers::FObjectFinder<UAnimMontage> LeaveBwdLeftObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> SwimAwayObj;
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
			
			
			, JumpRightObj(TEXT("/Game/Frog/Animations/Montages/JumpRight_Montage"))
			, JumpLeftObj(TEXT("/Game/Frog/Animations/Montages/JumpLeft_Montage"))
			, JumpFwdRightObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdRight_Montage"))
			, JumpFwdLeftObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdLeft_Montage"))
			, JumpBwdRightObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdRight_Montage"))
			, JumpBwdLeftObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdLeft_Montage"))

			, JumpRightShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpRightShortIn_Montage"))
			, JumpRightShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpRightShortOut_Montage"))
			, JumpRightShortObj(TEXT("/Game/Frog/Animations/Montages/JumpRightShort_Montage"))
			
			, JumpLeftShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpLeftShortIn_Montage"))
			, JumpLeftShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpLeftShortOut_Montage"))
			, JumpLeftShortObj(TEXT("/Game/Frog/Animations/Montages/JumpLeftShort_Montage"))

			/*, JumpFwdRightShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdRightShortIn_Montage"))
			, JumpFwdRightShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdRightShortOut_Montage"))
			, JumpFwdRightShortObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdRightShort_Montage"))

			, JumpFwdLeftShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdLeftShortIn_Montage"))
			, JumpFwdLeftShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdLeftShortOut_Montage"))
			, JumpFwdLeftShortObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdLeftShort_Montage"))*/
			, ErrorObj(TEXT("/Game/Frog/Animations/Montages/New/Error_Montage"))
			//, Error2Obj(TEXT("/Game/Frog/Animations/Montages/New/Error2_Montage"))

			, JumpBwdRightShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdRightShortIn_Montage"))
			, JumpBwdRightShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdRightShortOut_Montage"))
			, JumpBwdRightShortObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdRightShort_Montage"))

			, JumpBwdLeftShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdLeftShortIn_Montage"))
			, JumpBwdLeftShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdLeftShortOut_Montage"))
			, JumpBwdLeftShortObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdLeftShort_Montage"))

			, JumpDownRightToDownLeftObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownRightToDownLeft_Montage"))
			, JumpDownRightShortInToDownLeftObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownRightShortInToDownLeft_Montage"))

			, JumpDownRightShortInToRightObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownRightShortInToRight_Montage"))

			, JumpDownLeftToDownRightObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownLeftToDownRight_Montage"))
			, JumpDownLeftShortInToDownRightObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownLeftShortInToDownRight_Montage"))

			, JumpDownLeftShortInToLeftObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownLeftShortInToLeft_Montage"))
			//...addd JumpDownLeftShortToLeftObj
			/// Script / Engine.AnimMontage'/Game/Frog/Animations/Montages/New/JumpDownRightToRight_Montage.JumpDownRightToRight_Montage'

			, JumpDownRightToRightObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownRightToRight_Montage"))
			, JumpDownLeftToLeftObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownLeftToLeft_Montage"))

			, JumpDownRightToLeftObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownRightToLeft_Montage"))
			, JumpDownRightShortInToLeftObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownRightShortInToLeft_Montage"))

			, JumpDownLeftToRightObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownLeftToRight_Montage"))
			, JumpDownLeftShortInToRightObj(TEXT("/Game/Frog/Animations/Montages/New/JumpDownLeftShortInToRight_Montage"))

			, JumpRightToDownRightObj(TEXT("/Game/Frog/Animations/Montages/New/JumpRightToDownRight_Montage"))
			, JumpRightShortInToDownRightObj(TEXT("/Game/Frog/Animations/Montages/New/JumpRightShortInToDownRight_Montage"))

			, JumpLeftToDownLeftObj(TEXT("/Game/Frog/Animations/Montages/New/JumpLeftToDownLeft_Montage"))
			, JumpLeftShortInToDownLeftObj(TEXT("/Game/Frog/Animations/Montages/New/JumpLeftShortInToDownLeft_Montage"))

			, JumpRightToDownLeftObj(TEXT("/Game/Frog/Animations/Montages/New/JumpRightToDownLeft_Montage"))
			, JumpRightShortInToDownLeftObj(TEXT("/Game/Frog/Animations/Montages/New/JumpRightShortInToDownLeft_Montage"))

			, JumpLeftToDownRightObj(TEXT("/Game/Frog/Animations/Montages/New/JumpLeftToDownRight_Montage"))
			, JumpLeftShortInToDownRightObj(TEXT("/Game/Frog/Animations/Montages/New/JumpLeftShortInToDownRight_Montage"))

			//, LeaveBwdLeftObj(TEXT("/Game/Frog/Animations/Montages/Remove/LeaveBwdLeft_Montage"))
			, SwimAwayObj(TEXT("/Game/Frog/Animations/Montages/New/SwimAway_Montage"))
		
			
			/*/Script/Engine.AnimMontage'/Game/Frog/Animations/Montages/JumpLeftShor_Montage.JumpLeftShor_Montage'
/Script/Engine.AnimMontage'/Game/Frog/Animations/Montages/JumpLeftShorOut_Montage.JumpLeftShorOut_Montage'
/Script/Engine.AnimMontage'/Game/Frog/Animations/Montages/JumpLeftShortIn_Montage.JumpLeftShortIn_Montage'*/

		{
		}
	};

	BoxMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxMesh->bHiddenInGame = true;
	BoxMesh->SetBoxExtent(FVector(80.f, 70.f, 10.f));
	BoxMesh->SetCollisionProfileName(TEXT("EmptySlotProfile"));
	BoxMesh->ShapeColor = FColor::Blue;
	//BoxMesh->SetLineThickness(2.0f);
	RootComponent = BoxMesh;

	static FConstructorStatics ConstructorStatics;


	
	FrogMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FrogMesh"));
	FrogMesh->SetSkeletalMesh(ConstructorStatics.FrogMeshObj.Object);

	FrogMesh->SetupAttachment(RootComponent);
	FrogMesh->bCastHiddenShadow = true;

	//FrogMesh->SetRelativeLocation(FVector(0.f, 0.f, -80.0f));
	FrogMesh->bCastDynamicShadow = true;


	if (ConstructorStatics.FrogAnimBPObj.Class != NULL)
	{
		FrogMesh->SetAnimInstanceClass(ConstructorStatics.FrogAnimBPObj.Class);
	}

	Error = ConstructorStatics.ErrorObj.Object;
	
	JumpRight = ConstructorStatics.JumpRightObj.Object;
	JumpLeft = ConstructorStatics.JumpLeftObj.Object;
	JumpUpRight = ConstructorStatics.JumpFwdRightObj.Object;
	JumpUpLeft = ConstructorStatics.JumpFwdLeftObj.Object;
	JumpDownRight = ConstructorStatics.JumpBwdRightObj.Object;
	JumpDownLeft = ConstructorStatics.JumpBwdLeftObj.Object;

	JumpRightShortIn = ConstructorStatics.JumpRightShortInObj.Object;
	JumpRightShortOut = ConstructorStatics.JumpRightShortOutObj.Object;
	JumpRightShort = ConstructorStatics.JumpRightShortObj.Object;

	JumpLeftShortIn = ConstructorStatics.JumpLeftShortInObj.Object;
	JumpLeftShortOut = ConstructorStatics.JumpLeftShortOutObj.Object;
	JumpLeftShort = ConstructorStatics.JumpLeftShortObj.Object;

	/*JumpUpRightShortIn = ConstructorStatics.JumpFwdRightShortInObj.Object;
	JumpUpRightShortOut = ConstructorStatics.JumpFwdRightShortOutObj.Object;
	JumpUpRightShort = ConstructorStatics.JumpFwdRightShortObj.Object;

	JumpUpLeftShortIn = ConstructorStatics.JumpFwdLeftShortInObj.Object;
	JumpUpLeftShortOut = ConstructorStatics.JumpFwdLeftShortOutObj.Object;
	JumpUpLeftShort = ConstructorStatics.JumpFwdLeftShortObj.Object;*/

	JumpDownRightShortIn = ConstructorStatics.JumpBwdRightShortInObj.Object;
	JumpDownRightShortOut = ConstructorStatics.JumpBwdRightShortOutObj.Object;
	JumpDownRightShort = ConstructorStatics.JumpBwdRightShortObj.Object;

	JumpDownLeftShortIn = ConstructorStatics.JumpBwdLeftShortInObj.Object;
	JumpDownLeftShortOut = ConstructorStatics.JumpBwdLeftShortOutObj.Object;
	JumpDownLeftShort = ConstructorStatics.JumpBwdLeftShortObj.Object;

	/*	JumpDownRightToDownLeft = ConstructorStatics.JumpDownRightToLeftObj.Object;
	JumpDownLeftToDownRight = ConstructorStatics.JumpDownLeftToRightObj.Object;*/
	JumpDownRightToDownLeft = ConstructorStatics.JumpDownRightToDownLeftObj.Object;
	JumpDownRightShortInToRight = ConstructorStatics.JumpDownRightShortInToRightObj.Object;
	JumpDownLeftToDownRight = ConstructorStatics.JumpDownLeftToDownRightObj.Object;
	JumpDownLeftShortInToLeft = ConstructorStatics.JumpDownLeftShortInToLeftObj.Object;

	JumpDownRightToRight = ConstructorStatics.JumpDownRightToRightObj.Object; //done
	JumpDownRightToLeft = ConstructorStatics.JumpDownRightToLeftObj.Object;
	JumpDownRightShortInToLeft = ConstructorStatics.JumpDownRightShortInToLeftObj.Object;
	
	JumpDownLeftToRight = ConstructorStatics.JumpDownLeftToRightObj.Object;
	JumpDownLeftShortInToRight = ConstructorStatics.JumpDownLeftShortInToRightObj.Object;
	JumpDownLeftToLeft = ConstructorStatics.JumpDownLeftToLeftObj.Object;

	JumpRightToDownRight = ConstructorStatics.JumpRightToDownRightObj.Object;
	JumpRightShortInToDownRight = ConstructorStatics.JumpRightShortInToDownRightObj.Object;

	JumpLeftToDownLeft = ConstructorStatics.JumpLeftToDownLeftObj.Object;
	JumpLeftShortInToDownLeft = ConstructorStatics.JumpLeftShortInToDownLeftObj.Object;

	JumpDownLeftShortInToDownRight = ConstructorStatics.JumpDownLeftShortInToDownRightObj.Object;
	JumpDownRightShortInToDownLeft = ConstructorStatics.JumpDownRightShortInToDownLeftObj.Object;

	JumpRightToDownLeft = ConstructorStatics.JumpRightToDownLeftObj.Object;
	JumpRightShortInToDownLeft = ConstructorStatics.JumpRightShortInToDownLeftObj.Object;

	JumpLeftToDownRight = ConstructorStatics.JumpLeftToDownRightObj.Object;
	JumpLeftShortInToDownRight = ConstructorStatics.JumpLeftShortInToDownRightObj.Object;


	//LeaveBwdLeft = ConstructorStatics.LeaveBwdLeftObj.Object;

	SwimAway = ConstructorStatics.SwimAwayObj.Object;


	MatBlue = ConstructorStatics.BlueMaterial.Get();
	MatOrange = ConstructorStatics.OrangeMaterial.Get();
	MatGreen = ConstructorStatics.GreenMaterial.Get();
	MatRedEye = ConstructorStatics.RedEyeMaterial.Get();
	MatStrawberry = ConstructorStatics.StrawberryMaterial.Get();
	MatBombFrog = ConstructorStatics.BombFrogMaterial.Get();
	//RedMatBombFrog = ConstructorStatics.RedBombFrogMaterial.Get();

	//JumpMontageMap =
	//{
	//	// Base directions
	//	{ EFrogJump::Right,        JumpRightMontage },
	//	{ EFrogJump::Left,         JumpLeftMontage },
	//	{ EFrogJump::UpRight,      JumpUpRightMontage },
	//	{ EFrogJump::UpLeft,       JumpUpLeftMontage },
	//	{ EFrogJump::DownRight,    JumpDownRightMontage },
	//	{ EFrogJump::DownLeft,     JumpDownLeftMontage },

	//	// Right short variants
	//	{ EFrogJump::RightShortIn,    JumpRightShortIn },
	//	{ EFrogJump::RightShortOut,   JumpRightShortOut },
	//	{ EFrogJump::RightShort, JumpRightShort },

	//	// Left short variants
	//	{ EFrogJump::LeftShortIn,    JumpLeftShortIn },
	//	{ EFrogJump::LeftShortOut,   JumpLeftShortOut },
	//	{ EFrogJump::LeftShort, JumpLeftShort },

	//	// UpRight short variants
	//	//{ EFrogJump::UpRightShortIn,    JumpUpRightShortIn },
	//	//{ EFrogJump::UpRightShortOut,   JumpUpRightShortOut },
	//	//{ EFrogJump::UpRightShort, JumpUpRightShort },

	//	//// UpLeft short variants
	//	//{ EFrogJump::UpLeftShortIn,    JumpUpLeftShortIn },
	//	//{ EFrogJump::UpLeftShortOut,   JumpUpLeftShortOut },
	//	//{ EFrogJump::UpLeftShort, JumpUpLeftShort },

	//	// DownRight short variants
	//	{ EFrogJump::DownRightShortIn,    JumpDownRightShortIn },
	//	{ EFrogJump::DownRightShortOut,   JumpDownRightShortOut },
	//	{ EFrogJump::DownRightShort, JumpDownRightShort },

	//	// DownLeft short variants
	//	{ EFrogJump::DownLeftShortIn,    JumpDownLeftShortIn },
	//	{ EFrogJump::DownLeftShortOut,   JumpDownLeftShortOut },
	//	{ EFrogJump::DownLeftShort, JumpDownLeftShort },

	//	{ EFrogJump::DownRightToRight,     JumpDownRightToRight },
	//	{ EFrogJump::DownRightToLeft,      JumpDownRightToLeft },
	//	{ EFrogJump::DownLeftToRight,      JumpDownLeftToRight },
	//	{ EFrogJump::DownLeftToLeft,       JumpDownLeftToLeft },

	//	{ EFrogJump::DownRightToDownLeft,  JumpDownRightToDownLeft },
	//	{ EFrogJump::DownLeftToDownRight,  JumpDownLeftToDownRight },
	//};

	//JumpTransitions =
	//{
	//	{ {EFrogJump::Left, EFrogJump::Left}, EFrogJump::LeftShortIn },
	//	{ {EFrogJump::Left, EFrogJump::Left}, EFrogJump::LeftShort },
	//	{ {EFrogJump::Left, EFrogJump::DownLeft}, EFrogJump::LeftToDownLeft },
	//	{ {EFrogJump::Right, EFrogJump::Right}, EFrogJump::RightShort },
	//	{ {EFrogJump::Right, EFrogJump::DownRight}, EFrogJump::RightToDownRight },
	//	{ {EFrogJump::DownLeft, EFrogJump::DownLeft}, EFrogJump::DownLeftShort },
	//	{ {EFrogJump::DownLeft, EFrogJump::Left}, EFrogJump::DownLeftToLeft },
	//	{ {EFrogJump::DownLeft, EFrogJump::Right}, EFrogJump::DownLeftToRight },
	//	{ {EFrogJump::DownLeft, EFrogJump::DownRight}, EFrogJump::DownLeftToDownRight },
	//	{ {EFrogJump::DownRight, EFrogJump::DownRight}, EFrogJump::DownRightShort },
	//	{ {EFrogJump::DownRight, EFrogJump::Left}, EFrogJump::DownRightToLeft },
	//	{ {EFrogJump::DownRight, EFrogJump::Right}, EFrogJump::DownRightToRight },
	//	{ {EFrogJump::DownRight, EFrogJump::DownLeft}, EFrogJump::DownRightToDownLeft },
	//};

	/*Jump UpLeft variations*/
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::UpLeft, EJumpDirection::None, EJumpMontage::UpLeft, JumpUpLeft) });

	/*Jump UpRight variations*/
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::UpRight, EJumpDirection::None,  EJumpMontage::UpRight, JumpUpRight) });
	
	
	///*Jump Left variations*/
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::Left, EJumpDirection::None, EJumpMontage::LeftShortIn, JumpLeftShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::Left, EJumpDirection::Left, EJumpMontage::LeftShort, JumpLeftShort) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::Left, EJumpDirection::UpLeft, EJumpMontage::LeftShort, JumpLeftShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::Left, EJumpDirection::UpRight, EJumpMontage::LeftShort, JumpLeftShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::Left, EJumpMontage::LeftShortOut, JumpLeftShortOut) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftToDownLeft, JumpLeftToDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftToDownLeft, JumpLeftToDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftToDownLeft, JumpLeftToDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftShortInToDownLeft, JumpLeftShortInToDownLeft) });



	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Left, EJumpDirection::None, EJumpMontage::LeftShortIn, JumpLeftShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Left, EJumpDirection::Left, EJumpMontage::LeftShort, JumpLeftShort) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftShortToDownLeft, JumpLeftShortToDownLeft) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::DownRight, EJumpMontage::LeftToDownRight, JumpLeftToDownRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::Left, EJumpDirection::DownRight, EJumpMontage::LeftShortToDownRight, JumpLeftShortToDownRight) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Left, EJumpDirection::None, EJumpMontage::Left, JumpLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Left, EJumpDirection::None, EJumpMontage::Left, JumpLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Left, EJumpDirection::Left, EJumpMontage::LeftShortOut, JumpLeftShortOut) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Left, EJumpDirection::Left, EJumpMontage::LeftShortOut, JumpLeftShortOut) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftToDownLeft, JumpLeftToDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftToDownLeft, JumpLeftToDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Left, EJumpDirection::DownRight, EJumpMontage::Left, JumpLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Left, EJumpDirection::DownRight, EJumpMontage::Left, JumpLeft) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Left, EJumpDirection::None, EJumpMontage::Left, JumpLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Left, EJumpDirection::UpLeft, EJumpMontage::Left, JumpLeft) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Left, EJumpDirection::DownRight, EJumpMontage::LeftShortIn, JumpLeftShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::Right, EJumpMontage::Left, JumpLeft) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::UpLeft, EJumpMontage::Left, JumpLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::UpRight, EJumpMontage::Left, JumpLeft) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Left, EJumpDirection::UpLeft, EJumpMontage::Left, JumpLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Left, EJumpDirection::UpRight, EJumpMontage::Left, JumpLeft) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Left, EJumpDirection::UpRight, EJumpMontage::Left, JumpLeft) });
	//
	///*Jump Right variations*/
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::None, EJumpMontage::RightShortIn, JumpRightShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::Right, EJumpMontage::Right, JumpRightShort) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::Right, EJumpMontage::RightShortOut, JumpRightShortOut) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::DownRight, EJumpMontage::RightToDownRight, JumpRightToDownRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::DownRight, EJumpMontage::RightShortInToDownRight, JumpRightShortInToDownRight) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Right, EJumpDirection::None, EJumpMontage::RightShortIn,JumpRightShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Right, EJumpDirection::Right, EJumpMontage::RightShort, JumpRightShort) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Right, EJumpDirection::DownRight, EJumpMontage::RightShortToDownRight, JumpRightShortToDownRight) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::DownLeft, EJumpMontage::RightToDownLeft, JumpRightToDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Right, EJumpDirection::DownLeft, EJumpMontage::RightToDownLeft, JumpRightToDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::DownLeft, EJumpMontage::RightShortToDownLeft, JumpRightShortToDownLeft) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Right, EJumpDirection::None, EJumpMontage::Right, JumpRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Right, EJumpDirection::None, EJumpMontage::Right, JumpRight) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Right, EJumpDirection::Right, EJumpMontage::Right, JumpRightShortOut) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Right, EJumpDirection::Right, EJumpMontage::Right, JumpRightShortOut) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Right, EJumpDirection::DownLeft, EJumpMontage::Right, JumpRightToDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Right, EJumpDirection::DownLeft, EJumpMontage::Right, JumpRightToDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::Right, EJumpDirection::DownRight, EJumpMontage::Right, JumpRightToDownRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Right, EJumpDirection::DownRight, EJumpMontage::Right, JumpRightToDownRight) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Right, EJumpDirection::None, EJumpMontage::Right, JumpRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Right, EJumpDirection::UpRight, EJumpMontage::Right, JumpRight) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Right, EJumpDirection::DownLeft, EJumpMontage::RightShortIn, JumpRightShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::Left, EJumpMontage::Right, JumpRight) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::UpRight, EJumpMontage::Right, JumpRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::UpLeft, EJumpMontage::Right, JumpRight) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::Right, EJumpDirection::UpLeft, EJumpMontage::Right, JumpRight) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::UpLeft, EJumpMontage::Right, JumpRightShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::UpRight, EJumpMontage::Right, JumpRightShortIn) });

	///*Jump DownLeft variations*/
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpMontage::DownLeftShortOut, JumpDownLeftShortOut) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpDirection::None, EJumpMontage::DownLeftShortIn, JumpDownLeftShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpMontage::DownLeftShort, JumpDownLeftShort) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownLeft, EJumpDirection::Left, EJumpMontage::DownLeftToLeft, JumpDownLeftToLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpDirection::Left, EJumpMontage::DownLeftShortToLeft, JumpDownLeftShortToLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpMontage::DownLeftToDownRight, JumpDownLeftToDownRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpMontage::DownLeftShortToDownRight, JumpDownLeftShortToDownRight) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpDirection::Left, EJumpMontage::DownLeftShortToLeft, JumpDownLeftShortToLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpMontage::DownLeftShortToDownRight, JumpDownLeftShortToDownRight) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownLeft, EJumpDirection::UpLeft, EJumpMontage::DownLeft, JumpDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::DownLeft, EJumpDirection::UpLeft, EJumpMontage::DownLeft, JumpDownLeft) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpLeft, EJumpDirection::DownLeft, EJumpDirection::None, EJumpMontage::DownLeft, JumpDownLeft) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownLeft, EJumpDirection::None, EJumpMontage::DownLeftShortIn, JumpDownLeftShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownLeft, EJumpDirection::Right, EJumpMontage::DownLeft, JumpDownLeft) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownLeft, EJumpDirection::None, EJumpMontage::DownLeft, JumpDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpMontage::DownLeftShortOut, JumpDownLeftShortOut) });

	///*Jump DownRight variations*/

	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpMontage::DownRightShortOut, JumpDownRightShortOut) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpDirection::None, EJumpMontage::DownRightShortIn, JumpDownRightShortIn) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpMontage::DownRightShort, JumpDownRightShort) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownRight, EJumpDirection::Right, EJumpMontage::DownRightToRight, JumpDownRightToRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpDirection::Right, EJumpMontage::DownRightShortToRight, JumpDownRightShortToRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpMontage::DownRightToDownLeft, JumpDownRightToDownLeft) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpMontage::DownRightShortToDownLeft, JumpDownRightShortToDownLeft) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpDirection::Right, EJumpMontage::DownRightShortToRight, JumpDownRightShortToRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpMontage::DownRightShortToDownLeft, JumpDownRightShortToDownLeft) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownRight, EJumpDirection::UpRight, EJumpMontage::DownRight, JumpDownRight) });
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::DownRight, EJumpDirection::UpRight, EJumpMontage::DownRight, JumpDownRight) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::UpRight, EJumpDirection::DownRight, EJumpDirection::None, EJumpMontage::DownRight, JumpDownRight) });
	//
	//MappedJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownRight, EJumpDirection::None, EJumpMontage::DownRightShortIn, JumpDownRightShortIn) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownRight, EJumpDirection::Left, EJumpMontage::DownRight, JumpDownRight) });


	//MappedJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownRight, EJumpDirection::None, EJumpMontage::DownRight, JumpDownRight) });

	//MappedJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpMontage::DownRightShortOut, JumpDownRightShortOut) });
	
	/*Jump Left variations*/
	LeftJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::None, EJumpMontage::Left, JumpLeft) });
	LeftJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::Left, EJumpDirection::None, EJumpMontage::LeftShortIn, JumpLeftShortIn) });
	LeftJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::Left, EJumpDirection::Left, EJumpMontage::LeftShort, JumpLeftShort) });
	LeftJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::Left, EJumpMontage::LeftShortOut, JumpLeftShortOut) });

	LeftJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftShortInToDownLeft, JumpLeftShortInToDownLeft) });
	LeftJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::Left, EJumpDirection::DownRight,EJumpMontage::LeftShortInToDownRight, JumpLeftShortInToDownRight) }); //

	LeftJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Left, EJumpDirection::None, EJumpMontage::LeftShortIn, JumpLeftShortIn) });
	LeftJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Left, EJumpDirection::Left, EJumpMontage::LeftShort, JumpLeftShort) });
	LeftJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftShortInToDownLeft, JumpLeftShortInToDownLeft) });
	LeftJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Left, EJumpDirection::DownRight, EJumpMontage::LeftShortInToDownRight, JumpLeftShortInToDownRight) }); //Added by GPT

	LeftJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Left, EJumpDirection::None, EJumpMontage::Left, JumpLeftShortIn) });
	LeftJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Left, EJumpDirection::Left, EJumpMontage::LeftShort, JumpLeftShort) }); //Added by GPT
	LeftJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftShortInToDownLeft, JumpLeftShortInToDownLeft) }); //Added by GPT
	LeftJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Left, EJumpDirection::DownRight, EJumpMontage::Left, JumpLeft) }); //Added by GPT

	LeftJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::Right, EJumpMontage::Left, JumpLeft) }); //Added by GPT
	LeftJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::DownLeft, EJumpMontage::LeftToDownLeft, JumpLeftToDownLeft) });
	
	LeftJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Left, EJumpDirection::DownRight, EJumpMontage::LeftToDownRight, JumpLeftToDownRight) }); //EJumpMontage::LeftToDownRight, JumpLeftToDownRight  //TODO: could add another animation from left to downRight later
	
	/*Jump Right variations*/
	RightJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::None, EJumpMontage::Right, JumpRight) });
	RightJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::None, EJumpMontage::RightShortIn, JumpRightShortIn) });
	RightJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::None, EJumpMontage::RightShortIn, JumpRightShortIn) });
	RightJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::Right, EJumpMontage::Right, JumpRightShort) });
	RightJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::Right, EJumpMontage::RightShortOut, JumpRightShortOut) });

	RightJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::DownLeft, EJumpMontage::RightShortInToDownLeft, JumpRightShortInToDownLeft) });

	RightJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::Right, EJumpDirection::DownRight, EJumpMontage::RightShortInToDownRight, JumpRightShortInToDownRight) });
	RightJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::DownRight, EJumpMontage::RightToDownRight, JumpRightToDownRight) });

	RightJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Right, EJumpDirection::None, EJumpMontage::RightShortIn, JumpRightShortIn) });
	RightJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Right, EJumpDirection::Right, EJumpMontage::RightShort, JumpRightShort) });
	RightJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Right, EJumpDirection::DownRight, EJumpMontage::RightShortInToDownRight, JumpRightShortInToDownRight) });
	RightJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::Right, EJumpDirection::DownLeft, EJumpMontage::RightShortInToDownLeft, JumpRightShortInToDownLeft) }); //Added by GPT

	RightJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Right, EJumpDirection::None, EJumpMontage::RightShortIn, JumpRightShortIn) });
	RightJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Right, EJumpDirection::Right, EJumpMontage::RightShort, JumpRightShort) }); //Added by GPT
	RightJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Right, EJumpDirection::DownRight, EJumpMontage::RightShortInToDownRight, JumpRightShortInToDownRight) }); //Added by GPT
	RightJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::Right, EJumpDirection::DownLeft, EJumpMontage::Right, JumpRight) }); //Added by GPT

	RightJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::Left, EJumpMontage::Right, JumpRight) }); //Added by GPT
	RightJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::Right, EJumpDirection::DownLeft, EJumpMontage::RightToDownLeft, JumpRightToDownLeft) });//EJumpMontage::RightToDownLeft, JumpRightToDownLeft //TODO: could add another animation from right to downLeft later
	
	/*Jump DownLeft variations*/
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownLeft, EJumpDirection::None, EJumpMontage::DownLeft, JumpDownLeft) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpDirection::None, EJumpMontage::DownLeftShortIn, JumpDownLeftShortIn) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpMontage::DownLeftShort, JumpDownLeftShort) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpDirection::Left, EJumpMontage::DownLeftShortInToLeft, JumpDownLeftShortInToLeft) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpDirection::Right, EJumpMontage::DownLeftShortIn, JumpDownLeftShortIn) }); //Added by GPT

	DownLeftJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpDirection::None, EJumpMontage::DownLeftShortIn, JumpDownLeftShortIn) }); //Added by GPT
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpMontage::DownLeftShort, JumpDownLeftShort) }); //Added by GPT
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpDirection::Left, EJumpMontage::DownLeftShortInToLeft, JumpDownLeftShortInToLeft) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpDirection::Right, EJumpMontage::DownLeftShortInToDownRight, JumpDownLeftShortInToDownRight) });

	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownLeft, EJumpDirection::None, EJumpMontage::DownLeftShortIn, JumpDownLeftShortIn) });

	DownLeftJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownLeft, EJumpDirection::Right, EJumpMontage::DownLeftToRight, JumpDownLeftToRight) });

	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownLeft, EJumpDirection::Right, EJumpMontage::DownLeftShortInToRight, JumpDownLeftShortInToRight) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpDirection::Right, EJumpMontage::DownLeftShortInToRight, JumpDownLeftShortInToRight) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpDirection::Right, EJumpMontage::DownLeftShortInToRight, JumpDownLeftShortInToRight) });

	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownLeft, EJumpDirection::Left, EJumpMontage::DownLeftShortInToLeft, JumpDownLeftShortInToLeft) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpMontage::DownLeftToDownRight, JumpDownLeftToDownRight) });

	DownLeftJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpMontage::DownLeftShortOut, JumpDownLeftShortOut) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownLeft, EJumpDirection::Left, EJumpMontage::DownLeftToLeft, JumpDownLeftToLeft) });
	
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpMontage::DownLeftShortInToDownRight, JumpDownLeftShortInToDownRight) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpMontage::DownLeftShort, JumpDownLeftShort) });
	
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownLeft, EJumpDirection::None, EJumpMontage::DownLeftShortIn, JumpDownLeftShortIn) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownLeft, EJumpDirection::None, EJumpMontage::DownLeftShortIn, JumpDownLeftShortIn) });
	
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownLeft, EJumpDirection::Right, EJumpMontage::DownLeftShortIn, JumpDownLeftShortInToRight) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpMontage::DownLeftShortInToDownRight, JumpDownLeftShortInToDownRight) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownLeft, EJumpDirection::DownLeft, EJumpMontage::DownLeftShort, JumpDownLeftShort) });
	DownLeftJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownLeft, EJumpDirection::Left, EJumpMontage::DownLeftShortInToLeft, JumpDownLeftShortInToLeft) });
	
	
	
	/*Jump DownRight variations*/
	DownRightJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownRight, EJumpDirection::None, EJumpMontage::DownRight, JumpDownRight) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpDirection::None, EJumpMontage::DownRightShortIn, JumpDownRightShortIn) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpMontage::DownRightShort, JumpDownRightShort) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpDirection::Right, EJumpMontage::DownRightShortInToRight, JumpDownRightShortInToRight) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpDirection::Left, EJumpMontage::DownRightShortIn, JumpDownRightShortIn) }); //Added by GPT
	
	DownRightJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpDirection::None, EJumpMontage::DownRightShortIn, JumpDownRightShortIn) }); //Added by GPT
	DownRightJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpMontage::DownRightShort, JumpDownRightShort) }); //Added by GPT
	DownRightJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpDirection::Right, EJumpMontage::DownRightShortInToRight, JumpDownRightShortInToRight) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpDirection::Left, EJumpMontage::DownRightShortIn, JumpDownRightShortIn) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownRight, EJumpDirection::Left, EJumpMontage::DownRightToLeft, JumpDownRightToLeft) });

	DownRightJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownRight, EJumpDirection::Left, EJumpMontage::DownRightShortInToLeft, JumpDownRightShortInToLeft) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::DownLeft, EJumpDirection::DownRight, EJumpDirection::Left, EJumpMontage::DownRightShortInToLeft, JumpDownRightShortInToLeft) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpDirection::Left, EJumpMontage::DownRightShortInToLeft, JumpDownRightShortInToLeft) });

	DownRightJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownRight, EJumpDirection::Right, EJumpMontage::DownRightShortInToRight, JumpDownRightShortInToRight) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpMontage::DownRightToDownLeft, JumpDownRightToDownLeft) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpMontage::DownRightShortOut, JumpDownRightShortOut) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::None, EJumpDirection::DownRight, EJumpDirection::Right, EJumpMontage::DownRightToRight, JumpDownRightToRight) });
	
	DownRightJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpMontage::DownRightShortInToDownLeft, JumpDownRightShortInToDownLeft) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpMontage::DownRightShort, JumpDownRightShort) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownRight, EJumpDirection::None, EJumpMontage::DownRightShortIn, JumpDownRightShortIn) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownRight, EJumpDirection::None, EJumpMontage::DownRightShortIn, JumpDownRightShortIn) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::Right, EJumpDirection::DownRight, EJumpDirection::Left, EJumpMontage::DownRightShortIn, JumpDownRightShortInToLeft) });
	
	DownRightJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownRight, EJumpDirection::DownLeft, EJumpMontage::DownRightShortInToDownLeft, JumpDownRightShortInToDownLeft) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownRight, EJumpDirection::DownRight, EJumpMontage::DownRightShort, JumpDownRightShort) });
	DownRightJumps.Add({ FFrogJump(EJumpDirection::Left, EJumpDirection::DownRight, EJumpDirection::Right, EJumpMontage::DownRightShortInToRight, JumpDownRightShortInToRight) });

	
	/*FrogMesh->OnClicked.AddDynamic(this, &AFrog::OnClicked);
	FrogMesh->OnReleased.AddDynamic(this, &AFrog::OnReleased);
	FrogMesh->OnInputTouchBegin.AddDynamic(this, &AFrog::OnTouchStart);
	FrogMesh->OnInputTouchEnd.AddDynamic(this, &AFrog::OnTouchEnd);*/

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



void AFrog::Jump_Implementation(const TArray<FVector>& InMarkedSlots)
//void AFrog::Jump_Implementation(const TMap<FVector, ESlotType>& InMappedJumps, const TArray<FVector>& InMarkedSlots)
{
	MarkedJumpDirections.Empty();
	MarkedJumpAnims.Empty();
	MarkedJumps.Empty();

	MarkedSlots = InMarkedSlots;
	MarkedSlots.Insert(GetActorLocation(), 0);
	
	
	//MappedMarkedJumps = InMappedJumps;
	
	CurrentJumpIndex = 0;
	int i = 0;
	while (i < MarkedSlots.Num()-1)
	{
		FVector Delta = MarkedSlots[i+1] - MarkedSlots[i];
		if (Delta.X == 0 && Delta.Y > 0)
		{
			MarkedJumpDirections.Add(EJumpDirection::Right);
			MarkedJumpAnims.Add(JumpRight);
			MarkedJumps.Add(EJumpMontage::Right);
		}
		else if (Delta.X == 0 && Delta.Y < 0)
		{
			MarkedJumpDirections.Add(EJumpDirection::Left);
			MarkedJumpAnims.Add(JumpLeft);
			MarkedJumps.Add(EJumpMontage::Left);
			// Left
		}
		else if (Delta.X > 0 && Delta.Y > 0)
		{
			MarkedJumpDirections.Add(EJumpDirection::UpRight);
			MarkedJumpAnims.Add(JumpUpRight);
			MarkedJumps.Add(EJumpMontage::UpRight);
			// UpRight
		}
		else if (Delta.X > 0 && Delta.Y < 0)
		{
			MarkedJumpDirections.Add(EJumpDirection::UpLeft);
			MarkedJumpAnims.Add(JumpUpLeft);
			MarkedJumps.Add(EJumpMontage::UpLeft);
			// UpLeft
		}
		else if (Delta.X < 0 && Delta.Y > 0)
		{
			MarkedJumpDirections.Add(EJumpDirection::DownRight);
			MarkedJumpAnims.Add(JumpDownRight);
			MarkedJumps.Add(EJumpMontage::DownRight);
			// DownRight
		}
		else if (Delta.X < 0 && Delta.Y < 0)
		{
			MarkedJumpDirections.Add(EJumpDirection::DownLeft);
			MarkedJumpAnims.Add(JumpDownLeft);
			MarkedJumps.Add(EJumpMontage::DownLeft);
			// DownLeft
		}
		i++;
	}
	GenerateMergedJumps();
	PerformJump(); 
}
//void AFrog::AddJumpSingle()
//{
//	switch (CurrentJump)
//	{
//	case EJumpDirection::Right:
//		MarkedJumpAnims.Add(JumpRight);
//		MarkedJumps.Add(EJumpMontage::Right);
//		break;
//	case EJumpDirection::Left:
//		MarkedJumpAnims.Add(JumpLeft);
//		MarkedJumps.Add(EJumpMontage::Left);
//		break;
//	case EJumpDirection::UpRight:
//		MarkedJumpAnims.Add(JumpUpRight);
//		MarkedJumps.Add(EJumpMontage::UpRight);
//		break;
//	case EJumpDirection::UpLeft:
//		MarkedJumpAnims.Add(JumpUpLeft);
//		MarkedJumps.Add(EJumpMontage::UpLeft);
//		break;
//	case EJumpDirection::DownRight:
//		MarkedJumpAnims.Add(JumpDownRight);
//		MarkedJumps.Add(EJumpMontage::DownRight);
//		break;
//	case EJumpDirection::DownLeft:
//		MarkedJumpAnims.Add(JumpDownLeft);
//		MarkedJumps.Add(EJumpMontage::DownLeft);
//		break;
//	default:
//		break;
//	}
//}
void AFrog::GenerateMergedJumps()
{
	if (MarkedJumpDirections.Num() > 1)
	{
		MarkedJumpAnims.Empty();
		MarkedJumps.Empty();

		EJumpDirection LastJump = EJumpDirection::None;
		for (int32 i = 0; i < MarkedJumpDirections.Num(); i++)
		{
			EJumpDirection CurrentJump = MarkedJumpDirections[i];
			if (LastJump == EJumpDirection::UpRight || LastJump == EJumpDirection::UpLeft)
			{
				LastJump = EJumpDirection::None;
			}			
			//For UpRight and UpLeft we don't need to worry about what "transition variant" animation to play
			if (CurrentJump == EJumpDirection::UpRight)
			{
				MarkedJumpAnims.Add(JumpUpRight);
				MarkedJumps.Add(EJumpMontage::UpRight);
				LastJump = CurrentJump;
			}
			else if (CurrentJump == EJumpDirection::UpLeft)
			{
				MarkedJumpAnims.Add(JumpUpLeft);
				MarkedJumps.Add(EJumpMontage::UpLeft);
				LastJump = CurrentJump;
			}
			else
			{
				EJumpDirection NextJump = EJumpDirection::None;
				if (MarkedJumpDirections.Num() > i + 1)
				{
					NextJump = MarkedJumpDirections[i + 1];
					if (NextJump == EJumpDirection::UpRight || NextJump == EJumpDirection::UpLeft)
					{
						NextJump = EJumpDirection::None;
					}
				}				
				bool bFoundVariant = false; //TODO: remove this, it's for safety until we make it work with all the variations
				//FFrogJump Variant = { LastJump, CurrentJump, NextJump };

				TArray<FFrogJump>* MappedJumps = nullptr;
				switch (CurrentJump)
				{
				case EJumpDirection::Right:
					MappedJumps = &RightJumps;
					break;				
				case EJumpDirection::Left:
					MappedJumps = &LeftJumps;
					break;
				case EJumpDirection::DownRight:
					MappedJumps = &DownRightJumps;
					break;
				case EJumpDirection::DownLeft:
					MappedJumps = &DownLeftJumps;
					break;
				default:
					break;
				}
				for (const FFrogJump& Variant : *MappedJumps)
				{
					if (Variant.Prev == LastJump && Variant.Current == CurrentJump && Variant.Next == NextJump)
					{
						MarkedJumpAnims.Add(Variant.Montage);
						MarkedJumps.Add(Variant.MontageName);
						LastJump = CurrentJump;
						bFoundVariant = true;
						break;
					}
				}
				if (!bFoundVariant)//TODO: remove this, it's for safety until we make it work with all the variations
				{
					MarkedJumpAnims.Add(Error);
					MarkedJumps.Add(EJumpMontage::Error);
				}
			}
		}
	}

	 
	//for (int32 i = 0; i < MarkedJumpDirections.Num(); i++)
	//{
	//	EJumpDirection CurrentJump = MarkedJumpDirections[i];

	//	bool bTransitionPlayed = false;

	//	// Check if a transition montage is needed
	//	TPair<EFrogJump, EFrogJump> Key = { LastJump, CurrentJump };
	//	if (JumpTransitions.Contains(Key))
	//	{
	//		MarkedJumps.Add(JumpTransitions[Key]);
	//		bTransitionPlayed = true;

	//		// Only advance LastJump if transition represents a new "effective" jump
	//		LastJump = JumpTransitions[Key];
	//	}

	//	// Only add the base jump if the transition did NOT replace it
	//	if (!bTransitionPlayed)
	//	{
	//		MarkedJumps.Add(CurrentJump);
	//		LastJump = CurrentJump;
	//	}
	//}

	UE_LOG(LogTemp, Log, TEXT("=== Generated Jump Sequence ==="));
	for (int32 i = 0; i < MarkedJumpDirections.Num(); i++)
	{
		FString JumpName = StaticEnum<EJumpDirection>()->GetNameStringByValue((int64)MarkedJumpDirections[i]);
		UE_LOG(LogTemp, Log, TEXT("%d: %s"), i, *JumpName);
	}
	UE_LOG(LogTemp, Log, TEXT("=== End of Sequence ==="));

	UE_LOG(LogTemp, Log, TEXT("=== Generated MarkedJumps enums ==="));
	for (int32 i = 0; i < MarkedJumps.Num(); i++)
	{
		FString JumpName = StaticEnum<EJumpMontage>()->GetNameStringByValue((int64)MarkedJumps[i]);
		UE_LOG(LogTemp, Log, TEXT("%d: %s"), i, *JumpName);
	}
	UE_LOG(LogTemp, Log, TEXT("=== End of Sequence ==="));
}


void AFrog::PerformJump()
{
	UAnimInstance* AnimInstance = FrogMesh->GetAnimInstance();
	if (AnimInstance)
	{
		if (UAnimMontage* FoundMontage = MarkedJumpAnims[CurrentJumpIndex])
		{
			AnimInstance->Montage_Play(FoundMontage);

		}

		/*if (UAnimMontage* FoundMontage = JumpMontageMap.FindRef(MarkedJumps[CurrentJumpIndex]))
		{
			AnimInstance->Montage_Play(FoundMontage);
			
		}*/
		/*if (UAnimMontage** FoundMontage = JumpMontageMap.Find(MarkedJumps[CurrentJumpIndex]))
		{
			MontageToPlay = *FoundMontage;
			AnimInstance->Montage_Play(*FoundMontage);
		}*/
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("WARNING: No montage found for jump type %d"), (int32)MarkedJumps[CurrentJumpIndex]);
			FString JumpName = StaticEnum<EJumpMontage>()->GetNameStringByValue((int64)MarkedJumps[CurrentJumpIndex]);
			FString JumpNameAnim = StaticEnum<EJumpDirection>()->GetNameStringByValue((int64)MarkedJumpDirections[CurrentJumpIndex]);
			UE_LOG(LogTemp, Warning, TEXT("WARNING: No montage found for jump direction: %s, variant: %s"),  *JumpNameAnim, *JumpName);
		}
	}
}
void AFrog::DestroyFrog_Implementation()
{
	Destroy();
	
}
void AFrog::JumpAway_Implementation()
{
	
	/*FrogMesh->SetSimulatePhysics(true);
	FrogMesh->SetEnableGravity(true);
	FrogMesh->SetCollisionProfileName(TEXT("BlockAll"));*/

	//TODO:: Add frog jumping into water animation
	UAnimInstance* AnimInstance = FrogMesh->GetAnimInstance();
	if (AnimInstance)
	{
		if (SwimAway)
		{
			AnimInstance->Montage_Play(SwimAway);
			//AnimInstance->Montage_Play(LeaveBwdLeft);
			//BoxMesh->SetCollisionProfileName(TEXT("NoCollision"));
			//BoxMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
			{
				if (GM->Implements<UGameModeInterface>())
				{
					/*	FVector First = MarkedSlots[0];
						FVector Second = MarkedSlots[1];

						FVector test = (First + Second) /2;*/
					FVector WaterSplashLoc = GetActorLocation() + FVector(90.f, 87.0f, -15.0f);

					/*(X = 448.000000, Y = 448.000000, Z = 202.000000)
					(X = 546.319990, Y = 551.376322, Z = 193.396221)*/
					IGameModeInterface::Execute_SetupSplashEffect(GM, WaterSplashLoc);
					//IGameModeInterface::Execute_AddSlot(GM, (MarkedSlots[CurrentJumpIndex]));
				}
			}
		}
		
		//else
		{
			//UE_LOG(LogTemp, Warning, TEXT("WARNING: No montage found for jump type %d"), (int32)MarkedJumps[CurrentJumpIndex]);
			//FString JumpName = StaticEnum<EJumpMontage>()->GetNameStringByValue((int64)MarkedJumps[CurrentJumpIndex]);
			//FString JumpNameAnim = StaticEnum<EJumpDirection>()->GetNameStringByValue((int64)MarkedJumpDirections[CurrentJumpIndex]);
			//UE_LOG(LogTemp, Warning, TEXT("WARNING: No montage found for jump direction: %s, variant: %s"), *JumpNameAnim, *JumpName);
		}
	}
}
// Called when the game starts or when spawned
void AFrog::BeginPlay()
{
	Super::BeginPlay();

	UAnimInstance* Anim = Cast<UAnimInstance>(FrogMesh->GetAnimInstance());
	Anim->OnMontageEnded.AddDynamic(this, &AFrog::OnAnyMontageEnded);


	//AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAICharacterBase::OnPerceptionUpdated);
	//AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AAICharacterBase::OnPerceptionUpdated);
	//PawnPerceptionComp->OnSeePawn.AddDynamic(this, &AAICharacterBase::OnPawnSeen);
}
//void AFrog::PlayNextAnimation_Implementation()
//{
//	UE_LOG(LogTemp, Warning, TEXT("PlayNextAnimation_Implementation called."));
//
//	CurrentJumpIndex++;
//	SetActorLocation(MarkedSlots[CurrentJumpIndex]);
//
//
//	if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
//	{
//		if (GM->Implements<UGameModeInterface>())
//		{
//			/*	FVector First = MarkedSlots[0];
//				FVector Second = MarkedSlots[1];
//
//				FVector test = (First + Second) /2;*/
//			IGameModeInterface::Execute_RemoveFrogAddSlot(GM, MarkedSlots[CurrentJumpIndex - 1], MarkedSlots[CurrentJumpIndex]);
//			//IGameModeInterface::Execute_AddSlot(GM, (MarkedSlots[CurrentJumpIndex]));
//		}
//	}
//
//	if (CurrentJumpIndex < MarkedJumpDirections.Num())
//	{
//		PerformJump();
//	}
//	else if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
//	{
//		if (GM->Implements<UGameModeInterface>())
//		{
//			/*	FVector First = MarkedSlots[0];
//				FVector Second = MarkedSlots[1];
//
//				FVector test = (First + Second) /2;*/
//			IGameModeInterface::Execute_FrogJumpingEnded(GM);
//			//IGameModeInterface::Execute_AddSlot(GM, (MarkedSlots[CurrentJumpIndex]));
//		}
//
//	}
//	/*else 
//	{
//		SetActorLocation(MarkedSlots[CurrentJumpIndex + 1]);
//		CurrentJumpIndex++;
//		if (CurrentJumpIndex < MarkedJumpDirections.Num())
//		{
//			PerformJump();
//		}
//	}*/
//}
void AFrog::SpellCastTeleportOut_Implementation()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UObject* GM = (UObject*)World->GetAuthGameMode();
		if (GM && GM->Implements<UGameModeInterface>())
		{
			IGameModeInterface::Execute_FrogsTeleportOut(GM, this);
		}
	}
}

void AFrog::OnAnyMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("OnAnyMontageEnded called for  %s, with bInterrupted = %s."), *Montage->GetName(), bInterrupted ? *FString(TEXT("True")) : *FString(TEXT("False")));
	/*if (CurrentJumpIndex == 0 && Montage->GetName().Contains("CastingSpell"))
	{
		if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
		{
			if (GM->Implements<UGameModeInterface>())
			{
				IGameModeInterface::Execute_FrogsTeleportOut(GM, this);
			}
		}
	}
	else
	{*/
		CurrentJumpIndex++;
		if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
		{
			if (GM->Implements<UGameModeInterface>())
			{
				/*	FVector First = MarkedSlots[0];
					FVector Second = MarkedSlots[1];

					FVector test = (First + Second) /2;*/
				IGameModeInterface::Execute_RemoveFrogAddSlot(GM, MarkedSlots[CurrentJumpIndex - 1], MarkedSlots[CurrentJumpIndex]);
				//IGameModeInterface::Execute_AddSlot(GM, (MarkedSlots[CurrentJumpIndex]));
			}
		}
		SetActorLocation(MarkedSlots[CurrentJumpIndex]);
		if (CurrentJumpIndex < MarkedJumpDirections.Num())
		{
			PerformJump();
		}
		else if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
		{
			if (GM->Implements<UGameModeInterface>())
			{
				/*	FVector First = MarkedSlots[0];
				FVector Second = MarkedSlots[1];

				FVector test = (First + Second) /2;*/
				IGameModeInterface::Execute_FrogJumpingEnded(GM, this, MarkedSlots[CurrentJumpIndex - 1]);
				//IGameModeInterface::Execute_AddSlot(GM, (MarkedSlots[CurrentJumpIndex]));
			}
		}
	//}
}
//void AMyCharacter::WarmupMontages() //TODO: Add preload to animations and effects
//{
//	UAnimInstance* Anim = GetMesh()->GetAnimInstance();
//
//	for (UAnimMontage* Montage : JumpMontages)
//	{
//		if (!Montage) continue;
//
//		Anim->Montage_Play(Montage, 0.001f);
//		Anim->Montage_Stop(0.f, Montage);
//	}
//}
// 
// 
//void AFrog::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void AFrog::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

