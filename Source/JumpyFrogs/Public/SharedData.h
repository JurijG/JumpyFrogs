// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SharedData.generated.h"

/**
 * 
 */

class JUMPYFROGS_API SharedData
{
public:
	SharedData(); // Constructor
	~SharedData(); // Destructor
};

USTRUCT()
struct FLevelsDataList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FLevelsDataList()
		: FrogsList(0)
		, LilyPadsMeshNumList(0)
		, DistanceList(2048.0f)
		, CamLoc(FVector(0.0f, 0.0f, 0.0f))
		, Level({ FVector2D(0.0f,0.0f) })
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	int32 FrogsList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	int32 LilyPadsMeshNumList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	float DistanceList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	FVector CamLoc;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	TArray<FVector2D> Level;
};

USTRUCT()
struct FTelAndBombsDataList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FTelAndBombsDataList()
		: NumOfBombsList(0)
		, TelDataList({ 0.0f })
		, TeleportersList({ FVector(0.0f,0.0f,0.0f) })
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	int32 NumOfBombsList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	TArray<float> TelDataList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	TArray<FVector> TeleportersList;
};

USTRUCT()
struct FLibraryData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FLibraryData()
		: English("")
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	FString English;

};

USTRUCT()
struct FScreenTextData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FScreenTextData()
		: LevelStr("")
		, FailedStr("")
		, CompleteStr("")
		, UnlockedStr("")
		, LevScoreStr("")
		, TimeBonStr("")
		, TotScoreStr("")
		, RatingStr("")
		, AchUnlockStr("")
		, TipUnlockStr("")
		, ResetStr("")
		, SureStr("")
		, BuyStr("")
		, Buy2Str("")
		, Buy3Str("")
		, BuyConfirm("")
		, BuyConfirm2("")
		, BuyConfirm3("")
		, RestorePurch("")
		, RestorePurch2("")
		, RestorePurch3("")
		, Price("")
		, Thanks("")
		, Failed("")
		, Failed2("")
		, Failed3("")
		, Restored("")
		, Wait("")
		, Askios("")
		, AskAndroid("")
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString LevelStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString FailedStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString CompleteStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString UnlockedStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString LevScoreStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString TimeBonStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString TotScoreStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString RatingStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString AchUnlockStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString TipUnlockStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString ResetStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString SureStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString BuyStr;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString Buy2Str;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString Buy3Str;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString BuyConfirm;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString BuyConfirm2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString BuyConfirm3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString RestorePurch;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString RestorePurch2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString RestorePurch3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString Price;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString Thanks;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString Failed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString Failed2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString Failed3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString Restored;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString Wait;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString Askios;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "screenTexts")
	FString AskAndroid;
};

USTRUCT()
struct FRatingLimitsDT : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FRatingLimitsDT()
		: TwoStars(0)
		, ThreeStars(0)
		, TimeLimit(0.0f)
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stars Score Limits")
	int32 TwoStars;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stars Score Limits")
	int32 ThreeStars;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Stars Score Limits")
	float TimeLimit;
};

USTRUCT()
struct FAchText : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FAchText()
		: First("")
		, Second("")
		, Third("")
		, Fourth("")
		, Fifth("")
		, Sixth("")
		, Seven("")
		, Eight("")
		, Nine("")
		, Ten("")
		, Eleven("")
		, Twelwe("")
		, Thirteen("")
		, Fourteen("")
		, Fifteen("")
		, Sixteen("")
	{
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString First;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Second;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Third;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Fourth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Fifth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Sixth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Seven;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Eight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Nine;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Ten;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Eleven;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Twelwe;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Thirteen;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Fourteen;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Fifteen;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AchievementsTexts")
	FString Sixteen;

};

