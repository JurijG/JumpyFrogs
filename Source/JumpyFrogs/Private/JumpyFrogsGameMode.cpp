//Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#include "JumpyFrogsGameMode.h"
#include "Pawns/PlayerPawn.h"
#include "Controllers/JumpyFrogsPlayerController.h"
#include "UI/JumpyFrogsHUD.h"

#include "Actors/Frog.h"
#include "Actors/WizardFrog.h"
#include "Actors/Teleporter.h"
#include "Actors/LilyPads.h"
#include "Actors/EmptySlot.h"
#include "Actors/Water.h"
#include "GameInstances/JumpyFrogsGameInstance.h"

#include "HAL/PlatformFilemanager.h"
#include "Serialization/BufferArchive.h"

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
#include "Kismet/GameplayStatics.h"
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
			, SpawnLevelsDTObj(TEXT("/Game/DataTables/SpawnLevelsDataTable.SpawnLevelsDataTable"))
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
	//SpawnFrogsAndProps(5); //GameInstanceReference->LevelNumber
	
	FString Path = FPaths::ProjectDir();
	Path.Append("\\Saved\\jumpyfrogs.save");

	//FString Path("C:\\JumpyFrogsSaves\\SaveData\\jumpyfrogs.save");
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*Path))
	{
		UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
		LoadGameDataFromFile(Path, GameInstanceReference->bSoundOn, Language, AchievementsArray, UnlockedArray, HighScoreArray);
		//GameInstanceReference->SelLang = NumGemsCollected;
		
		//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::FromInt(NumGemsCollected));
		/*for (int32 i = 0; i < 10; ++i)
		{
		..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, UnlockedArray[i] ? "True" : "False");
		}*/
		bool bDeleteMe = false;
		//..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Load successful !!!!!"));
		//..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::FromInt(NumGemsCollected));
		//ToDelete:
	}
	else
	{
		
		FTimerHandle GameCen32;
		GetWorld()->GetTimerManager().SetTimer(GameCen32, this, &AJumpyFrogsGameMode::FirstSave, 0.3f, false);
	}

	Lifecycle->ApplicationWillEnterBackgroundDelegate.AddDynamic(this, &AJumpyFrogsGameMode::EnterBackground);
	Lifecycle->ApplicationWillDeactivateDelegate.AddDynamic(this, &AJumpyFrogsGameMode::EnterBackground);
	Lifecycle->ApplicationHasReactivatedDelegate.AddDynamic(this, &AJumpyFrogsGameMode::EnterForeground);
	Lifecycle->ApplicationHasEnteredForegroundDelegate.AddDynamic(this, &AJumpyFrogsGameMode::EnterForeground);
	//LilyPadsObject = GetWorld()->SpawnActor<ALilyPads>(FVector(0.0f, 0.0f, 0.0f), Rot);

	//AddFlowers(FVector2D(0.0f, 0.0f));
	//AddFlowers(FVector2D(1200.0f, -250.0f));
	//AddFlowers(FVector2D(300.0f, 1250.0f));
	UJumpyFrogsGameInstance* GI = Cast<UJumpyFrogsGameInstance>(GetWorld()->GetGameInstance());
	//GetWorld()->SpawnActor<AWater>(FVector(0.0f, 0.0f, 181.0f), FRotator::ZeroRotator);
	if (GI && !GI->bFirstMapLoad)	{
		
		CurrentLevel = GI->CurrentLevel;
		SpawnFrogsAndProps();
		/*FTimerHandle chr6;
		GetWorld()->GetTimerManager().SetTimer(chr6, this, &AJumpyFrogsGameMode::SpawnFrogsShort, 0.01f, false);*/
	}
	if (GI->bFirstMapLoad)
	{
		GI->bFirstMapLoad = false;
	}
	/*else if (!GI)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed To Cast/Load GameInstance in BeginPlay"));
	}*/
	
	
	
}
//void AJumpyFrogsGameMode::SpawnFrogsShort()
//{
//	class UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
//	//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, ":SpawnFrogsShort executed!!!");
//	if (Cast<UJumpyFrogsGameInstance>(GetWorld()->GetGameInstance()))
//	{
//		SpawnFrogsAndProps(GameInstanceReference->CurrentLevel);
//		/*FTimerHandle audio6;
//		GetWorld()->GetTimerManager().SetTimer(audio6, this, &AJumpyFrogsGameModeBase::HandleAudio, 0.01f, false);*/
//	}
//	
//}
void AJumpyFrogsGameMode::FirstSave()
{
	
	HighScoreArray.Init(0, 321); // 321 elements, all initialized to 0
	UnlockedArray.Init(false, 321);
	UnlockedArray[0] = false;
	AchievementsArray.Init(false, 16); //TODO: Set to true/false?

	SaveGameDataToFile();

	//PlayClickSound(); TODO: PlaySound

	AJumpyFrogsHUD* JFHudRef = Cast<AJumpyFrogsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	//SpawnFlareBlocker();
	JFHudRef->FirstSave();
	

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
void AJumpyFrogsGameMode::AddWizardFrog(FVector2D Pos)
{
	FVector T;
	T.X = Pos.X;
	T.Y = Pos.Y;
	T.Z = 202.0f;//T.Z = 278.0f;
	//AWizardFrog* Wiz = 
	FrogsArray.Add(GetWorld()->SpawnActor<AWizardFrog>(T, FRotator::ZeroRotator));
}
void AJumpyFrogsGameMode::AddSlot(FVector2D Pos)
{
	FVector T;
	T.X = Pos.X;
	T.Y = Pos.Y;//T.Z = 278.0f-70.f;
	T.Z = 202.0f;
	SlotsArray.Add(GetWorld()->SpawnActor<AEmptySlot>(T, FRotator::ZeroRotator));	
}

int32 AJumpyFrogsGameMode::GetScore_Implementation() const
{
	return Score;
}

TArray<bool> AJumpyFrogsGameMode::GetUnlockedArray_Implementation() const
{
	return UnlockedArray;
}

TArray<int32> AJumpyFrogsGameMode::GetHighScoreArray_Implementation() const
{
	return HighScoreArray;
}

bool AJumpyFrogsGameMode::GetBlockClicks_Implementation() const
{
	return bBlockClicks;
}

bool AJumpyFrogsGameMode::GetAchievementUnlocked_Implementation() const
{
	return bAchievementUnlocked;
}

bool AJumpyFrogsGameMode::GetNewLevUnlocked_Implementation() const
{
	return bNewLevUnlocked;
}

int32 AJumpyFrogsGameMode::GetAchIndex_Implementation() const
{
	return AchIndex;
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
void AJumpyFrogsGameMode::SpawnFrogsAndProps()
{
	//UJumpyFrogsGameInstance* GI = Cast<UJumpyFrogsGameInstance>(GetWorld()->GetGameInstance());
	//GI->bFirstMapLoad = false;
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
			AddWizardFrog(SpawnLevelsList[CurrentLevel]->Level[i]);
			//FrogsArray[i]->bWizardFrog = true;
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
	if (CurrentLevel > 100)
	{
		//int32 TelNmb = TeleportersList[CurrentLevel - 100].Num() / 4;
		int32 TelNmb = TelAndBombsList[CurrentLevel - 100]->TeleportersList.Num() / 4;
		for (int32 i = 0; i < TelNmb; i++)
		{
			//TheTeleportersArray.Add(GetWorld()->SpawnActor<ATeleporter>(TeleportersList[CurrentLevel - 100][i * 4], Rot));
			//TheTeleportersArray[i]->RepositionTeleportersAndApplyMaterial(TelDataList[CurrentLevel - 100][i * 3], TelDataList[CurrentLevel - 100][i * 3 + 1], TeleportersList[CurrentLevel - 100][i * 4 + 1], (int32)TelDataList[CurrentLevel - 100][i * 3 + 2], TeleportersList[CurrentLevel - 100][i * 4 + 2], TeleportersList[CurrentLevel - 100][i * 4 + 3]);
			TheTeleportersArray.Add(GetWorld()->SpawnActor<ATeleporter>(TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4], FRotator::ZeroRotator));
			//TheTeleportersArray[i]->RepositionTeleportersAndApplyMaterial(TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3], TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3 + 1], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 1], (int32)TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3 + 2], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 2], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 3]);
			if (ATeleporter* Tel = Cast<ATeleporter>(TheTeleportersArray[i]))
			{
				Tel->RepositionTeleportersAndApplyMaterial(TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3], TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3 + 1], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 1], (int32)TelAndBombsList[CurrentLevel - 100]->TelDataList[i * 3 + 2], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 2], TelAndBombsList[CurrentLevel - 100]->TeleportersList[i * 4 + 3]);
			}
		}
	}

	AJumpyFrogsHUD* JFHudRef = Cast<AJumpyFrogsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	JFHudRef->StartGame();

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
	//AJumpyFrogsHUD* JFHudRef = Cast<AJumpyFrogsHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
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


void AJumpyFrogsGameMode::ResetGameData()
{
	for (int32 i = 0; i < 321; ++i)
	{
		HighScoreArray[i] = 0; //Set all levels highscore to 0, then we load in if savefile exists
	}

	UnlockedArray[0] = false;
	for (int32 i = 1; i < 321; ++i)
	{
		UnlockedArray[i] = true; //change to true to make save system work properly
	}
	//NumGemsCollected = 43;
	//PlayerLocation = FVector(448.0f, 672.0f, 278.0f);
	//AchievementsArray.Add(FRotator(448.0f, 672.0f, 278.0f));
	//FString Path = FPaths::GameDir();
	SaveGameDataToFile(); //SaveGameDataToFile("C:\\JumpyFrogsSaves\\SaveData\\jumpyfrogs.save");
	AchievementsArray = { false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };
	//TODO: here you should add the order to also delete achievements from the game center and or google play
}


void AJumpyFrogsGameMode::SaveGame()
{
	if (!(HighScoreArray[CurrentLevel - 1] > 0)) { IsNewAch = true; }
	if (UnlockedArray[CurrentLevel] == true) { IsNewTip = true; }

	if (SaveProgress)
	{
		if (UnlockedArray[CurrentLevel])
		{
			UnlockedArray[CurrentLevel] = false;
			if (CurrentLevel == 12)
			{
				UnlockedArray[100] = false;
				bNewModeUnlocked = true;
			}
			else if (CurrentLevel == 112)
			{
				UnlockedArray[200] = false;
				bNewModeUnlocked = true;
			}
			else if (CurrentLevel == 212)
			{
				UnlockedArray[300] = false;
				bNewModeUnlocked = true;
			}
		}
		int32 TempScore = Score + TimeBonus;
		if (HighScoreArray[CurrentLevel - 1] < TempScore)//check if score is bigger than last highscore
		{
			HighScoreArray[CurrentLevel - 1] = TempScore;
			FString Path = FPaths::ProjectDir();
			Path.Append("\\Saved\\jumpyfrogs.save");
			UJumpyFrogsGameInstance* GI = Cast<UJumpyFrogsGameInstance>(GetWorld()->GetGameInstance());
			Language = GI->SelLang;
			SaveGameDataToFile(); //, ToBinary //SaveGameDataToFile("C:\\JumpyFrogsSaves\\SaveData\\jumpyfrogs.save"); //, ToBinary

			//write new highscore to leaderboard TODO:HIghscore leaderboard shit
			/*if (PlayerLocation.Z == 22.2f)
			{
				AJF_HUD* JFHudRef = Cast<AJF_HUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
				JFHudRef->WriteLeaderboard(GetTotalScore());
			}*/
		}

		////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, FString::FromInt(JFHudRef->totalsc));
		//}
	}
}

void AJumpyFrogsGameMode::SaveGameQuick()
{
	SaveGameDataToFile();
}
void AJumpyFrogsGameMode::SaveLanguage()
{
	
	SaveGameDataToFile();
}
//SAVE SYSTEM CODE:::::--------::::::::>>>>ooooooooooo
void AJumpyFrogsGameMode::SaveLoadData(FArchive& Ar, bool& bSoundOn, uint8& SaveDataInt32, 
	TArray<bool>& SaveDataAchievementsArray, TArray<bool>& SaveDataUnlockedArray, TArray<int32>& SaveDataHighScoreArray)
{
	Ar << bSoundOn;
	Ar << SaveDataInt32;
	Ar << SaveDataAchievementsArray;
	Ar << SaveDataUnlockedArray;
	Ar << SaveDataHighScoreArray;
}
bool AJumpyFrogsGameMode::SaveGameDataToFile()
{
	FString FullFilePath = FPaths::ProjectDir();
	FullFilePath.Append("\\Saved\\jumpyfrogs.save");
	
	//UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	//Language = GameInstanceReference->SelLang;

	UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	FBufferArchive ToBinary; //This var must never be global so that it keeps getting deleted once function is complete
	SaveLoadData(ToBinary, GameInstanceReference->bSoundOn, Language, AchievementsArray, UnlockedArray, HighScoreArray);
	//Step 2: Binary to Hard Disk
	if (FFileHelper::SaveArrayToFile(ToBinary, *FullFilePath))
	{
		//..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Save Success!"));
		return true;
	}
	//..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("File Could Not Be Saved!"));
	return false;
}


bool AJumpyFrogsGameMode::LoadGameDataFromFile(
	const FString& FullFilePath,
	bool& bSoundOn,
	uint8& SaveDataInt32,//FVector& SaveDataVector,
	TArray<bool>& SaveDataAchievementsArray,
	TArray<bool>& SaveDataUnlockedArray,
	TArray<int32>& SaveDataHighScoreArray
)
{
	TArray<uint8> TheBinaryArray;
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullFilePath)) // if file exists
	{
		if (!FFileHelper::LoadFileToArray(TheBinaryArray, *FullFilePath))
		{
			//ClientMessage("FFILEHELPER:>> Invalid File");
			//..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("FFILEHELPER:>> Invalid File, Loading Failed, deleting the file now!"));
			FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*FullFilePath);
			return false;
		}
		else
		{
			FMemoryReader FromBinary = FMemoryReader(TheBinaryArray, true); //true, free data after done
			FromBinary.Seek(0);  // dunno what this does exeactly
			UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
			SaveLoadData(FromBinary, GameInstanceReference->bSoundOn, Language, AchievementsArray, UnlockedArray, HighScoreArray);

			//..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Loaded File Size"));
			//..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(TheBinaryArray.Num()));
			return true;
		}
	}
	else //file doesn't exist
	{
		//..[]..//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("There is no Save file in this location!"));
		return false;
	}
}
//void AJumpyFrogsGameMode::LoadNextLevel_Implementation()
//{
//	CurrentLevel++;
//	LoadMap();
//}
void AJumpyFrogsGameMode::LoadLevel_Implementation(int32 LevelNumber)
{
	CurrentLevel = LevelNumber;
	/*UJumpyFrogsGameInstance* GameInstanceReference = Cast<UJumpyFrogsGameInstance>(GetWorld()->GetGameInstance());
	GameInstanceReference->CurrentLevel = LevelNumber;*/
	LoadMap(); 
}
void AJumpyFrogsGameMode::LoadMap()
{
	TArray<FLevelsDataList*> SpawnLevelsList;
	//TArray<FTelAndBombsDataList*> TelAndBombsList;
	SpawnLevelsDT->GetAllRows<FLevelsDataList>("Some Debug Message String if Fails", SpawnLevelsList);
	//TelAndBombsDT->GetAllRows<FTelAndBombsDataList>("Some Debug Message String if Fails", TelAndBombsList);
	if (CurrentLevel == 33) { CurrentLevel = 101; }
	else if (CurrentLevel == 141) { CurrentLevel = 201; }
	else if (CurrentLevel == 229) { CurrentLevel = 301; }
	else if (CurrentLevel == 321) { CurrentLevel = 320; }

	UJumpyFrogsGameInstance* GameInstanceReference = Cast<UJumpyFrogsGameInstance>(GetWorld()->GetGameInstance());
	GameInstanceReference->CurrentLevel = CurrentLevel;
	UGameplayStatics::OpenLevel(this, FName(*(GetWorld()->GetName())), false);

	//class UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	//GameInstanceReference->CamLocc = SpawnLevelsList[CurrentLevel]->CamLoc;
	//GameInstanceReference->Distancee = SpawnLevelsList[CurrentLevel]->DistanceList;
	//CamLoc = GameInstanceReference->CamLocc;
	//Distance = GameInstanceReference->Distancee;
	//bIsCameraHome = false;//dodano da se izognemo animaciji kamere itd
	//if (bIsCameraHome)
	//{
	//	GameInstanceReference->AudioStartTime = 0.0f;
	//	SpawnFrogsAndProps(CurrentLevel);
	//	AdjustCamera();
	//	//PondAudioComponent->FadeOut(2.4f, 0.0f);
	//	PondAudioComponent->FadeOut(1.2f, 0.0f);
	//	//GameInstanceReference->AudioPrevLength = 0.0f;
	//	/*FTimerHandle chrysler;
	//	GetWorld()->GetTimerManager().SetTimer(chrysler, this, &AJumpyFrogsGameModeBase::SaveVarsAndLoadMap, 2.5f, false);*/
	//}
	//else
	//{
	//int32 TrackLen = 53533;
	//int32 RnTimeInt = (int32)((CamDirector->RunTime - 0.01f) * 1000);
	//GameInstanceReference->AudioStartTime += ((float)(RnTimeInt % TrackLen)) / 1000.0f;
	//GameInstanceReference->AudioPrevLength = ((float)(RnTimeInt % TrackLen)) / 1000.0f;
	//SaveVarsAndLoadMap();
	//}

}
//
//void AJumpyFrogsGameMode::SaveVarsAndLoadMap()
//{
//	UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
//	//nt32 sada= 563 % 60;
//	GameInstanceReference->LevelNumber = CurrentLevel;
//	//GameInstanceReference->bIsCamHome = bIsCameraHome;
//	//GameInstanceReference->IsAiActive = IsAiActive;
//	//GameInstanceReference->bFadeIn = bIsCameraHome;
//
//	UGameplayStatics::OpenLevel(this, FName(*(GetWorld()->GetName())), false);
//	//UGameplayStatics::OpenLevel(this, FName(*(GetWorld()->GetName() + "?listen?game=AJumpyFrogsGameMode ")), false);
//}
//
