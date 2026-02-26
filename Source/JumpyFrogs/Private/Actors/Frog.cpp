// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Actors/Frog.h"
//#include "Particles/ParticleSystemComponent.h"
//#include "Components/CapsuleComponent.h"
//#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
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
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpRightShortInOutObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpLeftShortInOutObj;

	/*	ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdRightShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdRightShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdRightShortInOutObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdLeftShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdLeftShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpFwdLeftShortInOutObj;*/

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdRightShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdRightShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdRightShortInOutObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdLeftShortInObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdLeftShortOutObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpBwdLeftShortInOutObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownRightToDownLeftObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownLeftToDownRightObj;

		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownRightToRightObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownRightToLeftObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownLeftToRightObj;
		ConstructorHelpers::FObjectFinder<UAnimMontage> JumpDownLeftToLeftObj;
		

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
			, JumpRightShortInOutObj(TEXT("/Game/Frog/Animations/Montages/JumpRightShortInOut_Montage"))
			
			, JumpLeftShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpLeftShortIn_Montage"))
			, JumpLeftShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpLeftShortOut_Montage"))
			, JumpLeftShortInOutObj(TEXT("/Game/Frog/Animations/Montages/JumpLeftShortInOut_Montage"))

			/*, JumpFwdRightShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdRightShortIn_Montage"))
			, JumpFwdRightShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdRightShortOut_Montage"))
			, JumpFwdRightShortInOutObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdRightShortInOut_Montage"))

			, JumpFwdLeftShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdLeftShortIn_Montage"))
			, JumpFwdLeftShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdLeftShortOut_Montage"))
			, JumpFwdLeftShortInOutObj(TEXT("/Game/Frog/Animations/Montages/JumpFwdLeftShortInOut_Montage"))*/

			, JumpBwdRightShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdRightShortIn_Montage"))
			, JumpBwdRightShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdRightShortOut_Montage"))
			, JumpBwdRightShortInOutObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdRightShortInOut_Montage"))

			, JumpBwdLeftShortInObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdLeftShortIn_Montage"))
			, JumpBwdLeftShortOutObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdLeftShortOut_Montage"))
			, JumpBwdLeftShortInOutObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdLeftShortInOut_Montage"))

			, JumpDownRightToDownLeftObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdRightToBwdLeft_Montage"))
			, JumpDownLeftToDownRightObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdLeftToBwdRight_Montage"))

			, JumpDownRightToRightObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdRightToRight_Montage"))
			, JumpDownRightToLeftObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdRightToLeft_Montage"))
			, JumpDownLeftToRightObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdLeftToRightObj_Montage"))
			, JumpDownLeftToLeftObj(TEXT("/Game/Frog/Animations/Montages/JumpBwdLeftToLeftObj"))
			
			/*/Script/Engine.AnimMontage'/Game/Frog/Animations/Montages/JumpLeftShorInOut_Montage.JumpLeftShorInOut_Montage'
/Script/Engine.AnimMontage'/Game/Frog/Animations/Montages/JumpLeftShorOut_Montage.JumpLeftShorOut_Montage'
/Script/Engine.AnimMontage'/Game/Frog/Animations/Montages/JumpLeftShortIn_Montage.JumpLeftShortIn_Montage'*/

		{
		}
	};

	BoxMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxMesh->bHiddenInGame = false;
	BoxMesh->SetBoxExtent(FVector(80.f, 70.f, 10.f));
	BoxMesh->SetCollisionProfileName(TEXT("EmptySlotProfile"));
	RootComponent = BoxMesh;

	static FConstructorStatics ConstructorStatics;


	
	FrogMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FrogMesh"));
	FrogMesh->SetSkeletalMesh(ConstructorStatics.FrogMeshObj.Object);

	FrogMesh->SetupAttachment(RootComponent);

	//FrogMesh->SetRelativeLocation(FVector(0.f, 0.f, -80.0f));
	FrogMesh->bCastDynamicShadow = true;


	if (ConstructorStatics.FrogAnimBPObj.Class != NULL)
	{
		FrogMesh->SetAnimInstanceClass(ConstructorStatics.FrogAnimBPObj.Class);
	}

	JumpRightMontage = ConstructorStatics.JumpRightObj.Object;
	JumpLeftMontage = ConstructorStatics.JumpLeftObj.Object;
	JumpUpRightMontage = ConstructorStatics.JumpFwdRightObj.Object;
	JumpUpLeftMontage = ConstructorStatics.JumpFwdLeftObj.Object;
	JumpDownRightMontage = ConstructorStatics.JumpBwdRightObj.Object;
	JumpDownLeftMontage = ConstructorStatics.JumpBwdLeftObj.Object;

	JumpRightShortIn = ConstructorStatics.JumpRightShortInObj.Object;
	JumpRightShortOut = ConstructorStatics.JumpRightShortOutObj.Object;
	JumpRightShortInOut = ConstructorStatics.JumpRightShortInOutObj.Object;

	JumpLeftShortIn = ConstructorStatics.JumpLeftShortInObj.Object;
	JumpLeftShortOut = ConstructorStatics.JumpLeftShortOutObj.Object;
	JumpLeftShortInOut = ConstructorStatics.JumpLeftShortInOutObj.Object;

	/*JumpUpRightShortIn = ConstructorStatics.JumpFwdRightShortInObj.Object;
	JumpUpRightShortOut = ConstructorStatics.JumpFwdRightShortOutObj.Object;
	JumpUpRightShortInOut = ConstructorStatics.JumpFwdRightShortInOutObj.Object;

	JumpUpLeftShortIn = ConstructorStatics.JumpFwdLeftShortInObj.Object;
	JumpUpLeftShortOut = ConstructorStatics.JumpFwdLeftShortOutObj.Object;
	JumpUpLeftShortInOut = ConstructorStatics.JumpFwdLeftShortInOutObj.Object;*/

	JumpDownRightShortIn = ConstructorStatics.JumpBwdRightShortInObj.Object;
	JumpDownRightShortOut = ConstructorStatics.JumpBwdRightShortOutObj.Object;
	JumpDownRightShortInOut = ConstructorStatics.JumpBwdRightShortInOutObj.Object;

	JumpDownLeftShortIn = ConstructorStatics.JumpBwdLeftShortInObj.Object;
	JumpDownLeftShortOut = ConstructorStatics.JumpBwdLeftShortOutObj.Object;
	JumpDownLeftShortInOut = ConstructorStatics.JumpBwdLeftShortInOutObj.Object;

	JumpDownRightToDownLeft = ConstructorStatics.JumpDownRightToLeftObj.Object;
	JumpDownLeftToDownRight = ConstructorStatics.JumpDownLeftToRightObj.Object;

	JumpDownRightToRight = ConstructorStatics.JumpDownRightToRightObj.Object;
	JumpDownRightToLeft = ConstructorStatics.JumpDownRightToLeftObj.Object;
	JumpDownLeftToRight = ConstructorStatics.JumpDownLeftToRightObj.Object;
	JumpDownLeftToLeft = ConstructorStatics.JumpDownLeftToLeftObj.Object;

	MatBlue = ConstructorStatics.BlueMaterial.Get();
	MatOrange = ConstructorStatics.OrangeMaterial.Get();
	MatGreen = ConstructorStatics.GreenMaterial.Get();
	MatRedEye = ConstructorStatics.RedEyeMaterial.Get();
	MatStrawberry = ConstructorStatics.StrawberryMaterial.Get();
	MatBombFrog = ConstructorStatics.BombFrogMaterial.Get();
	//RedMatBombFrog = ConstructorStatics.RedBombFrogMaterial.Get();

	JumpMontageMap =
	{
		// Base directions
		{ EFrogJump::Right,        JumpRightMontage },
		{ EFrogJump::Left,         JumpLeftMontage },
		{ EFrogJump::UpRight,      JumpUpRightMontage },
		{ EFrogJump::UpLeft,       JumpUpLeftMontage },
		{ EFrogJump::DownRight,    JumpDownRightMontage },
		{ EFrogJump::DownLeft,     JumpDownLeftMontage },

		// Right short variants
		{ EFrogJump::RightShortIn,    JumpRightShortIn },
		{ EFrogJump::RightShortOut,   JumpRightShortOut },
		{ EFrogJump::RightShortInOut, JumpRightShortInOut },

		// Left short variants
		{ EFrogJump::LeftShortIn,    JumpLeftShortIn },
		{ EFrogJump::LeftShortOut,   JumpLeftShortOut },
		{ EFrogJump::LeftShortInOut, JumpLeftShortInOut },

		// UpRight short variants
		//{ EFrogJump::UpRightShortIn,    JumpUpRightShortIn },
		//{ EFrogJump::UpRightShortOut,   JumpUpRightShortOut },
		//{ EFrogJump::UpRightShortInOut, JumpUpRightShortInOut },

		//// UpLeft short variants
		//{ EFrogJump::UpLeftShortIn,    JumpUpLeftShortIn },
		//{ EFrogJump::UpLeftShortOut,   JumpUpLeftShortOut },
		//{ EFrogJump::UpLeftShortInOut, JumpUpLeftShortInOut },

		// DownRight short variants
		{ EFrogJump::DownRightShortIn,    JumpDownRightShortIn },
		{ EFrogJump::DownRightShortOut,   JumpDownRightShortOut },
		{ EFrogJump::DownRightShortInOut, JumpDownRightShortInOut },

		// DownLeft short variants
		{ EFrogJump::DownLeftShortIn,    JumpDownLeftShortIn },
		{ EFrogJump::DownLeftShortOut,   JumpDownLeftShortOut },
		{ EFrogJump::DownLeftShortInOut, JumpDownLeftShortInOut },

		{ EFrogJump::DownRightToRight,     JumpDownRightToRight },
		{ EFrogJump::DownRightToLeft,      JumpDownRightToLeft },
		{ EFrogJump::DownLeftToRight,      JumpDownLeftToRight },
		{ EFrogJump::DownLeftToLeft,       JumpDownLeftToLeft },

		{ EFrogJump::DownRightToDownLeft,  JumpDownRightToDownLeft },
		{ EFrogJump::DownLeftToDownRight,  JumpDownLeftToDownRight },
	};

	TMap<TPair<EFrogJump, EFrogJump>, EFrogJump> JumpTransitions =
	{
		{ {EFrogJump::Left, EFrogJump::Left}, EFrogJump::LeftShortInOut },
		{ {EFrogJump::Left, EFrogJump::DownLeft}, EFrogJump::LeftToDownLeft },
		{ {EFrogJump::Right, EFrogJump::Right}, EFrogJump::RightShortInOut },
		{ {EFrogJump::Right, EFrogJump::DownRight}, EFrogJump::RightToDownRight },
		{ {EFrogJump::DownLeft, EFrogJump::DownLeft}, EFrogJump::DownLeftShortInOut },
		{ {EFrogJump::DownLeft, EFrogJump::Left}, EFrogJump::DownLeftToLeft },
		{ {EFrogJump::DownLeft, EFrogJump::Right}, EFrogJump::DownLeftToRight },
		{ {EFrogJump::DownLeft, EFrogJump::DownRight}, EFrogJump::DownLeftToDownRight },
		{ {EFrogJump::DownRight, EFrogJump::DownRight}, EFrogJump::DownRightShortInOut },
		{ {EFrogJump::DownRight, EFrogJump::Left}, EFrogJump::DownRightToLeft },
		{ {EFrogJump::DownRight, EFrogJump::Right}, EFrogJump::DownRightToRight },
		{ {EFrogJump::DownRight, EFrogJump::DownLeft}, EFrogJump::DownRightToDownLeft },
	};

	EFrogJump LastJump = EFrogJump::None;

	
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
{
	MarkedJumpDirections.Empty();
	MarkedSlots = InMarkedSlots;
	MarkedSlots.Insert(GetActorLocation(), 0);
	CurrentJumpIndex = 0;
	int i = 0;
	while (i < MarkedSlots.Num()-1)
	{
		FVector Delta = MarkedSlots[i+1] - MarkedSlots[i];
		if (Delta.X == 0 && Delta.Y > 0)
		{
			MarkedJumpDirections.Add(EFrogJump::Right);
		}
		else if (Delta.X == 0 && Delta.Y < 0)
		{
			MarkedJumpDirections.Add(EFrogJump::Left);
			// Left
		}
		else if (Delta.X > 0 && Delta.Y > 0)
		{
			MarkedJumpDirections.Add(EFrogJump::UpRight);
			// UpRight
		}
		else if (Delta.X > 0 && Delta.Y < 0)
		{
			MarkedJumpDirections.Add(EFrogJump::UpLeft);
			// UpLeft
		}
		else if (Delta.X < 0 && Delta.Y > 0)
		{
			MarkedJumpDirections.Add(EFrogJump::DownRight);
			// DownRight
		}
		else if (Delta.X < 0 && Delta.Y < 0)
		{
			MarkedJumpDirections.Add(EFrogJump::DownLeft);
			// DownLeft
		}
		i++;
	}
	GenerateMergedJumps();
	PerformJump(); 
	
}

void AFrog::Eliminate_Implementation()
{
	//TODO:: Add frog jumping into water animation
	Destroy();
}

void AFrog::PerformJump()
{
	UAnimInstance* AnimInstance = FrogMesh->GetAnimInstance();
	if (AnimInstance)
	{
		if (UAnimMontage* FoundMontage = JumpMontageMap.FindRef(MarkedJumps[CurrentJumpIndex]))
		{
			AnimInstance->Montage_Play(FoundMontage);
			
		}
		/*if (UAnimMontage** FoundMontage = JumpMontageMap.Find(MarkedJumps[CurrentJumpIndex]))
		{
			MontageToPlay = *FoundMontage;
			AnimInstance->Montage_Play(*FoundMontage);
		}*/
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("WARNING: No montage found for jump type %d"), (int32)MarkedJumps[CurrentJumpIndex]);
		}
	}
}
void AFrog::AddMergedDirection(
	EFrogJump Single,
	EFrogJump Out,
	EFrogJump InOut,
	EFrogJump In,
	int32 RepeatCount)
{
	// If the "short variants" are invalid (like swap montages or Fwd jumps), just repeat Single
	bool bHasShortVariants = (Out != Single || InOut != Single || In != Single);

	if (!bHasShortVariants)
	{
		// Just repeat the single montage
		for (int32 j = 0; j < RepeatCount; j++)
		{
			MarkedJumps.Add(Single);
		}
		return;
	}

	// Standard merged ShortIn/Out/InOut logic
	if (RepeatCount >= 3)
	{
		MarkedJumps.Add(Out);

		for (int32 j = 1; j < RepeatCount - 1; j++)
		{
			MarkedJumps.Add(InOut);
		}

		MarkedJumps.Add(In);
	}
	else if (RepeatCount == 2)
	{
		MarkedJumps.Add(Out);
		MarkedJumps.Add(In);
	}
	else
	{
		MarkedJumps.Add(Single);
	}
}
void AFrog::GenerateMergedJumps()
{
	MarkedJumps.Empty();

	int32 i = 0;

	while (i < MarkedJumpDirections.Num())
	{
		// Transition detection FIRST
		if (i + 1 < MarkedJumpDirections.Num())
		{
			EFrogJump Current = MarkedJumpDirections[i];
			EFrogJump Next = MarkedJumpDirections[i + 1];

			// ---------------------------------
			// DownRight transitions
			// ---------------------------------

			if (Current == EFrogJump::DownRight)
			{
				if (Next == EFrogJump::DownLeft)
				{
					MarkedJumps.Add(EFrogJump::DownRightToDownLeft);
					i += 2;
					continue;
				}

				if (Next == EFrogJump::Right)
				{
					MarkedJumps.Add(EFrogJump::DownRightToRight);
					i += 2;
					continue;
				}

				if (Next == EFrogJump::Left)
				{
					MarkedJumps.Add(EFrogJump::DownRightToLeft);
					i += 2;
					continue;
				}
			}

			// ---------------------------------
			// DownLeft transitions
			// ---------------------------------

			if (Current == EFrogJump::DownLeft)
			{
				if (Next == EFrogJump::DownRight)
				{
					MarkedJumps.Add(EFrogJump::DownLeftToDownRight);
					i += 2;
					continue;
				}

				if (Next == EFrogJump::Left)
				{
					MarkedJumps.Add(EFrogJump::DownLeftToLeft);
					i += 2;
					continue;
				}

				if (Next == EFrogJump::Right)
				{
					MarkedJumps.Add(EFrogJump::DownLeftToRight);
					i += 2;
					continue;
				}
			}
		}

		// ---------------------------------
		// Normal grouping logic
		// ---------------------------------

		EFrogJump CurrentDir = MarkedJumpDirections[i];
		int32 RepeatCount = 1;

		while (i + RepeatCount < MarkedJumpDirections.Num() &&
			MarkedJumpDirections[i + RepeatCount] == CurrentDir)
		{
			RepeatCount++;
		}

		switch (CurrentDir)
		{
		case EFrogJump::Right:
			AddMergedDirection(
				EFrogJump::Right,
				EFrogJump::RightShortOut,
				EFrogJump::RightShortInOut,
				EFrogJump::RightShortIn,
				RepeatCount);
			break;

		case EFrogJump::Left:
			AddMergedDirection(
				EFrogJump::Left,
				EFrogJump::LeftShortOut,
				EFrogJump::LeftShortInOut,
				EFrogJump::LeftShortIn,
				RepeatCount);
			break;

		case EFrogJump::UpRight:
			for (int32 j = 0; j < RepeatCount; j++)
				MarkedJumps.Add(EFrogJump::UpRight);
			break;

		case EFrogJump::UpLeft:
			for (int32 j = 0; j < RepeatCount; j++)
				MarkedJumps.Add(EFrogJump::UpLeft);
			break;

		case EFrogJump::DownRight:
			AddMergedDirection(
				EFrogJump::DownRight,
				EFrogJump::DownRightShortOut,
				EFrogJump::DownRightShortInOut,
				EFrogJump::DownRightShortIn,
				RepeatCount);
			break;

		case EFrogJump::DownLeft:
			AddMergedDirection(
				EFrogJump::DownLeft,
				EFrogJump::DownLeftShortOut,
				EFrogJump::DownLeftShortInOut,
				EFrogJump::DownLeftShortIn,
				RepeatCount);
			break;
		}

		i += RepeatCount;
	}
}
//void AFrog::GenerateMergedJumps() //this WORKS FOR LEFT AND RIGHT
//{
//	MarkedJumps.Empty();
//
//	int32 i = 0;
//	while (i < MarkedJumpDirections.Num())
//	{
//		EFrogJump CurrentDir = MarkedJumpDirections[i];
//		int32 RepeatCount = 1;
//
//		// Count how many times this direction repeats
//		while (i + RepeatCount < MarkedJumpDirections.Num() && MarkedJumpDirections[i + RepeatCount] == CurrentDir)
//		{
//			RepeatCount++;
//		}
//
//		// Procedurally generate merged montages based on RepeatCount
//		if (CurrentDir == EFrogJump::Right)
//		{
//			if (RepeatCount >= 3)
//			{
//				MarkedJumps.Add(EFrogJump::RightShortOut);
//				for (int32 j = 1; j < RepeatCount - 1; j++)
//				{
//					MarkedJumps.Add(EFrogJump::RightShortInOut);
//				}
//				MarkedJumps.Add(EFrogJump::RightShortIn);
//			}
//			else if (RepeatCount == 2)
//			{
//				MarkedJumps.Add(EFrogJump::RightShortOut);
//				MarkedJumps.Add(EFrogJump::RightShortIn);
//			}
//			else
//			{
//				MarkedJumps.Add(EFrogJump::Right);
//			}
//		}
//		else if (CurrentDir == EFrogJump::Left)
//		{
//			if (RepeatCount >= 3)
//			{
//				MarkedJumps.Add(EFrogJump::LeftShortOut);
//				for (int32 j = 1; j < RepeatCount - 1; j++)
//				{
//					MarkedJumps.Add(EFrogJump::LeftShortInOut);
//				}
//				MarkedJumps.Add(EFrogJump::LeftShortIn);
//			}
//			else if (RepeatCount == 2)
//			{
//				MarkedJumps.Add(EFrogJump::LeftShortOut);
//				MarkedJumps.Add(EFrogJump::LeftShortIn);
//			}
//			else
//			{
//				MarkedJumps.Add(EFrogJump::Left);
//			}
//		}
//		else
//		{
//			// Diagonals or other directions: just add the normal jumps
//			for (int32 j = 0; j < RepeatCount; j++)
//			{
//				MarkedJumps.Add(CurrentDir);
//			}
//		}
//
//		i += RepeatCount; // skip over all repeats we just handled
//	}
//}
void AFrog::AnalyzeInBetweenJumps()
{
	//for (uint8 i = 0; i < MarkedJumpDirections.Num(); i++)
	//{
	//	switch (MarkedJumpDirections[i])
	//	{
	//	case EFrogJump::Right:
	//			//check if next Jump is also to the right
	//			if (MarkedJumpDirections[i+1] == EFrogJump::Right)
	//			{
	//				
	//				if (MarkedJumpDirections[i + 2] == EFrogJump::Right)
	//				{
	//					//jumps right three times in a row
	//					MarkedJumps.Add(EFrogJump::RightShortOut);
	//					MarkedJumps.Add(EFrogJump::RightShortInOut);
	//					MarkedJumps.Add(EFrogJump::RightShortIn);
	//				}
	//				else
	//				{
	//					//jumps right two times in a row
	//					MarkedJumps.Add(EFrogJump::RightShortOut);
	//					MarkedJumps.Add(EFrogJump::RightShortIn);
	//				}
	//				

	//				MontageToPlay = JumpRightShortIn;
	//			}
	//			else if (CurrentJumpIndex < MarkedJumpDirections.Num() - 1 && MarkedJumpDirections[CurrentJumpIndex + 1] == EFrogJump::Right)
	//			{
	//				MontageToPlay = JumpRightShortOut;
	//			}
	//			else
	//			{
	//				MontageToPlay = JumpRightMontage;
	//			}
	//		break;
	//	case EFrogJump::Left:
	//		break;
	//	case EFrogJump::UpRight:
	//		break;
	//	case EFrogJump::UpLeft:
	//		break;
	//	case EFrogJump::DownRight:
	//		break;
	//	case EFrogJump::DownLeft:
	//		break;
	//	default:
	//		UE_LOG(LogTemp, Warning, TEXT("WARNING, we have a problem."));
	//		break;
	//	}
	//}
}
//void AFrog::OnJumpMontageEnded(UAnimMontage* Montage, bool bInterrupted)
//{
//	/*if (Montage != JumpMontage)
//		return;*/
//
//	/*UAnimInstance* AnimInstance = FrogMesh->GetAnimInstance();
//	if (AnimInstance)
//	{
//		AnimInstance->OnMontageEnded.RemoveDynamic(this, &AFrog::OnJumpMontageEnded);
//	}*/
//	if (CurrentJumpIndex < MarkedJumpDirections.Num())
//	{
//		CurrentJumpIndex++;
//		SetActorLocation(MarkedSlots[CurrentJumpIndex + 1]);
//		PerformJump();
//	}
//
//	
//	//if (!bInterrupted)
//	//{
//	//	OnJumpFinished(); // execute next jump
//	//}
//}
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
void AFrog::OnAnyMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Warning, TEXT("OnAnyMontageEnded called for  %s, with bInterrupted = %s."), *Montage->GetName(), bInterrupted ? *FString(TEXT("True")) : *FString(TEXT("False")));
	/*FString MontageName = Montage->GetName();
	if (MontageName.Contains(TEXT("Attack")))
	{
	}
	else if (MontageName.Contains(TEXT("StartFlying")))
	{
	}*/
	//for debugging
	//if (CurrentJumpIndex < MarkedSlots.Num())
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Playing Jump %d/%d: %s"),
	//		CurrentJumpIndex,
	//		MarkedSlots.Num(),
	//		*UEnum::GetValueAsString(MarkedSlots[CurrentJumpIndex]));
	//	SetActorLocation(MarkedSlots[CurrentJumpIndex]);
	//}

	SetActorLocation(MarkedSlots[CurrentJumpIndex + 1]);
	CurrentJumpIndex++;
	if (CurrentJumpIndex < MarkedJumpDirections.Num())
	{
		PerformJump();
	}
}
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

