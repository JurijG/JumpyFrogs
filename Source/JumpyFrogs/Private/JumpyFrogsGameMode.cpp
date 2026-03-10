//Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#include "JumpyFrogsGameMode.h"
#include "Pawns/PlayerPawn.h"
#include "Controllers/JumpyFrogsPlayerController.h"
#include "UI/JumpyFrogsHUD.h"
#include "Actors/Frog.h"
#include "Actors/LilyPads.h"
#include "Actors/EmptySlot.h"
#include "Actors/Water.h"


//#include "Actors/EmptySlot.h"
//#include "TimerManager.h"

//#include "Private/Teleporter.h"
//#include "Private/LilyFlowers.h"
//#include "Private/Water.h"
//#include "Private/CameraDirector.h"
//#include "Private/JFPlayerController.h"
//#include "JumpyFrogsGameInstance.h"
//#include "Private/Arrow.h"
//#include "UObject/ConstructorHelpers.h"
//#include "Components/StaticMeshComponent.h"
//#include "Materials/MaterialInstance.h"
#include "Components/AudioComponent.h"
//#include "Kismet/GameplayStatics.h"
//#include "Sound/SoundCue.h"
//#include "Engine/World.h"
//#include "Particles/ParticleSystemComponent.h"
//#include "HAL/PlatformFilemanager.h"
//#include "Serialization/BufferArchive.h"
//#include "Serialization/MemoryWriter.h"
//#include "Serialization/MemoryReader.h"
//#include "Runtime/Engine/Public/EngineUtils.h"
//#include "Private/LensFlare.h"
//#include "Misc/FileHelper.h"
//#include "Animation/AnimMontage.h"
#include "Runtime/Engine/Classes/Components/ApplicationLifecycleComponent.h"
#include "SharedData.h"



AJumpyFrogsGameMode::AJumpyFrogsGameMode()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = AJumpyFrogsPlayerController::StaticClass();
	HUDClass = AJumpyFrogsHUD::StaticClass();

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{

		ConstructorHelpers::FObjectFinder<UDataTable> TelAndBombsDTObj;
		ConstructorHelpers::FObjectFinder<UDataTable> SpawnLevelsDTObj;

		FConstructorStatics()
			: TelAndBombsDTObj(TEXT("/Game/DataTables/FTelAndBombsDataList.FTelAndBombsDataList"))
			, SpawnLevelsDTObj(TEXT("/Game/DataTables/FTelAndBombsDataList.FTelAndBombsDataList"))
		{
		}
	};



	static ConstructorHelpers::FObjectFinder<UDataTable> TelAndBombsDT_BP(TEXT("/Game/DataTables/FTelAndBombsDataList.FTelAndBombsDataList"));
	if (TelAndBombsDT_BP.Object != NULL)
	{
		TelAndBombsDT = TelAndBombsDT_BP.Object;

	}
	static ConstructorHelpers::FObjectFinder<UDataTable> SpawnLevelsDT_BP(TEXT("/Game/DataTables/SpawnLevelsDataTable.SpawnLevelsDataTable"));
	if (SpawnLevelsDT_BP.Object != NULL)
	{
		SpawnLevelsDT = SpawnLevelsDT_BP.Object;
	}


	/*static ConstructorHelpers::FObjectFinder<UDataTable> AiLevelsDT_BP(TEXT("/Game/DataTables/AILevelsDataTable.AILevelsDataTable"));
	if (AiLevelsDT_BP.Object != NULL)
	{
		AiLevelsDT = AiLevelsDT_BP.Object;
	}*/
	
	//ParticleSystem'/Game/MagicFX/Particles/Jurij/P_bloodyFlare.P_bloodyFlare'
	//ParticleSystem'/Game/MagicFX/Particles/Jurij/P_flareImpact_Simple.P_flareImpact_Simple'
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> NB1(TEXT("/Game/MagicFX/Particles/Jurij/P_flareImpact_Simple")); // NB1(TEXT("/Game/MagicFX/Particles/Jurij/P_flareImpactLight"));// PF1(TEXT("/Game/MagicFX/Particles/Jurij/P_flareImpact"));//PF1(TEXT("/Game/MagicFX/Particles/P_flareImpact")); //PF1(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Lightning/P_LineToPoint_Blast_Lightning_00"));
	//if (NB1.Object != NULL)                                      //ParticleSystem'/Game/MagicFX/Particles/P_bloodyFlare.P_bloodyFlare'
	//{
	//	NearbyBomb = NB1.Object;
	//}
	////ParticleSystem'/Game/MagicFX/Particles/Jurij/P_flareImpactHigh.P_flareImpactHigh'
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> PF1(TEXT("/Game/MagicFX/Particles/Jurij/P_flareImpactHigh"));//PF1(TEXT("/Game/MagicFX/Particles/Jurij/P_flareImpact2"));// PF1(TEXT("/Game/MagicFX/Particles/Jurij/P_flareImpact"));//PF1(TEXT("/Game/MagicFX/Particles/P_flareImpact")); //PF1(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Lightning/P_LineToPoint_Blast_Lightning_00"));
	//if (PF1.Object != NULL)                                      //ParticleSystem'/Game/MagicFX/Particles/P_bloodyFlare.P_bloodyFlare'
	//{
	//	ParticleEfekt1 = PF1.Object;
	//}
	////remove frog
	//static ConstructorHelpers::FObjectFinder<UParticleSystem> PF2(TEXT("/Game/MagicFX/Particles/Jurij/P_shieldImpactLight"));//PF2(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/Lightning/P_LineToPoint_Spawn_Proj_Lightning_00"));
	//if (PF2.Object != NULL)
	//{
	//	ParticleEfekt2 = PF2.Object;
	//}


	/*	static ConstructorHelpers::FObjectFinder<UParticleSystem> PF3(TEXT("/Game/MagicFX/Particles/Jurij/P_galeGlow")); //PF3(TEXT("/Game/InfinityBladeEffects/Effects/FX_Mobile/combat/P_Player_Shield_Untyped"));
	if (PF3.Object != NULL)
	{
	ParticleEfekt3 = PF3.Object;
	}*/
	/*static ConstructorHelpers::FObjectFinder<UParticleSystem> PF4(TEXT("/Game/MagicFX/Particles/Jurij/P_goldExp"));
	if (PF4.Object != NULL)
	{
		BombFrogExplosion = PF4.Object;
	}
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PF5(TEXT("/Game/MagicFX/Particles/Jurij/TeleportEffect_Blue"));
	if (PF5.Object != NULL)
	{
		TeleporterActivated = PF5.Object;
	}*/


	Lifecycle = CreateDefaultSubobject<UApplicationLifecycleComponent>(TEXT("Lifecycle"));
	//Lifecycle = PCIP.CreateDefaultSubobject<UApplicationLifecycleComponent>(this, TEXT("Lifecycle"));
	Lifecycle->SetActive(true);
}
void AJumpyFrogsGameMode::BeginPlay()
{
	SpawnFrogsAndProps(5); //GameInstanceReference->LevelNumber


	Lifecycle->ApplicationWillEnterBackgroundDelegate.AddDynamic(this, &AJumpyFrogsGameMode::EnterBackground);
	Lifecycle->ApplicationWillDeactivateDelegate.AddDynamic(this, &AJumpyFrogsGameMode::EnterBackground);
	Lifecycle->ApplicationHasReactivatedDelegate.AddDynamic(this, &AJumpyFrogsGameMode::EnterForeground);
	Lifecycle->ApplicationHasEnteredForegroundDelegate.AddDynamic(this, &AJumpyFrogsGameMode::EnterForeground);
	//LilyPadsObject = GetWorld()->SpawnActor<ALilyPads>(FVector(0.0f, 0.0f, 0.0f), Rot);

	//AddFlowers(FVector2D(0.0f, 0.0f));
	//AddFlowers(FVector2D(1200.0f, -250.0f));
	//AddFlowers(FVector2D(300.0f, 1250.0f));

	GetWorld()->SpawnActor<AWater>(FVector(0.0f, 0.0f, 181.0f), FRotator::ZeroRotator);

}
#pragma region SpawningLevels

void AJumpyFrogsGameMode::AddFrog(FVector2D Pos)
{
	FVector T;
	T.X = Pos.X;
	T.Y = Pos.Y;
	T.Z = 202.0f;//T.Z = 278.0f;
	FrogsArray.Add(GetWorld()->SpawnActor<AFrog>(T, FRotator::ZeroRotator));
}
void AJumpyFrogsGameMode::AddSlot(FVector2D Pos)
{
	FVector T;
	T.X = Pos.X;
	T.Y = Pos.Y;//T.Z = 278.0f-70.f;
	T.Z = 202.0f;
	SlotsArray.Add(GetWorld()->SpawnActor<AEmptySlot>(T, FRotator::ZeroRotator));	
}

bool AJumpyFrogsGameMode::IsMoveValidCheck_Implementation(const FVector Location)
{
	for (AActor* Frog : FrogsArray)
	{
		if (!IsValid(Frog)) continue;
		if (Frog->GetActorLocation() == Location)
		{
			return true;
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *Actor->GetName());
	return false;
}


void AJumpyFrogsGameMode::RemoveFrogAddSlot_Implementation(const FVector StartFrogLoc, const  FVector EndFrogLoc)
{
	const FVector MiddleLoc = (StartFrogLoc + EndFrogLoc) / 2;

	//AActor* SlotRef = nullptr;
	for (AActor* Slot : SlotsArray)
	{
		if (!IsValid(Slot)) continue;
		if (Slot->GetActorLocation() == EndFrogLoc)
		{
			Slot->SetActorLocation(FVector(StartFrogLoc));
			//SlotRef = Slot;
			break;
		}
	}
	/*if (SlotRef != nullptr)
	{
		SlotsArray.RemoveSingle(SlotRef);
	}*/


	//find the frog at InFrogLoc location and remove it, and spawn slot in those locations
	AActor* FrogRef = nullptr;
	for (AActor* Frog : FrogsArray)
	{
		if (!IsValid(Frog)) continue;
		if (Frog->GetActorLocation() == MiddleLoc)
		{
			FrogRef = Frog;
			break;
		}
	}
	if (FrogRef != nullptr)
	{
		IFrogInterface::Execute_JumpAway(FrogRef);
		AddSlot(FVector2d(MiddleLoc.X, MiddleLoc.Y));
		//AddSlot(FVector2d(StartFrogLoc.X, StartFrogLoc.Y));
		FrogsArray.RemoveSingle(FrogRef);
	}
}
void AJumpyFrogsGameMode::FrogJumpingEnded_Implementation()
{
	AJumpyFrogsPlayerController* const MyPlayer = Cast<AJumpyFrogsPlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
	{
		MyPlayer->bMoveInAction = false;
	}
}
void AJumpyFrogsGameMode::RemoveFrogsAndAddSlots_Implementation(FVector SelectedFrogLoc, TArray<FVector>& InMarkedSlots)
{
	//remove slot from the new frog location 
	for (AActor* Slot : SlotsArray)
	{
		if (!IsValid(Slot)) continue;
		if (Slot->GetActorLocation() == InMarkedSlots[InMarkedSlots.Num()-1])
		{
			Slot->Destroy();
			break;
		}
	}
	TArray<FVector> MarkedSlots = InMarkedSlots;
	MarkedSlots.Insert(SelectedFrogLoc, 0);
	//MarkedSlots.Pop();//remove last item from array, because there will be the frog after jump
	TArray<FVector> RemoveFrogLocations;
	//calculate in between positions to remove the frogs and spawn slots:
	for (uint8 i = 0; i < MarkedSlots.Num()-1; i++)
	{
		RemoveFrogLocations.Add((MarkedSlots[i] + MarkedSlots[i+1]) / 2);
	}
	//now find the frogs in those mid locations and eliminate them, and also spawn slots in those locations
	for (const FVector FrogLoc : RemoveFrogLocations)
	{
		for (AActor* Frog : FrogsArray)
		{
			if (!IsValid(Frog)) continue;
			if (Frog->GetActorLocation() == FrogLoc)
			{
				//IFrogInterface::Execute_Remove(Frog);
				AddSlot(FVector2d(FrogLoc.X, FrogLoc.Y));
			}
		}
		
	}
	//Spawn slot where the frog was before jumping:
	AddSlot(FVector2d(SelectedFrogLoc.X, SelectedFrogLoc.Y));
}
void AJumpyFrogsGameMode::SpawnFrogsAndProps(const int32 SelectedLevel)
{
	//DestroyAllActors();

	//SaveProgress = true;
	//TimeBonus = 0;
	////TArray<FVector> BombsArray;
	//IsLevelWon = false;
	//bLevelFailed = false;
	////timeTillGameOver = 2.0f;
	////gameOverTimer = 0.0f;
	//IsGameOver = false;
	//Score = 0;
	////PlayTime = 0;
	////GameTime = 0;
	//CurrentLevel = IfCurLevOutOfBounds(SelectedLevel);//after you make sure nobody can click next level on last level in array, then you can remove this
	//DeselectTheFrog();
	//bIsFrogInAction = false;
	//TheSlotsArray.Reset();  // Empty();
	//FrogsArray.Reset();   //Empty();
	//TheTeleportersArray.Reset();  //Empty();

	TArray<FLevelsDataList*> SpawnLevelsList;
	TArray<FTelAndBombsDataList*> TelAndBombsList;
	SpawnLevelsDT->GetAllRows<FLevelsDataList>("Some Debug Message String if Fails", SpawnLevelsList);
	TelAndBombsDT->GetAllRows<FTelAndBombsDataList>("Some Debug Message String if Fails", TelAndBombsList);

	FrogsRemaining = SpawnLevelsList[CurrentLevel]->FrogsList;
	 
	ALilyPads* LilyPadsObject = GetWorld()->SpawnActor<ALilyPads>(FVector(0.0f, 0.0f, 0.0f), FRotator::ZeroRotator);
	//LilyPadsObject->ReApplyStaticMesh(LilyPadsMeshNumList[CurrentLevel]);
	LilyPadsObject->ReApplyStaticMesh(SpawnLevelsList[CurrentLevel]->LilyPadsMeshNumList);
	//LilyPadsObject->ReApplyStaticMesh(5);
	int32 iMax; int32 deltai = 0;
	if (CurrentLevel > 200)
	{
		//deltai = NumOfBombsList[CurrentLevel - 200];
		deltai = TelAndBombsList[CurrentLevel - 100]->NumOfBombsList;
		iMax = deltai;
		for (int32 i = 0; i < iMax; i++)
		{
			//AddFrog(LevelsList[CurrentLevel][i]);
			AddFrog(SpawnLevelsList[CurrentLevel]->Level[i]);
			//FrogsArray[i]->IsThisBomb = true;
		}
	}
	iMax = FrogsRemaining;
	for (int32 i = 0 + deltai; i < iMax; i++)
	{
		//AddFrog(LevelsList[CurrentLevel][i]);
		AddFrog(SpawnLevelsList[CurrentLevel]->Level[i]);
	}
	//then we spawn empty slots based on remaining number of vectors in the LevelsList 
	//iMax = LevelsList[CurrentLevel].Num();
	iMax = SpawnLevelsList[CurrentLevel]->Level.Num();
	for (int32 i = FrogsRemaining; i < iMax; i++)
	{
		AddSlot(SpawnLevelsList[CurrentLevel]->Level[i]);
	}
	//now we spawn the teleporters if there are any
	//if (CurrentLevel > 100)
	//{
	//	//int32 TelNmb = TeleportersList[CurrentLevel - 100].Num() / 4;
	//	int32 TelNmb = TelAndBombsList[CurrentLevel - 100]->TeleportersList.Num() / 4;
	//	for (int32 i = 0; i < TelNmb; i++)
	//	{
	//		//TheTeleportersArray.Add(GetWorld()->SpawnActor<ATeleporter>(TeleportersList[CurrentLevel - 100][i * 4], Rot));
	//		//TheTeleportersArray[i]->RepositionTeleportersAndApplyMaterial(TelDataList[CurrentLevel - 100][i * 3], TelDataList[CurrentLevel - 100][i * 3 + 1], TeleportersList[CurrentLevel - 100][i * 4 + 1], (int32)TelDataList[CurrentLevel - 100][i * 3 + 2], TeleportersList[CurrentLevel - 100][i * 4 + 2], TeleportersList[CurrentLevel - 100][i * 4 + 3]);
	//		TheTeleportersArray.Add(GetWorld()->SpawnActor<ATeleporter>(TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4], Rot));
	//		TheTeleportersArray[i]->RepositionTeleportersAndApplyMaterial(TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3], TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3 + 1], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 1], (int32)TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3 + 2], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 2], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 3]);
	//	}
	//}
	//SetMaterials();

	/*FTimerHandle stmt;
	GetWorld()->GetTimerManager().SetTimer(stmt, this, &AJumpyFrogsGameModeBase::ReSetBlackMats, 0.2f, false);

	FTimerHandle addArr;
	GetWorld()->GetTimerManager().SetTimer(addArr, this, &AJumpyFrogsGameModeBase::AddArrows, 5.0f, false);*/


	////FrogsRemaining = FrogsList[CurrentLevel];
	//FrogsRemaining = SpawnLevelsList[CurrentLevel]->FrogsList;

	//SetQualityLevelBasedOnLevel();

	//LilyPadsObject = GetWorld()->SpawnActor<ALilyPads>(FVector(0.0f, 0.0f, 0.0f), Rot);
	////LilyPadsObject->ReApplyStaticMesh(LilyPadsMeshNumList[CurrentLevel]);
	//LilyPadsObject->ReApplyStaticMesh(SpawnLevelsList[CurrentLevel]->LilyPadsMeshNumList);
	////LilyPadsObject->ReApplyStaticMesh(5);
	//int32 iMax; int32 deltai = 0;
	//if (CurrentLevel > 200)
	//{
	//	//deltai = NumOfBombsList[CurrentLevel - 200];
	//	deltai = TelAndBombsList[CurrentLevel - 100]->NumOfBombsList;
	//	iMax = deltai;
	//	for (int32 i = 0; i < iMax; i++)
	//	{
	//		//AddFrog(LevelsList[CurrentLevel][i]);
	//		AddFrog(SpawnLevelsList[CurrentLevel]->Level[i]);
	//		FrogsArray[i]->IsThisBomb = true;
	//	}
	//}
	//iMax = FrogsRemaining;
	//for (int32 i = 0 + deltai; i < iMax; i++)
	//{
	//	//AddFrog(LevelsList[CurrentLevel][i]);
	//	AddFrog(SpawnLevelsList[CurrentLevel]->Level[i]);
	//}
	////then we spawn empty slots based on remaining number of vectors in the LevelsList 
	////iMax = LevelsList[CurrentLevel].Num();
	//iMax = SpawnLevelsList[CurrentLevel]->Level.Num();
	//for (int32 i = FrogsRemaining; i < iMax; i++)
	//{
	//	//AddSlot(LevelsList[CurrentLevel][i]);
	//	AddSlot(SpawnLevelsList[CurrentLevel]->Level[i]);
	//}
	////now we spawn the teleporters if there are any
	//if (CurrentLevel > 100)
	//{
	//	//int32 TelNmb = TeleportersList[CurrentLevel - 100].Num() / 4;
	//	int32 TelNmb = TelAndBombsList[CurrentLevel - 100]->TeleportersList.Num() / 4;
	//	for (int32 i = 0; i < TelNmb; i++)
	//	{
	//		//TheTeleportersArray.Add(GetWorld()->SpawnActor<ATeleporter>(TeleportersList[CurrentLevel - 100][i * 4], Rot));
	//		//TheTeleportersArray[i]->RepositionTeleportersAndApplyMaterial(TelDataList[CurrentLevel - 100][i * 3], TelDataList[CurrentLevel - 100][i * 3 + 1], TeleportersList[CurrentLevel - 100][i * 4 + 1], (int32)TelDataList[CurrentLevel - 100][i * 3 + 2], TeleportersList[CurrentLevel - 100][i * 4 + 2], TeleportersList[CurrentLevel - 100][i * 4 + 3]);
	//		TheTeleportersArray.Add(GetWorld()->SpawnActor<ATeleporter>(TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4], Rot));
	//		TheTeleportersArray[i]->RepositionTeleportersAndApplyMaterial(TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3], TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3 + 1], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 1], (int32)TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3 + 2], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 2], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 3]);
	//	}
	//}
	//SetMaterials();

	//FTimerHandle stmt;
	//GetWorld()->GetTimerManager().SetTimer(stmt, this, &AJumpyFrogsGameModeBase::ReSetBlackMats, 0.2f, false);

	//FTimerHandle addArr;
	//GetWorld()->GetTimerManager().SetTimer(addArr, this, &AJumpyFrogsGameModeBase::AddArrows, 5.0f, false);

	//FTimerHandle RcrdEvent3s2;
	//GetWorld()->GetTimerManager().SetTimer(RcrdEvent3s2, this, &AJumpyFrogsGameModeBase::RecordStartGame, 1.0f, false);

	//CamLoc = CamLocList[CurrentLevel];
	//Distance = DistanceList[CurrentLevel];
	//AdjustCamera(CamLoc, Distance);

	//FVector CamLoc = SpawnLevelsList[CurrentLevel]->CamLoc;
	//float Distance = SpawnLevelsList[CurrentLevel]->DistanceList;

	//RandomizeLillyColors(); not needed anymore since we load the map every level
	//AdjustCamera(SpawnLevelsList[CurrentLevel]->CamLoc, SpawnLevelsList[CurrentLevel]->DistanceList);
	//CamLoc = SpawnLevelsList[CurrentLevel]->CamLoc;
	//Distance = SpawnLevelsList[CurrentLevel]->DistanceList;
	//if(!GameInstanceReference->bFirstMapLoad)
	//{
	//AdjustCamera();
	//}
	//GameInstanceReference->bFirstMapLoad = false;
	//AdjustCamera();
}

#pragma endregion


#pragma region DeviceEvents
void AJumpyFrogsGameMode::EnterBackground()
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
	{
		MyPlayer->SetPause(true);
		//SetGamePaused(bool gamePaused)
	}
	AJumpyFrogsHUD* JFHudRef = Cast<AJumpyFrogsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	/*if (JFHudRef->bDrawHudIcons)
	{
		CamDirector->bTimeCounting = false;
		JFHudRef->bDrawHudIcons = false;
		JFHudRef->bDrawPauseMenu = true;
	}*/
}
void AJumpyFrogsGameMode::EnterForeground()
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (MyPlayer != NULL)
	{
		MyPlayer->SetPause(false);
	}
}
#pragma endregion