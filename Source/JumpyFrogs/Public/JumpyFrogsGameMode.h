// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
//#include "Engine/DataTable.h"
#include "Interfaces/GameModeInterface.h"
#include "JumpyFrogsGameMode.generated.h"

/**
 * 
 */


//class UAnimMontage;
class ACameraDirector;
class AFrog;
class AEmptySlot;
//class FVector2D;

UCLASS()
class JUMPYFROGS_API AJumpyFrogsGameMode : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()

public:
	AJumpyFrogsGameMode();

	
	
protected:
	 
	bool bNewLevUnlocked; //TODO: maybe move this to HUD?
	bool bBlockClicks;    //TODO: maybe move this to HUD?
	bool bAchievementUnlocked;    //TODO: maybe move this to HUD?
	int32 AchIndex;    //TODO: maybe move this to HUD?
	
	FVector PlayerLocation = FVector::ZeroVector;

	bool IsNewAch = false;
	bool IsNewTip = false;
	bool SaveProgress = false;
	bool bNewModeUnlocked = false;

#pragma region DrawHUD
	int32 Score;
	int32 HighScore;
	int32 MaxScoreTime;
	TArray <int32> HighScoreArray;
	TArray <float> TimeLimitsArray;
	int32 TimeBonus;

#pragma endregion

	int32 CurrentLevel = 30; //  100 -> TESTLEVEL;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void FirstSave();
	int32 FrogsRemaining = 0;
	TArray <AActor*> FrogsArray;
	TArray <AActor*> SlotsArray;
	//TArray <AEmptySlot*> TheSlotsArray;

#pragma region DataTableVars
	//UDataTable* AiLevelsDT;
	UDataTable* TelAndBombsDT;
	UDataTable* SpawnLevelsDT;

#pragma endregion

#pragma region SpawningLevels
	
	void AddFrog(FVector2D Pos);

	void AddSlot(FVector2D Pos);

	int32 GetScore_Implementation() const override;
	int32 GetPlayTime_Implementation() const override;
	int32 GetTimeBonus_Implementation() const override;
	TArray<bool> GetUnlockedArray_Implementation() const override;
	TArray<int32> GetHighScoreArray_Implementation() const override;

	bool GetBlockClicks_Implementation() const override;
	bool GetAchievementUnlocked_Implementation() const override;
	bool GetNewLevUnlocked_Implementation() const override;
	int32 GetAchIndex_Implementation() const override;

	bool IsMoveValidCheck_Implementation(const FVector Location);
	void RemoveFrogAddSlot_Implementation(const FVector NewFrogLoc, const  FVector MiddleLoc);
	void FrogJumpingEnded_Implementation();
	void LoadLevel_Implementation(int32 LevelNumber);


	//void LoadNextLevel_Implementation();

	void RemoveFrogsAndAddSlots_Implementation(FVector SelectedFrogLoc, TArray<FVector>& InMarkedSlots);
	void SpawnFrogsAndProps(const int32 SelectedLevel);


#pragma endregion

#pragma region GameData

	TArray<bool> AchievementsArray;
	TArray <bool> UnlockedArray;

	uint8 Language; //TODO: rename 	int32 NumGemsCollected to something meaningfull..renamed to Language

	void ResetGameData();
	void LoadMap();

	//void SaveVarsAndLoadMap();

	void SaveLoadData(FArchive& Ar, bool& bSoundOn, uint8& SaveDataInt32, TArray<bool>& SaveDataAchievementsArray, TArray<bool>& SaveDataUnlockedArray, TArray<int32>& SaveDataHighScoreArray);

	bool SaveGameDataToFile();//const FString& FullFilePath); //, FBufferArchive& ToBinary);

	bool LoadGameDataFromFile(const FString& FullFilePath, bool& bSoundOn, uint8& SaveDataInt32, TArray<bool>& SaveDataAchievementsArray, TArray<bool>& SaveDataUnlockedArray, TArray<int32>& SaveDataHighScoreArray);


	void SaveGame();
	void SaveGameQuick();
	void SaveLanguage();
	void ChkAchGlobal();


#pragma endregion


public:
#pragma region Camera

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	ACameraDirector* CamDirector;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = JumpyFrogs)
	bool bIsCameraHome;
	FVector CamLoc;
	float  Distance;

#pragma endregion

#pragma region DeviceEvents
	UPROPERTY()
	class UApplicationLifecycleComponent* Lifecycle;
	UFUNCTION(Category = "Jumpy Frogs")
	void EnterBackground();
	UFUNCTION(Category = "Jumpy Frogs")
	void EnterForeground();
#pragma endregion




};

