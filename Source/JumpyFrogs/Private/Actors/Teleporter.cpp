// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Teleporter.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TeleporterComponent.h"
//#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

#include "Interfaces/GameModeInterface.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

//#include "JumpyFrogsGameModeBase.h"

// Sets default values
ATeleporter::ATeleporter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	IsTelDead = false;
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>  TelLilyPadMesh;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh>  TeleporterEndMesh01;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> YellowMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GreenMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> PurpleMaterial;
		ConstructorHelpers::FObjectFinderOptional<UParticleSystem> LilyPadOrange;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraAsset;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraTeleportIn_Obj;
		ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraTeleportOut_Obj;

		FConstructorStatics() //StaticMesh'/Game/EmptySlot/StaticMesh/EmptySlot.EmptySlot'
			:// TelLilyPadMesh(TEXT("/Game/EmptySlot/StaticMesh/EmptySlot")),// //(TEXT("/Game/Teleporter/TeleporterStartMesh")),
			TelLilyPadMesh(TEXT("/Game/Teleporter/StaticMesh/TeleporterStone")),
			TeleporterEndMesh01(TEXT("/Game/Teleporter/StaticMesh/TeleporterStone")),//TeleporterEndMesh01(TEXT("/Game/Teleporter/TeleporterEndMesh")),
			//	BlueMaterial(TEXT("/Game/EmptySlot/Materials/Invisible_Mat")),		//	BlueMaterial(TEXT("/Game/Teleporter/TeleporterOrangeMat")), Material'/Game/EmptySlot/Materials/Invisible_Mat.Invisible_Mat'
			BaseMaterial(TEXT("/Game/Teleporter/Materials/TeleporterStoneBaseMat")),
			BlueMaterial(TEXT("/Game/Teleporter/Materials/TeleporterStoneMat_Blue")),
			YellowMaterial(TEXT("/Game/Teleporter/Materials/TeleporterStoneMat_Yellow")),
			GreenMaterial(TEXT("/Game/Teleporter/Materials/TeleporterStoneMat_Green")),
			PurpleMaterial(TEXT("/Game/Teleporter/Materials/TeleporterStoneMat_Purple")),
			LilyPadOrange(TEXT("/Game/LilyPads/Materials/Lily_Pad_Mat_Inst_Orange")),
			NiagaraAsset(TEXT("/Game/Niagara/NS_FrogHand.NS_FrogHand")),
			NiagaraTeleportIn_Obj(TEXT("/Game/Niagara/NS_FrogHand.NS_FrogHand")),
			NiagaraTeleportOut_Obj(TEXT("/Game/Niagara/NS_FrogHand.NS_FrogHand"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	TeleportMatStoneBase = ConstructorStatics.BaseMaterial.Get();
	TeleportMatBlue = ConstructorStatics.BlueMaterial.Get();
	TeleportMatYellow = ConstructorStatics.YellowMaterial.Get();
	TeleportMatGreen = ConstructorStatics.GreenMaterial.Get();
	TeleportMatPurple = ConstructorStatics.PurpleMaterial.Get();

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("TeleporterDummy"));
	RootComponent = DummyRoot;

	// Create static mesh component
	TeleporterStartMesh = CreateDefaultSubobject<UTeleporterComponent>(TEXT("TeleporterStartMesh"));
	TeleporterStartMesh->SetStaticMesh(ConstructorStatics.TelLilyPadMesh.Get());
	//TeleporterStartMesh->SetRelativeRotation(FRotator(0.0f, -39.0f, 0.0f));
	TeleporterStartMesh->SetRelativeScale3D(FVector(0.9f, 0.9f, 0.9f));
	//TeleporterStartMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f)); //180.0f
	TeleporterStartMesh->SetRelativeLocation(FVector(8.0f, 12.0f, 180.0f)); //180.0f
	TeleporterStartMesh->SetMaterial(0, TeleportMatBlue);
	TeleporterStartMesh->SetupAttachment(DummyRoot);//TeleporterStartMesh->AttachTo(DummyRoot);
	TeleporterStartMesh->bCastDynamicShadow = false;
	TeleporterStartMesh->SetGenerateOverlapEvents(false);
	/*TeleporterStartMesh->OnClicked.AddDynamic(this, &ATeleporter::TeleporterStartClicked);
	TeleporterStartMesh->OnInputTouchBegin.AddDynamic(this, &ATeleporter::OnFingerPressedTeleport);*/
	TeleporterStartMesh->TeleporterType = ETeleporterType::Start;


	TeleporterEndMesh = CreateDefaultSubobject<UTeleporterComponent>(TEXT("TeleporterEndMesh"));
	TeleporterEndMesh->SetStaticMesh(ConstructorStatics.TelLilyPadMesh.Get());
	TeleporterEndMesh->SetRelativeScale3D(FVector(0.9f, -0.9f, 0.9f));
	TeleporterEndMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f)); //180.f
	//TeleporterEndMesh->SetRelativeLocation(FVector(-440.0f, 232.0f, 200.0f));
	//TeleporterEndMesh->SetMaterial(0, ConstructorStatics.YellowMaterial.Get());
	TeleporterEndMesh->SetMaterial(0, TeleportMatBlue);
	TeleporterEndMesh->SetupAttachment(DummyRoot);//TeleporterEndMesh->AttachTo(DummyRoot);
	TeleporterEndMesh->bCastDynamicShadow = false;
	TeleporterEndMesh->SetGenerateOverlapEvents(false);
	/*TeleporterEndMesh->OnClicked.AddDynamic(this, &ATeleporter::TeleporterEndClicked);
	TeleporterEndMesh->OnInputTouchBegin.AddDynamic(this, &ATeleporter::OnFingerPressedEndTeleport);*/
	TeleporterEndMesh->TeleporterType = ETeleporterType::End;
	
	// Create Niagara component
	NiagaraEffectStart = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffectStart"));
	NiagaraEffectStart->SetAsset(ConstructorStatics.NiagaraAsset.Object);
	// Attach to root (or any component you want)
	NiagaraEffectStart->SetupAttachment(TeleporterStartMesh);

	// Optional: auto-activate
	NiagaraEffectStart->bAutoActivate = true;
	

	NiagaraEffectEnd = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffectEnd"));
	NiagaraEffectEnd->SetAsset(ConstructorStatics.NiagaraAsset.Object);
	// Attach to root (or any component you want)
	NiagaraEffectEnd->SetupAttachment(TeleporterEndMesh);

	// Optional: auto-activate
	NiagaraEffectEnd->bAutoActivate = true;
	
	//NiagaraEffect->Activate();
	//NiagaraEffect->Deactivate();
}
//
//void ATeleporter::BeginPlay()
//{
//	Super::BeginPlay();
//	//GameModeReference = (AJumpyFrogsGameModeBase*)GetWorld()->GetAuthGameMode();
//}

void ATeleporter::RepositionTeleportersAndApplyMaterial(float StartRot, float EndRot, FVector TeleportEndLoc, int32 WhichMaterial, FVector EndLocation, FVector StartLocation)
{
	switch (WhichMaterial)
	{
	case 1: TeleporterStartMesh->SetMaterial(0, TeleportMatBlue); TeleporterEndMesh->SetMaterial(0, TeleportMatBlue);  TeleporterStartMesh->SetMaterial(1, TeleportMatBlue); TeleporterEndMesh->SetMaterial(1, TeleportMatBlue); //TeleporterEndEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GlowB, EndLocation, FRotator(0.0f, 0.0f, 90.0f), true); TeleporterEndEmmiter->AttachTo(DummyRoot); break; // TeleporterStartEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleporterStartBlue, StartLocation, FRotator(0.0f, 0.0f, 90.0f), true); 
		NiagaraEffectStart->SetVariableLinearColor(TEXT("User.TelColor"), FLinearColor::Blue);
		NiagaraEffectEnd->SetVariableLinearColor(TEXT("User.TelColor"), FLinearColor::Blue);
		break;
	case 2: TeleporterStartMesh->SetMaterial(0, TeleportMatYellow); TeleporterEndMesh->SetMaterial(0, TeleportMatYellow); TeleporterStartMesh->SetMaterial(1, TeleportMatYellow); TeleporterEndMesh->SetMaterial(1, TeleportMatYellow); //TeleporterEndEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GlowY, EndLocation, FRotator(0.0f, 0.0f, 90.0f), true);  TeleporterEndEmmiter->AttachTo(DummyRoot); break; //TeleporterStartEmmiter->AttachTo(DummyRoot); break; //TeleporterStartEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),TeleporterStartYellow, StartLocation, FRotator(0.0f, 0.0f, 90.0f), true); 
		NiagaraEffectStart->SetVariableLinearColor(TEXT("User.TelColor"), FLinearColor::Yellow);
		NiagaraEffectEnd->SetVariableLinearColor(TEXT("User.TelColor"), FLinearColor::Yellow);
		break;
	case 3:	TeleporterStartMesh->SetMaterial(0, TeleportMatPurple); TeleporterEndMesh->SetMaterial(0, TeleportMatPurple); TeleporterStartMesh->SetMaterial(1, TeleportMatPurple); TeleporterEndMesh->SetMaterial(1, TeleportMatPurple); //TeleporterEndEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GlowR, EndLocation, FRotator(0.0f, 0.0f, 90.0f), true);  TeleporterEndEmmiter->AttachTo(DummyRoot); break;  //TeleporterStartEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleporterStartRed, StartLocation, FRotator(0.0f, 0.0f, 90.0f), true); TeleporterEndEmmiter->AttachTo(DummyRoot); TeleporterStartEmmiter->AttachTo(DummyRoot); break;
		NiagaraEffectStart->SetVariableLinearColor(TEXT("User.TelColor"), FLinearColor(0.25f, 0.f, 0.31f, 1.f));
		NiagaraEffectEnd->SetVariableLinearColor(TEXT("User.TelColor"), FLinearColor(0.25f, 0.f, 0.31f, 1.f));
		break;
	case 4: TeleporterStartMesh->SetMaterial(0, TeleportMatGreen); TeleporterEndMesh->SetMaterial(0, TeleportMatGreen); TeleporterStartMesh->SetMaterial(1, TeleportMatGreen); TeleporterEndMesh->SetMaterial(1, TeleportMatGreen); //TeleporterEndEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GlowG, EndLocation, FRotator(0.0f, 0.0f, 90.0f), true); TeleporterEndEmmiter->AttachTo(DummyRoot);  break; //TeleporterStartEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleporterStartGreen, StartLocation, FRotator(0.0f, 0.0f, 90.0f), true);  TeleporterEndEmmiter->AttachTo(DummyRoot); TeleporterStartEmmiter->AttachTo(DummyRoot); break;
		NiagaraEffectStart->SetVariableLinearColor(TEXT("User.TelColor"), FLinearColor::Green);
		NiagaraEffectEnd->SetVariableLinearColor(TEXT("User.TelColor"), FLinearColor::Green);
		break;
	default:;//TeleporterStartMesh->SetMaterial(0, TeleportMatBlue); TeleporterEndMesh->SetMaterial(0, TeleportMatBlue);
	}

	//TeleporterStartMesh->SetRelativeLocation(StartLocation);

	//TeleporterStartMesh->SetRelativeRotation(FRotator(0.0f, StartRot, 0.0f));
	TeleporterStartMesh->SetRelativeRotation(FRotator(0.0f, -94.0f, 0.0f));

	FVector EndLoc = TeleportEndLoc;
	EndLoc.X += 8.0f;
	EndLoc.Y += 12.0f;
	EndLoc.Z = 180.f;
	TeleporterEndMesh->SetRelativeLocation(EndLoc);
	//TeleporterEndMesh->SetRelativeRotation(FRotator(0.0f, EndRot, 0.0f));
	TeleporterEndMesh->SetRelativeRotation(FRotator(0.0f, 100.0f, 0.0f));

	/*
	switch (WhichMaterial)
	{
	case 1: TeleporterStartMesh->SetMaterial(0, TeleportMatGreen); TeleporterEndMesh->SetMaterial(0, TeleportMatGreen); TeleporterStartEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleporterStartBlue, StartLocation, FRotator(0.0f, 0.0f, 90.0f), true); TeleporterEndEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GlowB, EndLocation, FRotator(0.0f, 0.0f, 90.0f), true);
	TeleporterEndEmmiter->AttachTo(DummyRoot); TeleporterStartEmmiter->AttachTo(DummyRoot);  break;
	case 2: TeleporterStartMesh->SetMaterial(0, TeleportMatYellow); TeleporterEndMesh->SetMaterial(0, TeleportMatYellow); TeleporterStartEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleporterStartYellow, StartLocation, FRotator(0.0f, 0.0f, 90.0f), true); TeleporterEndEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GlowY, EndLocation, FRotator(0.0f, 0.0f, 90.0f), true); TeleporterEndEmmiter->AttachTo(DummyRoot); TeleporterStartEmmiter->AttachTo(DummyRoot); break;
	case 3: TeleporterStartMesh->SetMaterial(0, TeleportMatPurple); TeleporterEndMesh->SetMaterial(0, TeleportMatPurple); TeleporterStartEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleporterStartRed, StartLocation, FRotator(0.0f, 0.0f, 90.0f), true); TeleporterEndEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GlowR, EndLocation, FRotator(0.0f, 0.0f, 90.0f), true); TeleporterEndEmmiter->AttachTo(DummyRoot); TeleporterStartEmmiter->AttachTo(DummyRoot); break;
	case 4: TeleporterStartMesh->SetMaterial(0, TeleportMatBlue); TeleporterEndMesh->SetMaterial(0, TeleportMatBlue);  TeleporterStartEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleporterStartGreen, StartLocation, FRotator(0.0f, 0.0f, 90.0f), true); TeleporterEndEmmiter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GlowG, EndLocation, FRotator(0.0f, 0.0f, 90.0f), true); TeleporterEndEmmiter->AttachTo(DummyRoot); TeleporterStartEmmiter->AttachTo(DummyRoot); break;

	default:;//TeleporterStartMesh->SetMaterial(0, TeleportMatBlue); TeleporterEndMesh->SetMaterial(0, TeleportMatBlue);
	}*/
	//TeleporterStartMesh->
	//	TeleporterEndMesh->SetRelativeLocation(TeleportEndLoc);
	EndPosition = EndLocation;
	TelEndLoc = TeleportEndLoc;
	TelStartLoc = StartLocation;
	TelStartLoc.Z = 278.0f;
	//TeleporterStartMesh->SetStaticMesh(NewMesh);


	//TeleporterStartMesh->SetMaterial WhichMaterial
}

bool ATeleporter::AlreadyUsed_Implementation() const
{
	return bUsed;
}

void ATeleporter::Deactivate_Implementation()
{
	bUsed = true;
	//TeleporterStartMesh->SetCollisionProfileName(TEXT("NoCollision"));
	TeleporterStartMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//TeleporterStartMesh->SetCollisionProfile(ECollisionEnabled::NoCollision);
	//TeleporterEndMesh->SetCollisionProfileName(TEXT("NoCollision"));
	TeleporterEndMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (NiagaraEffectStart)
	{
		NiagaraEffectStart->Deactivate();
		NiagaraEffectStart->DestroyComponent();
	}
	TeleporterStartMesh->SetMaterial(0, TeleportMatStoneBase);
	TeleporterStartMesh->SetMaterial(1, TeleportMatStoneBase);
	if (NiagaraEffectEnd)
	{
		NiagaraEffectEnd->Deactivate();
		NiagaraEffectEnd->DestroyComponent();

	}

	TeleporterEndMesh->SetMaterial(0, TeleportMatStoneBase);
	TeleporterEndMesh->SetMaterial(1, TeleportMatStoneBase);


	//MeshComponent->MarkRenderStateDirty();

	
	


	//TeleporterStartMesh->SetMaterial(0, TeleportMatBlue); TeleporterEndMesh->SetMaterial(0, TeleportMatBlue);
	//TeleporterStartMesh->SetMaterial(1, TeleportMatBlue); TeleporterEndMesh->SetMaterial(1, TeleportMatBlue);

	//TeleporterStartMesh->SetMaterial(0, TeleportMatBlue); TeleporterEndMesh->SetMaterial(1, TeleportMatStoneBase);
	//TeleporterEndMesh->SetMaterial(0, TeleportMatBlue); TeleporterEndMesh->SetMaterial(1, TeleportMatStoneBase);
}
bool ATeleporter::IsThisStart_Implementation(UObject* InComponent) const
{
	if(UTeleporterComponent* InTeleporterComponent = Cast<UTeleporterComponent>(InComponent))
	{
		if(InTeleporterComponent->TeleporterType == ETeleporterType::Start)
		{
			return true;
		}
	}
	return false;
}
FVector ATeleporter::GetStartLocation_Implementation() const
{
	FVector ReturnStartLoc = TelStartLoc;
	ReturnStartLoc.Z = 202.f;
	return ReturnStartLoc;
	/*FVector ReturnStartLoc = TeleporterStartMesh->GetComponentLocation();
	ReturnStartLoc.X -= 8.f;
	ReturnStartLoc.Y -= 12.f;
	ReturnStartLoc.Z = 202.f;
	return ReturnStartLoc;*/
}
FVector ATeleporter::GetEndLocation_Implementation() const
{
	FVector ReturnLoc = EndPosition;
	ReturnLoc.Z = 202.f;
	return ReturnLoc;
	//FVector ReturnEndLoc = TeleporterEndMesh->GetComponentLocation();
	///*ReturnEndLoc.X -= 8.f;
	//ReturnEndLoc.Y -= 12.f;*/
	//ReturnEndLoc.Z = 202.f;
	//return ReturnEndLoc;
}
//
//void ATeleporter::OnFingerPressedTeleport(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
//{
//	TeleporterStartTouchedOrClicked(); //TeleporterStartClicked(TouchedComponent, FingerIndex);
//}
//
//void ATeleporter::OnFingerPressedEndTeleport(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
//{
//	TeleporterEndTouchedOrClicked(); //TeleporterEndClicked(TouchedComponent, FingerIndex);
//}
//void ATeleporter::TeleporterStartClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
//{
//	TeleporterStartTouchedOrClicked();
//}
//
//void ATeleporter::TeleporterEndClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
//{
//	TeleporterEndTouchedOrClicked();
//}

//void ATeleporter::TeleporterStartTouchedOrClicked()
//{
	//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("TeleporterStartClicked! "));
	/*	FVector TempV = this->GetActorLocation();
	float x = TempV.X;
	float y = TempV.Y;
	float z = TempV.Z;*/
	//..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Teleporter clicked in C++"));
	//if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
	//{
	//	if (GM->Implements<UGameModeInterface>())
	//	{
	//		//GameModeReference->PlayerLocation.Y = 777.7f; //TODO: check this 777.7 location shit when saving, its used to chech in app purchases 
	//		if (IGameModeInterface::Execute_(GM))
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("SavePurchase GAME DATA SAVED, all is ok."));
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("SavePurchase ERROR: GAME DATA WAS NOT SAVED."));
	//		}
	//	}
	//}
	//
	//GetWorld()->GetAuthGameMode();
	//if (GameModeReference->bIsFrogSelected) //first we check if we have any of the frogs selected
	//{
	//	if (!GameModeReference->bIsFrogInAction) //check if we have any of the frogs in action - jumping
	//	{
	//		//	if (GameModeReference->TeleportCheck())
	//		//{
	//		GameModeReference->bIsFrogInAction = true;
	//		//SlotLocation = this->GetActorLocation();
	//		GameModeReference->ClickedTeleporter = this; //send this clicked slot to the GameMode variable
	//		FVector TeleporterLoc = this->GetActorLocation();
	//		//GameModeReference->CheckIfMoveIsValidAndReturnAnimationToPlay(TeleporterLoc, true);
	//		GameModeReference->TeleportCheck(TeleporterLoc);
	//		//}
	//	}
	//}
//}


//void ATeleporter::TeleporterEndTouchedOrClicked()
//{
	//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("TeleporterEndClicked TeleporterEndClicked! "));
	/*FVector TempV = this->GetActorLocation(); //EndPosition
	float x = TempV.X;
	float y = TempV.Y;
	float z = TempV.Z;
	//..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT("Teleporter clicked in C++"));*/
	//class AJumpyFrogsGameModeBase* GameModeReference = (AJumpyFrogsGameModeBase*)GetWorld()->GetAuthGameMode();
	//if (GameModeReference->bIsFrogSelected) //first we check if we have any of the frogs selected
	//{
	//	if (!GameModeReference->bIsFrogInAction) //check if we have any of the frogs in action - jumping
	//	{
	//		//	if (GameModeReference->TeleportCheck())
	//		//{
	//		GameModeReference->bIsFrogInAction = true;
	//		GameModeReference->IsThisStartTel = false;
	//		//SlotLocation = this->GetActorLocation();
	//		GameModeReference->ClickedTeleporter = this; //send this clicked slot to the GameMode variable
	//		//FVector TeleporterLoc = this->GetActorLocation();
	//		//GameModeReference->CheckIfMoveIsValidAndReturnAnimationToPlay(TeleporterLoc, true);
	//		GameModeReference->TeleportCheck(EndPosition);
	//		//}
	//	}
	//}
//}

// Called when the game starts or when spawned
/*
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/


