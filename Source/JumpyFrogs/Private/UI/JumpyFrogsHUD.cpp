// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JumpyFrogsHUD.h"
#include "Engine/Canvas.h"

#include "Interfaces/GameModeInterface.h"
#include "GameInstances/JumpyFrogsGameInstance.h"

#include "SharedData.h"

#include "Blueprint/UserWidget.h"

//#include "UI/FactsWidget.h"
#include "UI/SFrogFacts.h"
#include "Engine/Engine.h"

//#include "../../../../../../../Epic Games/UE_5.3/Engine/Plugins/Editor/ObjectMixer/ObjectMixer/Source/ObjectMixer/Public/Views/List/ObjectMixerEditorList.h"
//#include "Algo/RandomShuffle.h"

//#include "TimerManager.h"
//#include "Sound/SoundCue.h"
//#include "IImageWrapper.h"
//#include "IImageWrapperModule.h"
//#include "Engine/World.h"
//#include "JumpyFrogsGameModeBase.h"
//#include "JumpyFrogsGameInstance.h"
//#include "Private/CameraDirector.h"

//#include "UObject/ConstructorHelpers.h"
//#include "HAL/PlatformFilemanager.h"
//#include "Kismet/GameplayStatics.h"
//#include "Misc/LocalTimestampDirectoryVisitor.h"


AJumpyFrogsHUD::AJumpyFrogsHUD()
{
	HS2StarsLimitArray = { 200 };
	HS3StarsLimitArray = { 600 };

	Buttons = {
		FVector2D(0.f, 0.f),
		FVector2D(0.f, 0.25f),
		FVector2D(0.f, 0.5f),
		FVector2D(0.f, 0.75f),
		FVector2D(0.25f, 0.f),
		FVector2D(0.25f, 0.25f),
		FVector2D(0.25f, 0.5f),
		FVector2D(0.25f, 0.75f),
		FVector2D(0.5f, 0.f),
		FVector2D(0.5f, 0.25f),
		FVector2D(0.5f, 0.5f),
		FVector2D(0.5f, 0.75f),
		FVector2D(0.75f, 0.f),
		FVector2D(0.75f, 0.25f),
		FVector2D(0.75f, 0.5f),
		FVector2D(0.75f, 0.75f),
	};
	RandomizeButtonColors();

	// --- Achievements ---
	AchievementsList = {
		TEXT("Wet Feet"),
		TEXT("Quick Learner"),
		TEXT("Puzzle Student"),
		TEXT("Brainiac"),
		TEXT("Puzzle Expert"),
		TEXT("Magic Pioneer"),
		TEXT("Scholar of Magic"),
		TEXT("Master of Magic"),
		TEXT("Sorcerer's Apprentice"),
		TEXT("Scholar of Sorcery"),
		TEXT("Master Sorcerer"),
		TEXT("Wizard's Apprentice"),
		TEXT("Master Wizard"),
		TEXT("Brain Evolver"),
		TEXT("Strategist"),
		TEXT("Mastermind")
	};

	AchievementsListiOS = {
		TEXT("Wet_Feet"),
		TEXT("Quick_Learner"),
		TEXT("Puzzle_Student"),
		TEXT("Brainiac_"),
		TEXT("com.jurijgantar.jumpyfrogs.achievement_00"),
		TEXT("Magic_Pioneer"),
		TEXT("Scholar_of_Magic"),
		TEXT("Master_of_Magic"),
		TEXT("Sorcerers_Apprentice"),
		TEXT("Scholar_of_Sorcery"),
		TEXT("Master_Sorcerer"),
		TEXT("Wizards_Apprentice"),
		TEXT("com.jurijgantar.jumpyfrogs.achievement_01"),
		TEXT("com.jurijgantar.jumpyfrogs.achievement_02"),
		TEXT("Strategist"),
		TEXT("Mastermind")
	};
	//Buttons.Init(FVector2D::ZeroVector, 16);

	struct FConstructorStatics
	{
		// --- DataTables ---
		ConstructorHelpers::FObjectFinder<UDataTable> RatingStarsDT_Obj;
		ConstructorHelpers::FObjectFinder<UDataTable> LibDataTable_Obj;
		ConstructorHelpers::FObjectFinder<UDataTable> LibDataTableSlovenian_Obj;
		ConstructorHelpers::FObjectFinder<UDataTable> LibDataTableChinese_Obj;
		ConstructorHelpers::FObjectFinder<UDataTable> LibDataTableTrChinese_Obj;
		ConstructorHelpers::FObjectFinder<UDataTable> ScreenTextDataTable_Obj;
		ConstructorHelpers::FObjectFinder<UDataTable> AchDT_Obj;

		// --- Fonts ---
		ConstructorHelpers::FObjectFinder<UFont> JFont_Obj;
		ConstructorHelpers::FObjectFinder<UFont> ChineseFont_Obj;

		// --- Textures ---
		ConstructorHelpers::FObjectFinder<UTexture2D> Achievements_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> Stars_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> ScreenShot_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> ChinaLangSel_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> CreditsText_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> HUDbuttons1_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> HUDbuttons1b_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> HUDbuttons2_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> HUDbuttonsBuy_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> Arrows_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> GreenLayer_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> WideButton_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> LevelSelectFrontMenu_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> LockTexture_256_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> PlayLevelMenu_1_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> PlayLevelMenu_2_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> PlayLevelMenu_3_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> PlayLevelMenu_4_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> Flags_Obj;
		ConstructorHelpers::FObjectFinder<UTexture2D> ButtonColors_Obj;
		//ConstructorHelpers::FObjectFinder<UUserWidget> UserWidgetInstance_Obj;

		// --- Sound ---
		//ConstructorHelpers::FObjectFinder<USoundCue> CountdownSound;

		FConstructorStatics()
			: RatingStarsDT_Obj(TEXT("/Game/DataTables/RatingStarsDT"))
			, LibDataTable_Obj(TEXT("/Game/DataTables/LibraryDataTable"))
			, LibDataTableSlovenian_Obj(TEXT("/Game/DataTables/SlovenianLibDT"))
			, LibDataTableChinese_Obj(TEXT("/Game/DataTables/Chinese_LibDT"))
			, LibDataTableTrChinese_Obj(TEXT("/Game/DataTables/TraditionalChinese_LibDT"))
			, ScreenTextDataTable_Obj(TEXT("/Game/DataTables/ScreenTextDataTable"))
			, AchDT_Obj(TEXT("/Game/DataTables/AchDataTable"))

			, JFont_Obj(TEXT("/Game/UI/JFont_Font"))
			, ChineseFont_Obj(TEXT("/Game/UI/DroidSansFallback_Font"))

			, Achievements_Obj(TEXT("/Game/UI/Textures/Achievements.Achievements"))
			, Stars_Obj(TEXT("/Game/UI/Textures/Stars.Stars"))
			, ScreenShot_Obj(TEXT("/Game/UI/test.test"))
			, ChinaLangSel_Obj(TEXT("/Game/UI/Textures/ChineseLangSel.ChineseLangSel"))
			, CreditsText_Obj(TEXT("/Game/UI/Textures/CreditsText.CreditsText"))
			, HUDbuttons1_Obj(TEXT("/Game/UI/Textures/Buttons1.Buttons1"))
			
			, HUDbuttons1b_Obj(TEXT("/Game/UI/Textures/Buttons1b.Buttons1b"))
			, HUDbuttons2_Obj(TEXT("/Game/UI/Textures/Buttons2.Buttons2"))
			, HUDbuttonsBuy_Obj(TEXT("/Game/UI/Textures/ButtonsBuy.ButtonsBuy"))
			, Arrows_Obj(TEXT("/Game/UI/Textures/Arrows.Arrows"))
			, GreenLayer_Obj(TEXT("/Game/UI/Textures/GreenLayer.GreenLayer"))
			, WideButton_Obj(TEXT("/Game/UI/Textures/NewWideButton"))
			, LevelSelectFrontMenu_Obj(TEXT("/Game/UI/Textures/LevelSelectFrontMenu.LevelSelectFrontMenu"))
			, LockTexture_256_Obj(TEXT("/Game/UI/Textures/LockTexture_256.LockTexture_256"))
			, PlayLevelMenu_1_Obj(TEXT("/Game/UI/Textures/PlayLevelMenu_1.PlayLevelMenu_1"))
			, PlayLevelMenu_2_Obj(TEXT("/Game/UI/Textures/PlayLevelMenu_2.PlayLevelMenu_2"))
			, PlayLevelMenu_3_Obj(TEXT("/Game/UI/Textures/PlayLevelMenu_3.PlayLevelMenu_3"))
			, PlayLevelMenu_4_Obj(TEXT("/Game/UI/Textures/PlayLevelMenu_4.PlayLevelMenu_4"))
			, Flags_Obj(TEXT("/Game/UI/Textures/Flags"))
			, ButtonColors_Obj(TEXT("/Game/UI/Textures/ButtonColors.ButtonColors"))
			//, UserWidgetInstance_Obj(TEXT("/Game/UserWidgetTest.UserWidgetTest"))
			/// Script / UMGEditor.WidgetBlueprint'/Game/UserWidgetTest.UserWidgetTest'
			//, CountdownSound(TEXT("/Game/Audio/UI/Countdown_Cue.Countdown_Cue"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;

	// Assign (no null checks needed if you're confident paths are valid)
	RatingStarsDT = ConstructorStatics.RatingStarsDT_Obj.Object;
	LibDataTable = ConstructorStatics.LibDataTable_Obj.Object;
	LibDataTableSlovenian = ConstructorStatics.LibDataTableSlovenian_Obj.Object;
	LibDataTableChinese = ConstructorStatics.LibDataTableChinese_Obj.Object;
	LibDataTableTrChinese = ConstructorStatics.LibDataTableTrChinese_Obj.Object;
	ScreenTextDataTable = ConstructorStatics.ScreenTextDataTable_Obj.Object;
	AchDT = ConstructorStatics.AchDT_Obj.Object;

	JFont = ConstructorStatics.JFont_Obj.Object;
	ChineseFont = ConstructorStatics.ChineseFont_Obj.Object;

	Achievements = ConstructorStatics.Achievements_Obj.Object;
	Stars = ConstructorStatics.Stars_Obj.Object;
	ScreenShot = ConstructorStatics.ScreenShot_Obj.Object;
	ChinaLangSel = ConstructorStatics.ChinaLangSel_Obj.Object;
	CreditsText = ConstructorStatics.CreditsText_Obj.Object;
	Buttons1 = ConstructorStatics.HUDbuttons1_Obj.Object;
	HUDbuttons1b = ConstructorStatics.HUDbuttons1b_Obj.Object;
	Buttons2 = ConstructorStatics.HUDbuttons2_Obj.Object;
	HUDbuttonsBuy = ConstructorStatics.HUDbuttonsBuy_Obj.Object;
	Arrows = ConstructorStatics.Arrows_Obj.Object;
	GreenLayer = ConstructorStatics.GreenLayer_Obj.Object;
	WideButton = ConstructorStatics.WideButton_Obj.Object;
	LevelSelectFrontMenu = ConstructorStatics.LevelSelectFrontMenu_Obj.Object;
	LockTexture_256 = ConstructorStatics.LockTexture_256_Obj.Object;
	PlayLevelMenu_1 = ConstructorStatics.PlayLevelMenu_1_Obj.Object;
	PlayLevelMenu_2 = ConstructorStatics.PlayLevelMenu_2_Obj.Object;
	PlayLevelMenu_3 = ConstructorStatics.PlayLevelMenu_3_Obj.Object;
	PlayLevelMenu_4 = ConstructorStatics.PlayLevelMenu_4_Obj.Object;
	Flags = ConstructorStatics.Flags_Obj.Object;
	ButtonColors = ConstructorStatics.ButtonColors_Obj.Object;

	/// Script / UMGEditor.WidgetBlueprint'/Game/UI/FactsWidget.FactsWidget'
	/*static ConstructorHelpers::FClassFinder<UFactsWidget> WidgetClass(TEXT("/Game/UI/FactsWidget.FactsWidget_C"));
	if (WidgetClass.Succeeded())
	{
		FactsUserWidgetReference = WidgetClass.Class;
	}*/

	//UserWidgetInstance = ConstructorStatics.UserWidgetInstance_Obj.Object;
}


void AJumpyFrogsHUD::DrawHUD()
{
	Super::DrawHUD();
	SD = FVector2D(Canvas->SizeX, Canvas->SizeY);
	/*
	if (bGameOver)
	{
		//FVector2D GameOverSize;
		if (IsLevelWon)
		{
			bDrawHudIcons = false;
			bDrawAIActive = false;
			bDrawAiSolverMenu = false;
			bLevelWon = true;
			LevelWonSound();
			bGameOver = false;
			startGameOverCount = false;
			//IsLevelWon = false;
			//UndoFrGgAnlytcs::]RecordGoogleEvent("Level " + FString::FromInt(CurrentLevel) + " Won", "TimeSpent: " + FString::SanitizeFloat(PlayTime), "Score: " + FString::SanitizeFloat(Score), Score);
			//UndoFrGgAnlytcs::]RecordGoogleScreen("Level " + FString::FromInt(CurrentLevel) + " Won");
		}
		else
		{
			bDrawHudIcons = false;
			bDrawAIActive = false;
			bLevelFailed = true;
			LevelFailedSound();
			bGameOver = false;
			startGameOverCount = false;
			//IsLevelWon = false;
			//UndoFrGgAnlytcs::]RecordGoogleEvent("Level " + FString::FromInt(CurrentLevel) + " Failed", "TimeSpent: " + FString::SanitizeFloat(PlayTime), "Score: " + FString::SanitizeFloat(Score), Score);
			//UndoFrGgAnlytcs::]RecordGoogleScreen("Level " + FString::FromInt(CurrentLevel) + " Failed");
		}
		bTimeCounting = false;
	}*/
	float IconSize = SD.X / 12;
	FVector2D IconHitBox = FVector2D(IconSize, IconSize);
	if (bDrawLoadingScreen)
	{
		DrawTexture(GreenLayer, 0.0f, SD.Y * 0.04f, SD.X * 0.995f, SD.Y * 0.9f, 0.0f, 0.25f, 1.0f, 0.75f);
		FVector2D Velik;
		FString Loading = TEXT("Loading");
		GetTextSize(Loading, (float&)Velik.X, (float&)Velik.Y, JFont, FontScale);
		DrawText(Loading, MyColor, (SD.X - Velik.X) / 2, (SD.Y - Velik.Y) / 2, JFont, FontScale);
	}
	//else if (bTransitionHitBox)
	//{
	//	AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
	//	////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("bTransitionHitBox is true!?, skipping rest of checking hud"));
	//}
	else if (bDrawHudIcons)
	{
		//AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level

		//float Height = ;
		//FVector2D FullScreen = FVector2D(SD.X, SD.Y);
		FVector2D TimeTextSize;
		//		FString LevComp = (TEXT("Level  ") + FString::FromInt(CurrentLevel) + ("  Completed"));
		//	FString::SanitizeFloat(RunTime - 3.0f);
		//int32 ttt;
		//FString TimeCount;
		//if (bShowStartCountdown)
		//{
		//	ttt = StartCountdown;
		//	TimeCount = FString::FromInt(ttt);
		//	FontScale -= 0.07f;
		//	if (FontScale < 1.4f) { FontScale = 1.4f; }
		//	AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		//}
		/*else
		{*/
		/*ttt = PlayTime;
		if (ttt > 59)
		{
			int32 mins = ttt / 60;
			int32 secs = ttt % 60;

			TimeCount = FString::FromInt(mins) + TEXT(":") + FString::FromInt(secs);
		}
		else
		{
			TimeCount = FString::FromInt(ttt);
		}*/

		DrawTexture(ButtonColors, 0.0f, 0.0f, IconSize, IconSize, Buttons[15].X, Buttons[15].Y, 0.25f, 0.25f);
		DrawTexture(Buttons1, 0.0f, 0.0f, IconSize, IconSize, 0.0f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(0.0f, 0.0f), IconHitBox, "Pause", false);

		//AI Solver button
		/*DrawTexture(Buttons2, IconSize, 0.0f, IconSize, IconSize, 0.75f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(IconSize, 0.0f), IconHitBox, "AISolver", false);*/

		//FString skor = FString::FromInt(IGameModeInterface::Execute_GetScore(GM));
		FString skor = FString::FromInt(Score);
		GetTextSize(skor, (float&)TimeTextSize.X, (float&)TimeTextSize.Y, JFont, FontScale);
		DrawText(skor, MyColorDark, SD.X - TimeTextSize.X - SD.X / 100, 0.0f, JFont, FontScale);
			
		//GetTextSize(TimeCount, (float&)TimeTextSize.X, (float&)TimeTextSize.Y, JFont, FontScale);
		//DrawText(TimeCount, MyColorDark, (SD.X - TimeTextSize.X) / 2.0f, 0.0f, JFont, FontScale);
	}
	else if (bDrawLevelSelectMenu)
	{
		FVector2D BoxTexSize = FVector2D(SD.X / 8, SD.X / 8);
		FVector2D BackbuttonAndTextureSize = FVector2D(SD.X / 2, SD.X / 8);

		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level

		//DrawTexture(GreenLayer, SD.X/4, 0.0f, SD.X/2, SD.X/2, 0.0f, 0.0f, 1.0f, 1.0f);
		DrawTexture(PlayLevelMenu_1, SD.X / 4, 0.0f, SD.X / 2, SD.X / 2, 0.0f, 0.0f, 1.0f, 1.0f);

		//DrawTexture(GoBackArrow, float(SD.X / 4), 0.0f, BackbuttonAndTextureSize.X, BackbuttonAndTextureSize.Y, 0.0f, 0.0f, 1.0f, 0.25f);
		AddHitBox(FVector2D(float(SD.X / 4), 0.0f), BackbuttonAndTextureSize, "Back", false);

		DrawTexture(Arrows, SD.X / 8 * 6.5f, SD.X / 8 * 2.7f, SD.X / 8, SD.X / 8 / 2, 0.0f, 0.0f, 1.0f, 0.5f);
		AddHitBox(FVector2D(SD.X / 8 * 6.5f, SD.X / 8 * 2.7f), FVector2D(SD.X / 8, SD.X / 8 / 2), "NextPage", false);

		float PosX = SD.X / 4;
		float PosY = SD.X / 8;
	
		for (int32 i = 1; i < 13; ++i)
		{
			if (UnlockedArray[i + DeltaLevel - 1])
			{
				DrawTexture(LockTexture_256, PosX, PosY, BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.0f, 1.0f, 1.0f);
			}
			else
			{
				if (HighScoreArray[i + DeltaLevel - 1] >= HS3StarsLimitArray[i + DeltaLevel])
				{
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.0f, 1.0f, 0.333333f);
				}
				else if (HighScoreArray[i + DeltaLevel - 1] >= HS2StarsLimitArray[i + DeltaLevel])
				{
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.333333f, 1.0f, 0.333333f);
				}
				else if (HighScoreArray[i + DeltaLevel - 1] > 100)
				{
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.666666f, 1.0f, 0.333333f);
				}

				AddHitBox(FVector2D(PosX, PosY), BoxTexSize, FName(*FString::FromInt(i)), false);
			}
			PosX += BoxTexSize.X;
			if (PosX > (SD.X / 4 + BoxTexSize.X * 3))
			{
				PosY += BoxTexSize.X;
				PosX = SD.X / 4;
			}
		}
		//AddHitBox(FVector2D(SD.X - BoxTexSize.X, (SD.Y - BoxTexSize.X)), BoxTexSize, "SocialMedia", false);
	}
	else if (bDrawLevelSelectMenu2)
	{
		FVector2D BoxTexSize = FVector2D(SD.X / 8, SD.X / 8);
		FVector2D BackbuttonAndTextureSize = FVector2D(SD.X / 2, SD.X / 8);

		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level

		//DrawTexture(GreenLayer, SD.X / 4, 0.0f, SD.X / 2, SD.X / 2, 0.0f, 0.0f, 1.0f, 1.0f);
		DrawTexture(PlayLevelMenu_2, SD.X / 4, 0.0f, SD.X / 2, SD.X / 2, 0.0f, 0.0f, 1.0f, 1.0f);

		//DrawTexture(GoBackArrow, float(SD.X / 4), 0.0f, BackbuttonAndTextureSize.X, BackbuttonAndTextureSize.Y, 0.0f, 0.0f, 1.0f, 0.25f);
		AddHitBox(FVector2D(float(SD.X / 4), 0.0f), BackbuttonAndTextureSize, "Back", false);

		if (DeltaLevel == 300)
		{
			DrawTexture(GreenLayer, SD.X / 4, SD.X / 4 + BoxTexSize.X, SD.X / 2, BoxTexSize.X, 0.0f, 0.75f, 1.0f, 0.25f);
		}
		else
		{
			DrawTexture(Arrows, SD.X / 8 * 6.5f, SD.X / 8 * 2.7f, SD.X / 8, SD.X / 8 / 2, 0.0f, 0.0f, 1.0f, 0.5f);
			AddHitBox(FVector2D(SD.X / 8 * 6.5f, SD.X / 8 * 2.7f), FVector2D(SD.X / 8, SD.X / 8 / 2), "NextPage", false);
		}


		DrawTexture(Arrows, SD.X / 8 * 0.5f, SD.X / 8 * 2.7f, SD.X / 8, SD.X / 8 / 2, 0.0f, 0.5f, 1.0f, 0.5f);
		AddHitBox(FVector2D(SD.X / 8 * 0.5f, SD.X / 8 * 2.7f), FVector2D(SD.X / 8, SD.X / 8 / 2), "PrevPage", false);


		float PosX = SD.X / 4;
		float PosY = SD.X / 8;
		int32 MaxLev = 25;
		if (DeltaLevel == 300) { MaxLev = 21; }

		for (int32 i = 13; i < MaxLev; ++i)
		{
			if (UnlockedArray[i + DeltaLevel - 1])
			{
				DrawTexture(LockTexture_256, PosX, PosY, BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.0f, 1.0f, 1.0f);
			}
			else
			{
				if (HighScoreArray[i + DeltaLevel - 1] >= HS3StarsLimitArray[i + DeltaLevel])
				{//ThreeStars
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.0f, 1.0f, 0.333333f);
				}
				else if (HighScoreArray[i + DeltaLevel - 1] >= HS2StarsLimitArray[i + DeltaLevel])
				{//TwoStars
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.333333f, 1.0f, 0.333333f);
				}
				else if (HighScoreArray[i + DeltaLevel - 1] > 100)
				{//OneStar
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.666666f, 1.0f, 0.333333f);
				}
				AddHitBox(FVector2D(PosX, PosY), BoxTexSize, FName(*FString::FromInt(i)), false);
			}
			PosX += BoxTexSize.X;
			if (PosX > (SD.X / 4 + BoxTexSize.X * 3))
			{
				PosY += BoxTexSize.X;
				PosX = SD.X / 4;
			}
		}
	}
	else if (bDrawLevelSelectMenu3)
	{
		FVector2D BoxTexSize = FVector2D(SD.X / 8, SD.X / 8);
		FVector2D BackbuttonAndTextureSize = FVector2D(SD.X / 2, SD.X / 8);

		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level

		//DrawTexture(GreenLayer, SD.X / 4, 0.0f, SD.X / 2, SD.X / 2, 0.0f, 0.0f, 1.0f, 1.0f);
		DrawTexture(PlayLevelMenu_3, SD.X / 4, 0.0f, SD.X / 2, SD.X / 2, 0.0f, 0.0f, 1.0f, 1.0f);

		//DrawTexture(GoBackArrow, float(SD.X / 4), 0.0f, BackbuttonAndTextureSize.X, BackbuttonAndTextureSize.Y, 0.0f, 0.0f, 1.0f, 0.25f);
		AddHitBox(FVector2D(float(SD.X / 4), 0.0f), BackbuttonAndTextureSize, "Back", false);

		if (DeltaLevel == 0)
		{
			DrawTexture(GreenLayer, SD.X / 4, SD.X / 4 + BoxTexSize.X, SD.X / 2, BoxTexSize.X, 0.0f, 0.75f, 1.0f, 0.25f);
		}
		else if (DeltaLevel == 200)
		{
			DrawTexture(GreenLayer, SD.X / 4, SD.X / 4, SD.X / 2, BoxTexSize.X * 2, 0.0f, 0.5f, 1.0f, 0.5f);
		}
		else
		{
			DrawTexture(Arrows, SD.X / 8 * 6.5f, SD.X / 8 * 2.7f, SD.X / 8, SD.X / 8 / 2, 0.0f, 0.0f, 1.0f, 0.5f);
			AddHitBox(FVector2D(SD.X / 8 * 6.5f, SD.X / 8 * 2.7f), FVector2D(SD.X / 8, SD.X / 8 / 2), "NextPage", false);
		}
		DrawTexture(Arrows, SD.X / 8 * 0.5f, SD.X / 8 * 2.7f, SD.X / 8, SD.X / 8 / 2, 0.0f, 0.5f, 1.0f, 0.5f);
		AddHitBox(FVector2D(SD.X / 8 * 0.5f, SD.X / 8 * 2.7f), FVector2D(SD.X / 8, SD.X / 8 / 2), "PrevPage", false);


		float PosX = SD.X / 4;
		float PosY = SD.X / 8;
		int32 MaxLev = 37;
		if (DeltaLevel == 0) { MaxLev = 33; }
		else if (DeltaLevel == 200) { MaxLev = 29; }
		for (int32 i = 25; i < MaxLev; ++i)
		{
			if (UnlockedArray[i + DeltaLevel])
			{
				DrawTexture(LockTexture_256, PosX, PosY, BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.0f, 1.0f, 1.0f);
			}
			else
			{
				if (HighScoreArray[i + DeltaLevel - 1] >= HS3StarsLimitArray[i + DeltaLevel])
				{//ThreeStars
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.0f, 1.0f, 0.333333f);
				}//TwoStars
				else if (HighScoreArray[i + DeltaLevel - 1] >= HS2StarsLimitArray[i + DeltaLevel])
				{
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.333333f, 1.0f, 0.333333f);
				}
				else if (HighScoreArray[i + DeltaLevel - 1] > 100)
				{//OneStar
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.666666f, 1.0f, 0.333333f);
				}
				AddHitBox(FVector2D(PosX, PosY), BoxTexSize, FName(*FString::FromInt(i)), false);
			}
			PosX += BoxTexSize.X;
			if (PosX > (SD.X / 4 + BoxTexSize.X * 3))
			{
				PosY += BoxTexSize.X;
				PosX = SD.X / 4;
			}
		}
	}
	else if (bDrawLevelSelectMenu4)
	{
		FVector2D BoxTexSize = FVector2D(SD.X / 8, SD.X / 8);
		FVector2D BackbuttonAndTextureSize = FVector2D(SD.X / 2, SD.X / 8);

		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level

		//DrawTexture(GreenLayer, SD.X / 4, 0.0f, SD.X / 2, SD.X / 2, 0.0f, 0.0f, 1.0f, 1.0f);
		DrawTexture(PlayLevelMenu_4, SD.X / 4, 0.0f, SD.X / 2, SD.X / 2, 0.0f, 0.0f, 1.0f, 1.0f);

		//DrawTexture(GoBackArrow, float(SD.X / 4), 0.0f, BackbuttonAndTextureSize.X, BackbuttonAndTextureSize.Y, 0.0f, 0.0f, 1.0f, 0.25f);
		AddHitBox(FVector2D(float(SD.X / 4), 0.0f), BackbuttonAndTextureSize, "Back", false);

		/*DrawTexture(Arrows, SD.X / 8 * 6.5f, SD.X / 8 * 2.7f, SD.X / 8, SD.X / 8 / 2, 0.0f, 0.0f, 1.0f, 0.5f);
		AddHitBox(FVector2D(SD.X / 8 * 6.5f, SD.X / 8 * 2.7f), FVector2D(SD.X / 8, SD.X / 8 / 2), "NextPage", false);*/

		DrawTexture(Arrows, SD.X / 8 * 0.5f, SD.X / 8 * 2.7f, SD.X / 8, SD.X / 8 / 2, 0.0f, 0.5f, 1.0f, 0.5f);
		AddHitBox(FVector2D(SD.X / 8 * 0.5f, SD.X / 8 * 2.7f), FVector2D(SD.X / 8, SD.X / 8 / 2), "PrevPage", false);


		float PosX = SD.X / 4;
		float PosY = SD.X / 8;
		
		for (int32 i = 37; i < 41; ++i)
		{
			if (UnlockedArray[i + DeltaLevel])
			{
				DrawTexture(LockTexture_256, PosX, PosY, BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.0f, 1.0f, 1.0f);
			}
			else
			{
				if (HighScoreArray[i + DeltaLevel - 1] >= HS3StarsLimitArray[i + DeltaLevel])
				{//ThreeStars
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.0f, 1.0f, 0.333333f);
				}
				else if (HighScoreArray[i + DeltaLevel - 1] >= HS2StarsLimitArray[i + DeltaLevel])
				{//TwoStars
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.333333f, 1.0f, 0.333333f);
				}
				else if (HighScoreArray[i + DeltaLevel - 1] > 100)
				{//OneStar
					DrawTexture(Stars, PosX + BoxTexSize.X * 0.125, PosY + BoxTexSize.X * 0.65f, BoxTexSize.X * 0.75f, BoxTexSize.Y * 0.25f, 0.0f, 0.666666f, 1.0f, 0.333333f);
				}
				AddHitBox(FVector2D(PosX, PosY), BoxTexSize, FName(*FString::FromInt(i)), false);
			}
			PosX += BoxTexSize.X;
			if (PosX > (SD.X / 4 + BoxTexSize.X * 3))
			{
				PosY += BoxTexSize.X;
				PosX = SD.X / 4;
			}
		}
	}
	else if (bDraw4LevelsType)
	{
		FVector2D BackbuttonAndTextureSize = FVector2D(SD.X / 2, SD.X / 8);
		FVector2D BoxTexSize = FVector2D(SD.X / 4, SD.X / 8 * 1.5f);

		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level

		//DrawTexture(GreenLayer, float (SD.X/4) , 0.0f , float(SD.X / 2), float(SD.X / 2), 0.0f, 0.0f, 1.0f, 1.0f);
		DrawTexture(GreenLayer, float(SD.X / 4), 0.0f, float(SD.X / 2), float(SD.X / 2), 0.0f, 0.0f, 1.0f, 1.0f);
		DrawTexture(LevelSelectFrontMenu, float(SD.X / 4), 0.0f, float(SD.X / 2), float(SD.X / 2), 0.0f, 0.0f, 1.0f, 1.0f);
		//DrawTexture(LevelSelectFrontMenu, float(SD.X / 4), float(SD.X / 8), float(SD.X / 2), float(SD.X / 8 * 3), 0.0f, 0.0f, 1.0f, 0.75f);

		//DrawTexture(GoBackArrow, float(SD.X / 4), 0.0f , BackbuttonAndTextureSize.X, BackbuttonAndTextureSize.Y, 0.0f, 0.0f, 1.0f, 0.25f);


		AddHitBox(FVector2D(float(SD.X / 4), 0.0f), BackbuttonAndTextureSize, "Back", false);

		AddHitBox(FVector2D(float(SD.X / 4), float(SD.X / 8)), BoxTexSize, "Classic", false);
		
		if (UnlockedArray[100]) //if unlocked (false means its unlocked)
		{
			DrawTexture(LockTexture_256, float((SD.X / 2) + (SD.X / 8)) - BoxTexSize.Y / 2, float(SD.X / 7.3f), BoxTexSize.Y, BoxTexSize.Y, 0.0f, 0.0f, 1.0f, 1.0f);
		}
		else //draw lock texture
		{
			AddHitBox(FVector2D(float(SD.X / 2), float(SD.X / 8)), BoxTexSize, "Teleporters", false);
		}
		if (UnlockedArray[200])  //if unlocked
		{
			DrawTexture(LockTexture_256, float((SD.X / 4) + (SD.X / 8)) - BoxTexSize.Y / 2, float(SD.X / 8 + SD.X / 8 * 1.49f), BoxTexSize.Y, BoxTexSize.Y, 0.0f, 0.0f, 1.0f, 1.0f);
			//AddHitBox(FVector2D(float(SD.X / 4), float(SD.X / 8)), BoxTexSize, "Bombs", false);
		}
		else //draw lock texture
		{
			AddHitBox(FVector2D(float(SD.X / 4), float(SD.X / 8 + SD.X / 8 * 1.5f)), BoxTexSize, "Bombs", false);
		}
		if (UnlockedArray[300])  //if unlocked
		{
			DrawTexture(LockTexture_256, float((SD.X / 2) + (SD.X / 8)) - BoxTexSize.Y / 2, float(SD.X / 8 + SD.X / 8 * 1.49f), BoxTexSize.Y, BoxTexSize.Y, 0.0f, 0.0f, 1.0f, 1.0f);
		}
		else
		{
			AddHitBox(FVector2D(float(SD.X / 2), float(SD.X / 8 + SD.X / 8 * 1.5f)), BoxTexSize, "TeleporterBombs", false);
		}
	}
	else if (bStartMenu)
	{
		//FVector2D BackbuttonAndTextureSize = FVector2D(SD.X / 2, SD.X / 8);
		FVector2D BoxTexSize = FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6);

		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		
		DrawTexture(ButtonColors, 0.0f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[0].X, Buttons[0].Y, 0.25f, 0.25f);
		DrawTexture(Buttons1, 0.0f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.25f, 0.25f, 0.25f, 0.25f);
		AddHitBox(FVector2D(0.0f, (SD.Y - BoxTexSize.X)), BoxTexSize, "SwissKnife", false);
		if (bSwissKnife)
		{			
			DrawTexture(ButtonColors, 0.0f, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[1].X, Buttons[2].Y, 0.25f, 0.25f);
			DrawTexture(Buttons1, 0.0f, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.5f, 0.5f, 0.25f, 0.25f);
			AddHitBox(FVector2D(0.0f, (SD.Y - 2 * BoxTexSize.X)), BoxTexSize, "Credits", false);

			DrawTexture(ButtonColors, BoxTexSize.X, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[3].X, Buttons[3].Y, 0.25f, 0.25f);
			DrawTexture(Buttons1, BoxTexSize.X, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.75f, 0.5f, 0.25f, 0.25f);
			AddHitBox(FVector2D(BoxTexSize.X, (SD.Y - 2 * BoxTexSize.X)), BoxTexSize, "ResetGame", false);

			if (PLATFORM_ANDROID)
			{
				//DrawTexture(HUDbuttonsBuy, 0.0f, (SD.Y - 3 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.5f, 0.5f, 0.5f, 0.5f);
				DrawTexture(ButtonColors, 0.0f, (SD.Y - 3 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[4].X, Buttons[4].Y, 0.25f, 0.25f);
				DrawTexture(Buttons1, 0.0f, (SD.Y - 3 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.25f, 0.75f, 0.25f, 0.25f);
			}
			else
			{
				//DrawTexture(HUDbuttonsBuy, 0.0f, (SD.Y - 3 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.5f, 0.5f, 0.5f);
				DrawTexture(ButtonColors, 0.0f, (SD.Y - 3 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[5].X, Buttons[5].Y, 0.25f, 0.25f);
				DrawTexture(Buttons1, 0.0f, (SD.Y - 3 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.75f, 0.25f, 0.25f);
			}
			AddHitBox(FVector2D(0.0f, (SD.Y - 3 * BoxTexSize.X)), BoxTexSize, "AskUser", false);

			FVector2D FlagSize = BoxTexSize;
			FlagSize.Y = FlagSize.X * 0.66666667f;
			if (Flags)
			{
				DrawTexture(Flags, BoxTexSize.X * 2.f + FlagSize.X * 0.15f, SD.Y - BoxTexSize.Y*0.5f - FlagSize.Y*0.5f, FlagSize.X, FlagSize.Y, FlagUVPos.X, FlagUVPos.Y, 0.25f, 0.67f);
			}
			AddHitBox(FVector2D(BoxTexSize.X * 2.f + FlagSize.X * 0.15f, SD.Y - BoxTexSize.Y * 0.5f - FlagSize.Y * 0.5f), FlagSize, "Language", false);

			DrawTexture(ButtonColors, BoxTexSize.X, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[6].X, Buttons[6].Y, 0.25f, 0.25f);
			DrawTexture(Buttons1, BoxTexSize.X, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.5f, 0.75f, 0.25f, 0.25f);
			if (!bSoundOn)
			{
				DrawTexture(Buttons1, BoxTexSize.X, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.75f, 0.75f, 0.25f, 0.25f);
			}
			AddHitBox(FVector2D(BoxTexSize.X, (SD.Y - BoxTexSize.X)), BoxTexSize, "SoundOnOff", false);
		}
		/*else
		{
			DrawTexture(ButtonColors, 0.0f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y,Buttons[0].X, Buttons[0].Y, 0.25f, 0.25f);
			DrawTexture(Buttons1, 0.0f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.25f, 0.25f, 0.25f, 0.25f);
			AddHitBox(FVector2D(0.0f, (SD.Y - BoxTexSize.X)), BoxTexSize, "SwissKnife", false);
		}*/

		//social media buttons.............
		if (bSocialMedia)
		{
			DrawTexture(ButtonColors, SD.X - BoxTexSize.X, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[8].X, Buttons[8].Y, 0.25f, 0.25f);
			DrawTexture(Buttons1, SD.X - BoxTexSize.X, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.75f, 0.25f, -0.25f);
			AddHitBox(FVector2D(SD.X - BoxTexSize.X, (SD.Y - BoxTexSize.X)), BoxTexSize, "SocialMedia", false);

			/*if (bDrawFbLike)
			{
				DrawTexture(ButtonColors, SD.X - BoxTexSize.X, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[9].X, Buttons[9].Y, 0.25f, 0.25f);
				DrawTexture(Buttons2, SD.X - BoxTexSize.X, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.5f, 0.25f, 0.25f);
				AddHitBox(FVector2D(SD.X - BoxTexSize.X, (SD.Y - 2 * BoxTexSize.X)), BoxTexSize, "Facebook", false);
				DrawTexture(ButtonColors, SD.X - BoxTexSize.X * 2, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[10].X, Buttons[10].Y, 0.25f, 0.25f);
				DrawTexture(Buttons2, SD.X - BoxTexSize.X * 2, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.5f, 0.5f, 0.25f, 0.25f);
				AddHitBox(FVector2D(SD.X - BoxTexSize.X * 2, (SD.Y - 2 * BoxTexSize.X)), BoxTexSize, "Friends", false);
				DrawTexture(ButtonColors, SD.X - BoxTexSize.X * 3, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[11].X, Buttons[11].Y, 0.25f, 0.25f);
				DrawTexture(Buttons2, SD.X - BoxTexSize.X * 3, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.75f, 0.5f, 0.25f, 0.25f);
				AddHitBox(FVector2D(SD.X - BoxTexSize.X * 3, (SD.Y - 2 * BoxTexSize.X)), BoxTexSize, "FbPage", false);

			}
			else*/
			//{
				DrawTexture(ButtonColors, SD.X - BoxTexSize.X, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[9].X, Buttons[9].Y, 0.25f, 0.25f);
				DrawTexture(Buttons2, SD.X - BoxTexSize.X, (SD.Y - 2 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.5f, 0.25f, 0.25f);
				AddHitBox(FVector2D(SD.X - BoxTexSize.X, (SD.Y - 2 * BoxTexSize.X)), BoxTexSize, "Facebook", false);
			//}


			DrawTexture(ButtonColors, SD.X - BoxTexSize.X, (SD.Y - 3 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[10].X, Buttons[10].Y, 0.25f, 0.25f);
			DrawTexture(Buttons2, SD.X - BoxTexSize.X, (SD.Y - 3 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.75f, 0.25f, 0.25f, 0.25f);
			AddHitBox(FVector2D(SD.X - BoxTexSize.X, (SD.Y - 3 * BoxTexSize.X)), BoxTexSize, "Tweeter", false);

			DrawTexture(ButtonColors, SD.X - BoxTexSize.X, (SD.Y - 4 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[11].X, Buttons[11].Y, 0.25f, 0.25f);
			DrawTexture(Buttons2, SD.X - BoxTexSize.X, (SD.Y - 4 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.25f, 0.5f, 0.25f, 0.25f);
			AddHitBox(FVector2D(SD.X - BoxTexSize.X, (SD.Y - 4 * BoxTexSize.X)), BoxTexSize, "Instagram", false);

			DrawTexture(ButtonColors, SD.X - BoxTexSize.X, (SD.Y - 5 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[12].X, Buttons[12].Y, 0.25f, 0.25f);
			DrawTexture(Buttons2, SD.X - BoxTexSize.X, (SD.Y - 5 * BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.0f, 0.25f, 0.25f);
			AddHitBox(FVector2D(SD.X - BoxTexSize.X, (SD.Y - 5 * BoxTexSize.X)), BoxTexSize, "Youtube", false);

			/*	DrawTexture(Buttons2, SD.X - BoxTexSize.X, (SD.Y - 5*BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.25f, 0.25f, 0.25f, 0.25f);
			AddHitBox(FVector2D(SD.X - BoxTexSize.X, (SD.Y - 5*BoxTexSize.X)), BoxTexSize, "Origami", false);*/

		}
		else
		{
			DrawTexture(ButtonColors, SD.X - BoxTexSize.X, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[8].X, Buttons[8].Y, 0.25f, 0.25f);
			DrawTexture(Buttons1, SD.X - BoxTexSize.X, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.5f, 0.25f, 0.25f);
			AddHitBox(FVector2D(SD.X - BoxTexSize.X, (SD.Y - BoxTexSize.X)), BoxTexSize, "SocialMedia", false);
		}

		//play button
		//DrawTexture(Buttons1, SD.X / 2 - SD.X * 0.0625f, SD.X * 0.25f, SD.X * 0.125f, SD.X * 0.125f, 0.5f, 0.0f, 0.5f, 0.5f);
		DrawTexture(Buttons1, SD.X / 2 - BoxTexSize.X*0.8f, SD.Y/2 - BoxTexSize.Y * 0.8f, BoxTexSize.X*1.6f, BoxTexSize.X * 1.6f, 0.5f, 0.0f, 0.5f, 0.5f);
		AddHitBox(FVector2D(SD.X / 2 - BoxTexSize.X * 0.8f, SD.Y / 2 - BoxTexSize.Y * 0.8f), FVector2D(BoxTexSize.X * 1.6f, BoxTexSize.X * 1.6f), "Play", false);

		//Achievemnts
		DrawTexture(ButtonColors, SD.X / 2 - BoxTexSize.X * 0.5f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[12].X, Buttons[12].Y, 0.25f, 0.25f);
		DrawTexture(Buttons2, SD.X / 2 - BoxTexSize.X * 0.5f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.25f, 0.25f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X / 2 - BoxTexSize.X / 2, (SD.Y - BoxTexSize.X)), BoxTexSize, "Library", false);
		//library
		DrawTexture(ButtonColors, SD.X / 2 - BoxTexSize.X * 1.5f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[14].X, Buttons[14].Y, 0.25f, 0.25f);
		DrawTexture(Buttons2, SD.X / 2 - BoxTexSize.X * 1.5f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.0f, 0.25f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X / 2 - BoxTexSize.X * 1.5f, (SD.Y - BoxTexSize.X)), BoxTexSize, "LeaderBoard", false);
		//leaderboard
		DrawTexture(ButtonColors, SD.X / 2 + BoxTexSize.X * 0.5f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[15].X, Buttons[15].Y, 0.25f, 0.25f);
		DrawTexture(Buttons2, SD.X / 2 + BoxTexSize.X * 0.5f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.5f, 0.25f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X / 2 + BoxTexSize.X * 0.5f, (SD.Y - BoxTexSize.X)), BoxTexSize, "Achievements", false);


		//DrawTexture(LevelSelectFrontMenu, float(SD.X / 4), float(SD.X / 8), float(SD.X / 2), float(SD.X / 8 * 3), 0.0f, 0.0f, 1.0f, 0.75f);

		//DrawTexture(GoBackArrow, float(SD.X / 4), 0.0f, BackbuttonAndTextureSize.X, BackbuttonAndTextureSize.Y, 0.0f, 0.0f, 1.0f, 0.25f);


		//AddHitBox(FVector2D(float(SD.X / 4), 0.0f), BackbuttonAndTextureSize, "Back", false);

		//AddHitBox(FVector2D(float(SD.X / 4), float(SD.X / 8)), BoxTexSize, "Classic", false);


		/*BoxTexSize.Y = BoxTexSize.X * 0.66666667f;
		if (Flags)
		{
			DrawTexture(Flags, SD.X / 2 - BoxTexSize.X * 0.5f, 0.0f, BoxTexSize.X, BoxTexSize.Y, FlagUVPos.X, FlagUVPos.Y, 0.25f, 0.67f);
		}
		AddHitBox(FVector2D(SD.X / 2 - BoxTexSize.X / 2, 0.0f), BoxTexSize, "Language", false);*/
	}
	else if (bDrawPauseMenu)
	{
	/*	DrawTexture(ButtonColors, 0.0f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, Buttons[0].X, Buttons[0].Y, 0.25f, 0.25f);
		DrawTexture(Buttons1, 0.0f, (SD.Y - BoxTexSize.X), BoxTexSize.X, BoxTexSize.Y, 0.25f, 0.25f, 0.25f, 0.25f);
		AddHitBox(FVector2D(0.0f, (SD.Y - BoxTexSize.X)), BoxTexSize, "HomeMenu", false);*/





		//float IconSize = SD.X / 12;
		//FVector2D BackgroundPos = FVector2D(float(SD.X / 2) - (SD.X / 16 * 3.5), float((SD.X / 2 / 2.7f) - (SD.X / 16 * 10 / 6 / 6)));

		//AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level

		//FVector2D IconHitBox = FVector2D(IconSize, IconSize);
		//DrawTexture(GreenLayer, BackgroundPos.X, BackgroundPos.Y, float(SD.X / 16 * 7), float(SD.X / 16 * 10 / 6 * 2.5833f), 0.0f, 0.25f, 1.0f, 0.75f);
		float IconSizeXY = SD.X / 16 * 10 / 6;
		
		//float IconSizeXY = SD.X / 16 * 10 / 6;

		//float IconSizeXY = SD.X / 16 * 10 / 6;// FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6);

		//restart button
		DrawTexture(ButtonColors, 0, 0, IconSizeXY, IconSizeXY, Buttons[3].X, Buttons[3].Y, 0.25f, 0.25f);
		DrawTexture(Buttons1, 0, 0, IconSizeXY, IconSizeXY, 0.0f, 0.25f, 0.25f, 0.25f);
		AddHitBox(FVector2D(0, 0), FVector2D(IconSizeXY, IconSizeXY), "Restart", false);
		
		//Next Level button
		DrawTexture(ButtonColors, IconSizeXY, 0, IconSizeXY, IconSizeXY, Buttons[5].X, Buttons[5].Y, 0.25f, 0.25f);
		DrawTexture(Buttons2, IconSizeXY, 0, IconSizeXY, IconSizeXY, 0.5f, 0.75f, 0.25f, 0.25f);
		if (!UnlockedArray[CurrentLevel] && !(CurrentLevel == 320)) //get unlocked level array for next level
		{
			AddHitBox(FVector2D(IconSizeXY, 0), FVector2D(IconSizeXY, IconSizeXY), "NextLevel", false);
		}
		else
		{
			DrawTexture(Buttons1, IconSizeXY, 0, IconSizeXY, IconSizeXY, 0.75f, 0.75f, 0.25f, 0.25f);
		}

		////level select button
		DrawTexture(ButtonColors, 0, IconSizeXY, IconSizeXY, IconSizeXY, Buttons[2].X, Buttons[2].Y, 0.25f, 0.25f);
		DrawTexture(Buttons1, 0, IconSizeXY,  IconSizeXY, IconSizeXY, 0.25f, 0.5f, 0.25f, 0.25f);
		AddHitBox(FVector2D(0, IconSizeXY), FVector2D(IconSizeXY, IconSizeXY), "LevelSelect", false);

		//Home menu button
		DrawTexture(ButtonColors, IconSizeXY, IconSizeXY, IconSizeXY, IconSizeXY, Buttons[1].X, Buttons[1].Y, 0.25f, 0.25f);
		DrawTexture(Buttons1, IconSizeXY, IconSizeXY,  IconSizeXY, IconSizeXY, 0.25f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(IconSizeXY, IconSizeXY), FVector2D(IconSizeXY, IconSizeXY), "HomeMenu", false);
		

	
		//play button continue
		DrawTexture(Buttons1, SD.X / 2 - IconSizeXY * 0.8f, SD.Y / 2 - IconSizeXY * 0.8f, IconSizeXY * 1.6f, IconSizeXY * 1.6f, 0.5f, 0.0f, 0.5f, 0.5f);
		AddHitBox(FVector2D(SD.X / 2 - IconSizeXY * 0.8f, SD.Y / 2 - IconSizeXY * 0.8f), FVector2D(IconSizeXY * 1.6f, IconSizeXY * 1.6f), "Continue", false);

		////SoundOnOFf button
		//DrawTexture(ButtonColors, float(SD.X / 2 - SD.X / 16 * 10 / 6 * 1.75f), float(SD.X / 2 / 2.7f + SD.X / 16 * 10 / 6 * 1.25f), IconSizeXY, IconSizeXY, Buttons[10].X, Buttons[10].Y, 0.25f, 0.25f);
		//DrawTexture(Buttons1, float(SD.X / 2 - SD.X / 16 * 10 / 6 * 1.75f), float(SD.X / 2 / 2.7f + SD.X / 16 * 10 / 6 * 1.25f), IconSizeXY, IconSizeXY, 0.5f, 0.75f, 0.25f, 0.25f);
		//AddHitBox(FVector2D(float(SD.X / 2 - SD.X / 16 * 10 / 6 * 1.75f), float(SD.X / 2 / 2.7f + SD.X / 16 * 10 / 6 * 1.25f)), FVector2D(IconSizeXY, IconSizeXY), "SoundOnOff", false);
		//if (!bSoundOn)
		//{
		//	DrawTexture(Buttons1, float(SD.X / 2 - SD.X / 16 * 10 / 6 * 1.75f), float(SD.X / 2 / 2.7f + SD.X / 16 * 10 / 6 * 1.25f), IconSizeXY, IconSizeXY, 0.75f, 0.75f, 0.25f, 0.25f);
		//}
		
		
		////Continue button
		//DrawTexture(HUDbuttons1b, float(SD.X / 2 + SD.X / 16 * 10 / 6 * 0.75f), float(SD.X / 2 / 2.7f + SD.X / 16 * 10 / 6 * 1.25f), IconSizeXY, IconSizeXY, 0.75f, 0.0f, 0.25f, 0.25f);
		//AddHitBox(FVector2D(float(SD.X / 2 + SD.X / 16 * 10 / 6 * 0.75f), float(SD.X / 2 / 2.7f + SD.X / 16 * 10 / 6 * 1.25f)), FVector2D(IconSizeXY, IconSizeXY), "Continue", false);

		/*FString TimeCount;
		int32 ttt = PlayTime;
		if (ttt > 59)
		{
			int32 mins = ttt / 60;
			int32 secs = ttt % 60;

			TimeCount = FString::FromInt(mins) + TEXT(":") + FString::FromInt(secs);
		}
		else
		{
			TimeCount = FString::FromInt(ttt);
		}
		FVector2D TimeTextSize;
		GetTextSize(TimeCount, (float&)TimeTextSize.X, (float&)TimeTextSize.Y, JFont, FontScale);
		DrawText(TimeCount, MyColorDark, (SD.X - TimeTextSize.X) / 2.0f, 0.0f, JFont, FontScale);*/
		FVector2D TimeTextSize;
		FString skor = FString::FromInt(Score);
		GetTextSize(skor, (float&)TimeTextSize.X, (float&)TimeTextSize.Y, JFont, FontScale);
		//UE_LOG(LogTemp, Warning, TEXT("Velikost vrstice1 : %s"), *FString::SanitizeFloat(TimeTextSize.X));
		DrawText(skor, MyColorDark, SD.X - TimeTextSize.X * 2.f, 0.0f, JFont, FontScale);

	}
	else if (bDrawLibrary)
	{
		
		//draw library
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		//draw library background
		DrawTexture(GreenLayer, 0.0f, SD.Y * 0.005f, SD.X, SD.Y, 0.005f, 0.25f, 0.99f, 0.75f);
		///////////
		//FVector2D Velikost;
		//if (bLockedTip)
		//{
		//	FVector2D PicSize = FVector2D(SD.X / 4, SD.X / 4 / 4 * 3);
		//	//DrawTexture(LockTexture_256, SD.X / 2, SD.Y / 2 - PicSize.Y*1.2f, PicSize.Y, PicSize.Y, 0.0f, 0.0f, 1.0f, 1.0f);
		//	DrawTexture(LockTexture_256, SD.X / 2 - PicSize.Y * 0.75f, SD.Y / 2 - PicSize.Y * 1.2f, PicSize.Y * 1.5f, PicSize.Y * 1.5f, 0.0f, 0.0f, 1.0f, 1.0f);
		//}
		//else if (bCutStrNextDraw)
		//{
		//	//UE_LOG(LogTemp, Warning, TEXT("bDrawLibrary running,if (bCutStrNextDraw=true, working so far "));
		//	bCutStrNextDraw = false;
		//	//determine how many letters fits into width of the display/canvas
		//	int32 runs = 0;
		//	while (runs < 200)
		//	{
		//		runs++;
		//		////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, MyColor, TEXT("fitting text into width "));
		//		FString TestSt;
		//		if (SelLang == 3 || SelLang == 4)
		//		{
		//			TestSt = TEXT("在在"); //TheTipsArray[TipsIndex].GetCharArray;
		//		}
		//		else
		//		{
		//			TestSt = "13";
		//		}

		//		for (int32 i = 0; i < 200; i++)
		//		{
		//			GetTextSize(TestSt, (float&)Velikost.X, (float&)Velikost.Y, HUDFont, FontScale);
		//			//UE_LOG(LogTemp, Warning, TEXT("Velikost vrstice2 : %s"), *FString::SanitizeFloat(Velikost.X));
		//			//UE_LOG(LogTemp, Warning, TEXT("Vrstica: %s"), *(TestSt));
		//			if (Velikost.X > SD.X)
		//			{
		//				break;
		//			}
		//			if (SelLang == 3 || SelLang == 4)
		//			{
		//				TestSt.Append(TEXT("在"));
		//			}
		//			else { TestSt.Append("3"); }
		//		}
		//		int32 length = TestSt.Len(); //calculated max length of a line
		//		FString zanimivost = TheTipsArray[TipsIndex];
		//		int32 StrLen = zanimivost.Len();
		//		//UE_LOG(LogTemp, Warning, TEXT("zanimivost1: %s"), *(zanimivost));
		//		int32 StVrstic = (StrLen / length) + 1;
		//		//UE_LOG(LogTemp, Warning, TEXT("StVrstic:%s"), *(FString::FromInt(StVrstic)));
		//		for (int32 i = 0; i < 100; i++)
		//		{
		//			GetTextSize(zanimivost, (float&)Velikost.X, (float&)Velikost.Y, HUDFont, FontScale);
		//			//UE_LOG(LogTemp, Warning, TEXT("Velikost vrstice3 : %s"), *FString::SanitizeFloat(Velikost.X));
		//			//UE_LOG(LogTemp, Warning, TEXT("Vrstica: %s"), *(zanimivost));
		//			//if (((Velikost.X / 6) < SD.X) && (Velikost.Y*5.5 < SD.Y / 2.0f))
		//			if (Velikost.Y * StVrstic < SD.Y * 0.70f)
		//			{
		//				//if (i == 0) { FontScale = 1.4f; }
		//				break;
		//			}
		//			FontScale -= 0.01f;
		//		}
		//		//UE_LOG(LogTemp, Warning, TEXT("zanimivost2: %s"), *(zanimivost));
		//		for (int32 i = 0; i < 200; i++)
		//		{
		//			GetTextSize(TestSt, (float&)Velikost.X, (float&)Velikost.Y, HUDFont, FontScale);
		//			//UE_LOG(LogTemp, Warning, TEXT("Velikost vrstice4 : %s"), *FString::SanitizeFloat(Velikost.X));
		//			//UE_LOG(LogTemp, Warning, TEXT("Vrstica: %s"), *(TestSt));
		//			if (Velikost.X > SD.X)
		//			{
		//				break;
		//			}
		//			if (SelLang == 3 || SelLang == 4)
		//			{
		//				TestSt.Append(TEXT("在"));
		//			}
		//			else { TestSt.Append("3"); }
		//		}
		//		//UE_LOG(LogTemp, Warning, TEXT("zanimivost3: %s"), *(zanimivost));
		//		length = TestSt.Len() - 1;//calculated max length of a line
		//		StVrstic = (StrLen / length) + 1;
		//		Vrstice.Reset();
		//		//UE_LOG(LogTemp, Warning, TEXT("Tuki tud še dela očitno! "));
		//		//UE_LOG(LogTemp, Warning, TEXT("StVrstic: %s"), *(FString::FromInt(StVrstic)));
		//		//UE_LOG(LogTemp, Warning, TEXT("calculated max length of a line: %s"), *(FString::FromInt(length)));
		//		//CutString(zanimivost, length);
		//		//bool TooManySpaces = false;
		//		//UE_LOG(LogTemp, Warning, TEXT("zanimivost4: %s"), *(zanimivost));
		//		//UE_LOG(LogTemp, Warning, TEXT("zanimivost4 zanimivost.Len(): %s"), *(FString::FromInt(zanimivost.Len())));
		//		for (int32 i = 0; zanimivost.Len() > 0; i++)
		//		{
		//			//UE_LOG(LogTemp, Warning, TEXT("logging iz  for (int32 i = 0; zanimivost.Len() > 0; i++)"));
		//			//UE_LOG(LogTemp, Warning, TEXT("Velikost vrstice5 : %s"), *FString::SanitizeFloat(Velikost.X));
		//			runs++;
		//			FString tt;
		//			if (zanimivost.Len() > length)
		//			{
		//				//FString tt2 = zanimivost.Left(length + 1);

		//				if (SelLang == 3 || SelLang == 4)
		//				{
		//					for (int32 s = 0; zanimivost.Len() > length; s++)
		//					{
		//						tt = zanimivost.Left(length); // vzamemo ven levo število znakov kolikor jih gre v širino
		//						//int32 endIndex = ttr3.Find(" ", ESearchCase::CaseSensitive, ESearchDir::FromEnd);//najdemo zadnji presledek če obstaja

		//						tt.RemoveFromEnd("(");
		//						tt.RemoveFromEnd(TEXT("（"));
		//						tt.RemoveFromEnd(TEXT("“"));
		//						tt.RemoveFromEnd(TEXT("一"));
		//						bool KejStevilk = true; //to tle ni res  ampk na začetku je blo zarad številk zdej je pa kr skoz pač 
		//						FString NextLine = zanimivost;
		//						NextLine.RemoveFromStart(tt); //kopiramo ostale znake v novo spremenljivo 
		//						for (int32 m = 0; m < 50; m++)
		//						{
		//							tt.Reset();
		//							tt = zanimivost.Left(length + m);
		//							NextLine.Reset();
		//							NextLine = zanimivost;
		//							NextLine.RemoveFromStart(tt);

		//							GetTextSize(tt, (float&)Velikost.X, (float&)Velikost.Y, HUDFont, FontScale);
		//							if (Velikost.X > SD.X)
		//							{
		//								tt.Reset();
		//								tt = zanimivost.Left(length + m - 1);
		//								tt.RemoveFromEnd("(");
		//								tt.RemoveFromEnd(TEXT("（"));
		//								tt.RemoveFromEnd(TEXT("“"));
		//								tt.RemoveFromEnd(TEXT("一"));
		//								NextLine.Reset();
		//								NextLine = zanimivost;
		//								NextLine.RemoveFromStart(tt);

		//								break;
		//							}
		//						}

		//						// preverimo če je drugi znak nove vrstice slučajno " ", če je je treba odvzet eno črko prvi vrstici in jo dat v drugo
		//						TArray <FString> CharsToCheck = { TEXT("。"), TEXT("，"), TEXT("一"),TEXT("！"),TEXT("）"),TEXT(")"),",","!","." };

		//						for (int32 c = 0; c < 9; c++)
		//						{
		//							if (NextLine.StartsWith(CharsToCheck[c]))
		//							{
		//								//IsFirstCharBad = true;
		//								int32 saf = tt.Len();
		//								tt.Reset();
		//								tt = zanimivost.Left(saf - 1);
		//								NextLine.Reset();
		//								NextLine = zanimivost;
		//								NextLine.RemoveFromStart(tt);
		//								break;
		//							}
		//						}
		//						int32 MyShinyNewInt = FCString::Atoi(*tt.Right(1));
		//						////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 5.f, MyColor, tt.Right(1));
		//						////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 5.f, MyColor, FString::FromInt(MyShinyNewInt));
		//						if ((MyShinyNewInt < 10 && MyShinyNewInt>0) || tt.EndsWith(TEXT("0")) || tt.EndsWith(TEXT("."))) //if it is a number 
		//						{
		//							////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 5.f, MyColor, TEXT("It Is TRUE!!"));
		//							//check if there is a number also the first char in next line
		//							int32 TestInt = FCString::Atoi(*NextLine.Left(1));
		//							if ((TestInt < 10 && TestInt>0) || NextLine.StartsWith(TEXT("0")) || NextLine.StartsWith(TEXT("."))) //if it is a number 
		//							{
		//								////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 5.f, MyColor, TEXT("It Is TRUE also again!!"));
		//								//obviously the number is split into new line, so find the first number in the number sequence from the end of first line, and then search for first char that is not a number
		//								for (int32 u = 2; u < 10; u++)
		//								{
		//									FString hh = tt.Right(u);
		//									FString gg = hh.Left(1);
		//									int32 TestInttt = FCString::Atoi(*gg);
		//									if (((TestInttt < 10 && TestInttt>0) || gg.StartsWith(TEXT("0"))))
		//									{
		//										int dasg = tt.Len();
		//										tt.Reset();
		//										tt = zanimivost.Left(dasg - u - 1);
		//										NextLine.Reset();
		//										NextLine = zanimivost;
		//										NextLine.RemoveFromStart(tt);
		//										break;
		//									}
		//								}
		//							}
		//						}
		//						TArray <FString> LettersToCheck = { "a","b","t","r","o","c","h","l","i","g","s","m","p","h","n","e",TEXT("”") };
		//						for (int32 c = 0; c < 16; c++)
		//						{
		//							if (tt.EndsWith(LettersToCheck[c]))
		//							{
		//								//so the last char is obviously a letter and probably a broken word, so to make sure, we check next line first char
		//								for (int32 t = 0; t < 17; t++)
		//								{
		//									if (NextLine.StartsWith(LettersToCheck[t]))
		//									{
		//										//obviously the word is broken at end of line so search the first line from-end untill you find TEXT("“")
		//										int32 WhereToCut = tt.Find(TEXT("“"), ESearchCase::CaseSensitive, ESearchDir::FromEnd);

		//										//int32 saf = tt.Len();
		//										tt.Reset();
		//										tt = zanimivost.Left(WhereToCut);
		//										NextLine.Reset();
		//										NextLine = zanimivost;
		//										NextLine.RemoveFromStart(tt);
		//										//
		//										break;
		//									}
		//								}
		//								break;
		//								//IsFirstCharBad = true;
		//							}
		//						}
		//						Vrstice.Add(tt);
		//						zanimivost.RemoveFromStart(tt);
		//					}
		//				}
		//				else
		//				{
		//					tt = zanimivost.Left(length);
		//					int32 endIndex = tt.Find(" ", ESearchCase::CaseSensitive, ESearchDir::FromEnd);

		//					//we get next line
		//					FString Temp = tt.Right(length - endIndex);
		//					tt.RemoveFromEnd(Temp);

		//					FString NextLine = zanimivost;
		//					NextLine.RemoveFromStart(tt);


		//					FString tricrke;
		//					tricrke = TEXT("xxx");

		//					float LetterSizeX, LetterSizeY;
		//					GetTextSize(tricrke, LetterSizeX, LetterSizeY, HUDFont, FontScale);

		//					//look in next line and copy first word to the end of previous line and test its length
		//					//GetTextSize(tt, (float&)Velikost.X, (float&)Velikost.Y, HUDFont, FontScale);
		//					for (int32 m = 0; m < 10; m++)
		//					{
		//						//if we'll copy the word we'll need the empty space before the word 
		//						//find first word in next line
		//						FString NextLineTemp = NextLine;
		//						FString FirstWord;
		//						if (NextLineTemp.RemoveFromStart(TEXT(" "))) //removes the empy " "space if there is one at start
		//						{
		//							FirstWord.Append(TEXT(" "));
		//						}
		//						//UE_LOG(LogTemp, Warning, TEXT("NextLineTemp:%s"), *NextLineTemp);
		//						int32 WordEndIndex = NextLineTemp.Find(" ", ESearchCase::CaseSensitive, ESearchDir::FromStart);//find next " ", this will index the where the word ends 
		//						//UE_LOG(LogTemp, Warning, TEXT("WordEndIndex: %s"), *FString::FromInt(WordEndIndex));
		//						//copy from the string the first word and paste it to the first line 
		//						//we set the first char to be empty space (we could later add if its start of a sentence to not need empty space)
		//						FirstWord.Append(NextLineTemp.Left(WordEndIndex));// create the string FirstWord of second line 
		//						////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, FirstWord);
		//						//UE_LOG(LogTemp, Warning, TEXT("FirstWord:%s"), *FirstWord);
		//						FString appendix = tt;// copy to new string to test if it will work this way or is the line too long now
		//						appendix.Append(FirstWord); // if too long, we skip adding more words and rather continue with inserting empty spaces to match the width
		//						//UE_LOG(LogTemp, Warning, TEXT("appendix.Append(FirstWord);: %s"), *appendix);
		//						GetTextSize(appendix, (float&)Velikost.X, (float&)Velikost.Y, HUDFont, FontScale);
		//						//UE_LOG(LogTemp, Warning, TEXT("Tuki Je problem -appendix- Velikost vrstice 2: %s"), *FString::SanitizeFloat(Velikost.X));
		//						if (Velikost.X < (SD.X - LetterSizeX))
		//						{
		//							tt.Append(FirstWord);
		//							NextLine.RemoveFromStart(FirstWord);
		//						}
		//						else { break; } //stop the loop and continue with inserting empty spaces to fit the desired width
		//						//GetTextSize(tt, (float&)Velikost.X, (float&)Velikost.Y, HUDFont, FontScale);
		//					}


		//					//FVector2D Vel2;
		//					//find all positions of " " in the whole string!
		//					FString chkstr = tt;
		//					TArray <int32> Presledki;
		//					chkstr.RemoveFromEnd(" "); //removes empty space at the end if it is there
		//					chkstr.RemoveFromStart(" "); //removes empty space at start if it is there
		//					for (int32 m = 0; m < 100 && chkstr.Contains(TEXT(" "), ESearchCase::CaseSensitive, ESearchDir::FromStart); m++)
		//					{
		//						int32 indx = chkstr.Find(" ", ESearchCase::CaseSensitive, ESearchDir::FromEnd);
		//						FString TempS = chkstr.Right(chkstr.Len() - indx + 1);
		//						chkstr.RemoveFromEnd(TempS);
		//						Presledki.Add(indx);
		//						////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, MyColor, FString::FromInt(indx));
		//					}
		//					FString tttemp = tt;
		//					FVector2D Vel;
		//					//GetTextSize(tttemp, (float&)Vel.X, (float&)Vel.Y, HUDFont, FontScale);
		//					tttemp.RemoveFromEnd(" "); //removes empty space at the end if it is there
		//					tttemp.RemoveFromStart(" "); //removes empty space at start if it is there
		//					GetTextSize(tttemp, (float&)Vel.X, (float&)Vel.Y, HUDFont, FontScale);
		//					int32 h = 0; int32 f = 0; int32 ajaa = 0;
		//					//	TooManySpaces = false;
		//					////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Velikost vrstice:") + FString::SanitizeFloat(Vel.X));
		//					////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::SanitizeFloat(Vel.X));
		//					//	UE_LOG(LogTemp, Warning, *(FString::SanitizeFloat(Vel.X)));
		//					//UE_LOG(LogTemp, Warning, TEXT("Velikost vrstice 6 : %s"), *FString::SanitizeFloat(Vel.X));
		//					//UE_LOG(LogTemp, Warning, TEXT("tttemp String je tukaj, it tega je zračunana velikost: %s"), *tttemp);
		//					for (int32 j = 0; Vel.X < (SD.X - LetterSizeX); j++)
		//					{
		//						//UE_LOG(LogTemp, Warning, TEXT("LetterSizeX:%s"), *FString::SanitizeFloat(LetterSizeX));
		//						////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("vstavljanje presledkov for loop executed"));
		//						if (j == Presledki.Num())
		//						{
		//							f++;
		//							j = 0;
		//							h += (Presledki.Num()) * f;
		//						}
		//						//ajaa++;
		//						//if ( 8 < ajaa) { TooManySpaces = true;}
		//						tttemp.InsertAt(Presledki[j] + h, TEXT(" "));
		//						h -= 1 * f;
		//						GetTextSize(tttemp, (float&)Vel.X, (float&)Vel.Y, HUDFont, FontScale);
		//					}
		//					////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("vstavljanje presledkov for loop executed"));
		//					//UE_LOG(LogTemp, Warning, TEXT("A dela tle pred	Vrstice.Add"));
		//					Vrstice.Add(tttemp);
		//					zanimivost.RemoveFromStart(tt);
		//				}
		//			}
		//			else
		//			{
		//				Vrstice.Add(zanimivost);
		//				break;
		//			}
		//		}
		//		//check if there are more than 3 spaces one after another , if so reduce the fontsize
		//		//check if there are more than 3 spaces one after another , if so reduce the fontsize
		//		if (!(SelLang == 3) || !(SelLang == 4))
		//		{
		//			bool TooManySpaces = false;
		//			for (int32 i = 0; i < Vrstice.Num(); i++)
		//			{
		//				FString FinalTest = Vrstice[i];
		//				int32 indx = FinalTest.Find(" ", ESearchCase::CaseSensitive, ESearchDir::FromStart);
		//				int32 xCounter = 0;
		//				while (FinalTest.Len() > 0)
		//				{
		//					//FString Letter = FinalTest.Left(1);
		//					if (FinalTest.RemoveFromStart(" "))
		//					{
		//						xCounter++;
		//						if (xCounter > 2) { TooManySpaces = true; break; }
		//					}
		//					else
		//					{
		//						FinalTest.RemoveFromStart(FinalTest.Left(1));
		//						xCounter = 0;
		//					}
		//				}

		//			}

		//			GetTextSize(Vrstice[0], (float&)Velikost.X, (float&)Velikost.Y, HUDFont, FontScale);
		//			FString tricrke;
		//			tricrke = TEXT("xxx");

		//			float LetterSizeX, LetterSizeY;
		//			GetTextSize(tricrke, LetterSizeX, LetterSizeY, HUDFont, FontScale);

		//			/*
		//			float LetterSizeX, LetterSizeY;
		//			GetTextSize("xxx", LetterSizeX, LetterSizeY, HUDFont, FontScale);
		//			*/
		//			////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 70.f, MyColor, FString::FromInt(TooManySpaces));
		//			if (SD.Y * 0.70f < (Vrstice.Num() * Velikost.Y) || TooManySpaces)  //if ((StVrstic < Vrstice.Num()) && )
		//			{
		//				////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("First option if executed") + FString::SanitizeFloat((Vrstice.Num()*Velikost.Y)));
		//				if (FontScale == 0.1f)
		//				{
		//					break;
		//				}
		//				FontScale -= 0.01f;
		//			}
		//			else
		//			{
		//				break;
		//			}
		//		}
		//	}
		//	////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::FromInt(Vrstice.Num()));
		//}

		////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 70.f, MyColor, FString::SanitizeFloat(FontScale));

		//GetTextSize(Vrstice[0], (float&)Velikost.X, (float&)Velikost.Y, HUDFont, FontScale);
		//FLinearColor TheFontColor = FLinearColor(0.287f, 0.25f, 0.25f);
		//DrawText(Vrstica1, TheFontColor, (SD.X - Velikost.X) / 2 , SD.Y/36.0f, HUDFont, FontScale);// (SD.X-Velikost.X)/2
		//calc Y position to centre the text


		

		//if (!bLockedTip)
		//{

		//	float YSize, XSize;
		//	GetTextSize(Vrstice[0], XSize, YSize, HUDFont, FontScale);
		//	YSize = (SD.Y * 0.35f + SD.Y / 36.0f) - (YSize * Vrstice.Num() / 2);
		//	for (int32 i = 0; i < Vrstice.Num(); i++)
		//	{
		//		GetTextSize(Vrstice[i], (float&)Velikost.X, (float&)Velikost.Y, HUDFont, FontScale); //SD.Y/36.0f + Velikost.Y*i
		//		DrawText(Vrstice[i], MyColor, (SD.X - Velikost.X) / 2, YSize + Velikost.Y * i, HUDFont, FontScale);
		//	}
		//}
		//draw green layer background for order display numbers 2/124
		//DrawTexture(GreenLayer, SD.X / 2 - SD.X / 8, SD.Y*0.79f, SD.X / 4, SD.Y*0.15f, 0.0f, 0.0f, 1.0f, 0.23f);
		


		
		//if (UserWidgetTestClass) // make sure you assigned the widget class in editor
		//{
		//	UserWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), UserWidgetTestClass);
		//	if (UserWidgetInstance)
		//	{
		//		UserWidgetInstance->AddToViewport();
		//		//UserWidgetInstance->SetText(NewText);
		//		//UserWidgetInstance->SetToolTipText(FText(TEXT("bfdonsaodfdf")));
		//	}
		//}
		// 
		// 
		//Kazalo
		//DrawTexture(WideButton, SD.X / 2 - SD.X / 8, SD.Y * 0.8f, SD.X / 4, IconSize, 0.0f, 0.0f, 1.0f, 1.0f);

		float ButtonSize = IconSize * 0.8f;
		//float ButtonSizeY = SD.X / 16 - SD.Y * 0.075f
		//draw Home button
		//TODO: tuki ce das Buttons[0] za koordinate povzroci napako, nobene logike... ampk ostali gumbi spodi nizje je pa ok?
		DrawTexture(ButtonColors, IconSize * 0.25f, SD.Y * 0.8f, IconSize, IconSize, Buttons[2].X, Buttons[2].Y, 0.25f, 0.25f);
		DrawTexture(Buttons1, IconSize * 0.25f, SD.Y * 0.8f, IconSize, IconSize, 0.25f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(IconSize * 0.25f, SD.Y * 0.8f), FVector2D(IconSize, IconSize), "Close", false);
	
		DrawTexture(ButtonColors, IconSize * 1.75f, SD.Y * 0.8f, IconSize, IconSize, Buttons[3].X, Buttons[3].Y, 0.25f, 0.25f);
		DrawTexture(Buttons1, IconSize * 1.75f, SD.Y * 0.8f, IconSize, IconSize, 0.5f, 0.75f, 0.25f, 0.25f);
		if (!bSoundOn)
		{
			DrawTexture(Buttons1, IconSize * 1.75f, SD.Y * 0.8f, IconSize, IconSize, 0.75f, 0.75f, 0.25f, 0.25f);
		}
		AddHitBox(FVector2D(IconSize * 1.75f, SD.Y * 0.8f), FVector2D(IconSize, IconSize), "sound", false);
		
		//-10 
		DrawTexture(ButtonColors, IconSize * 3.25f, SD.Y * 0.8f, IconSize, IconSize, Buttons[4].X, Buttons[4].Y, 0.25f, 0.25f);
		DrawTexture(Buttons2, IconSize * 3.25f, SD.Y * 0.8f, IconSize, IconSize, 0.0f, 0.75f, 0.25f, 0.25f);
		AddHitBox(FVector2D(IconSize * 3.25f, SD.Y * 0.8f), FVector2D(IconSize, IconSize), "minusten", false);

		//+10
		DrawTexture(ButtonColors, SD.X - IconSize * 4.25f, SD.Y * 0.8f, IconSize, IconSize, Buttons[1].X, Buttons[1].Y, 0.25f, 0.25f);
		DrawTexture(Buttons2, SD.X - IconSize * 4.25f, SD.Y * 0.8f, IconSize, IconSize, 0.25f, 0.75f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X - IconSize * 4.25f, SD.Y * 0.8f), FVector2D(IconSize, IconSize), "plusten", false);
		//Previous Tip
		DrawTexture(ButtonColors, SD.X - IconSize * 2.75f, SD.Y * 0.8f, IconSize, IconSize, Buttons[5].X, Buttons[5].Y, 0.25f, 0.25f);
		DrawTexture(Buttons2, SD.X - IconSize * 2.75f, SD.Y * 0.8f, IconSize, IconSize, 0.75f, 0.75f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X - IconSize * 2.75f, SD.Y * 0.8f), FVector2D(IconSize, IconSize), "PrevTip", false);
		//load next tip
		DrawTexture(ButtonColors, SD.X - IconSize * 1.25f, SD.Y * 0.8f, IconSize, IconSize, Buttons[6].X, Buttons[6].Y, 0.25f, 0.25f);
		DrawTexture(Buttons2, SD.X - IconSize * 1.25f, SD.Y * 0.8f, IconSize, IconSize, 1.f, 0.75f, -0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X - IconSize * 1.25f, SD.Y * 0.8f), FVector2D(IconSize, IconSize), "NextTip", false);
		//draw library Close button
		//DrawTexture(NextClose, SD.X/8, SD.Y / 8 * 5.9f , SD.X/4, SD.Y/5, 0.5f, 0.75f, 0.5f, 0.25f);
		//AddHitBox(FVector2D(SD.X/8, SD.Y / 8 * 5.9f), FVector2D(SD.X / 4, SD.Y / 5), "Close", false); 
		//draw library NextTip button
		//DrawTexture(NextClose, SD.X / 8*5, SD.Y / 8 * 5.9f, SD.X / 4, SD.Y / 5, 0.0f, 0.75f, 0.5f, 0.25f);
		//AddHitBox(FVector2D(SD.X / 8*5, SD.Y / 8 * 5.9f), FVector2D(SD.X / 4, SD.Y / 5), "NextTip", false);
		//FString kazalo = FString::FromInt(TipsIndex + 1) + "/121";
		//float Fss = 1.0f;
		////SD.Y/36.0f + Velikost.Y*i
		//for (int32 i = 0; i < 100; i++)
		//{
		//	GetTextSize(kazalo, (float&)Velikost.X, (float&)Velikost.Y, JFont, Fss);
		//	if (Velikost.Y > SD.Y * 0.09f)
		//	{
		//		break;
		//	}
		//	else
		//	{
		//		Fss += 0.01f;
		//	}
		//}
		//for (int32 i = 0; i < 100; i++)
		//{
		//	GetTextSize(kazalo, (float&)Velikost.X, (float&)Velikost.Y, JFont, Fss);
		//	if (Velikost.X < SD.X / 4)
		//	{
		//		break;
		//	}
		//	else
		//	{
		//		Fss -= 0.01f;
		//	}
		//}
		//DrawText(kazalo, FLinearColor(0.03f, 0.03f, 0.03f), (SD.X - Velikost.X) / 2, SD.Y * 0.88f - Velikost.Y / 2, JFont, Fss);
		////SD.Y*0.875f + SD.Y*0.075f
		////DrawTexture(GreenLayer, SD.X / 2 - SD.X / 8, SD.Y*0.825f, SD.X / 4, SD.Y*0.10f, 0.0f, 0.0f, 1.0f, 1.0f);

	}

	//else if (bTransitionHitBox)
	//{
	//	AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
	//}
	else if (bDrawCredits)
	{
		if (bDrawCreditsNames)
		{
			//DrawTexture(GreenLayer, SD.X / 4, 0.0f, SD.X / 2, SD.X / 2, 0.0f, 0.0f, 1.0f, 1.0f);
			//DrawTexture(GreenLayer, SD.X / 4, 0.0f, SD.X / 2, SD.X / 2, 0.0f, 0.0f, 1.0f, 1.0f);
			DrawTexture(CreditsText, SD.X / 4, 0.0f, SD.X / 2, SD.X / 2, 0.0f, 0.0f, 1.0f, 1.0f);
			/*
			FVector2D Velik;
			FString Credits = TEXT("Game by Jurij Gantar");
			GetTextSize(Credits, Velik.X, Velik.Y, HUDFont, FontScale*0.9f);
			DrawText(Credits, MyColor, (SD.X - Velik.X) / 2, SD.Y/4, HUDFont, FontScale*0.9f); // -(Velik.Y / 2)

			Credits = TEXT("Vector art by Tina Poljanšek");
			GetTextSize(Credits, Velik.X, Velik.Y, HUDFont, FontScale*0.9f);
			DrawText(Credits, MyColor, (SD.X - Velik.X) / 2, SD.Y / 4 + Velik.Y, HUDFont, FontScale*0.9f); // -(Velik.Y / 2)

			Credits = TEXT("Music by Nicole Marie T");
			GetTextSize(Credits, Velik.X, Velik.Y, HUDFont, FontScale*0.9f);
			DrawText(Credits, MyColor, (SD.X - Velik.X) / 2, SD.Y / 4 + Velik.Y *2.0f, HUDFont, FontScale*0.9f); // -(Velik.Y / 2)

			Credits = TEXT("Sound FX by Jan Stagličić");
			GetTextSize(Credits, Velik.X, Velik.Y, HUDFont, FontScale*0.9f);
			DrawText(Credits, MyColor, (SD.X - Velik.X) / 2, SD.Y / 4 + Velik.Y *3.0f, HUDFont, FontScale*0.9f); // -(Velik.Y / 2)

			Credits = TEXT("Translations:");
			GetTextSize(Credits, Velik.X, Velik.Y, HUDFont, FontScale*0.9f);
			DrawText(Credits, MyColor, (SD.X - Velik.X) / 2, SD.Y / 4 + Velik.Y *4.0f, HUDFont, FontScale*0.9f); // -(Velik.Y / 2)
			Credits = TEXT("Zhihao Lin 林志豪");
			GetTextSize(Credits, Velik.X, Velik.Y, HUDFont, FontScale*0.9f);
			DrawText(Credits, MyColor, (SD.X - Velik.X) / 2, SD.Y / 4 + Velik.Y *5.0f, HUDFont, FontScale*0.9f); // -(Velik.Y / 2)
			Credits = TEXT("Lovro Gantar");
			GetTextSize(Credits, Velik.X, Velik.Y, HUDFont, FontScale*0.9f);
			DrawText(Credits, MyColor, (SD.X - Velik.X) / 2, SD.Y / 4 + Velik.Y *6.0f, HUDFont, FontScale*0.9f); // -(Velik.Y / 2)
			Credits = TEXT("Copyright 2011-2017 by Jurij Gantar");
			GetTextSize(Credits, Velik.X, Velik.Y, HUDFont, FontScale*0.9f);
			DrawText(Credits, MyColor, (SD.X - Velik.X) / 2, SD.Y / 4, HUDFont, FontScale*0.5f); // -(Velik.Y / 2)
			Credits = TEXT("All Rights Reserved");
			GetTextSize(Credits, Velik.X, Velik.Y, HUDFont, FontScale*0.9f);
			DrawText(Credits, MyColor, (SD.X - Velik.X) / 2, SD.Y / 4, HUDFont, FontScale*0.5f); // -(Velik.Y / 2)
			*/

			//GetTextSize(Loading, Velik.X, Velik.Y, HUDFont, FontScale);
			//DrawText(Loading, MyColor, (SD.X - Velik.X) / 2, (SD.Y - Velik.Y) / 2, HUDFont, FontScale);

			/*
			DrawTexture(GreenLayer, 0.0f, 0.0f, SD.X, SD.Y, 0.0f, 0.25f, 1.0f, 0.75f);
			DrawTexture(CreditsText, 0.0f, 0.0f, SD.X / 2 , SD.X / 2, 0.0f, 0.25f, 1.0f, 0.75f);*/
		}
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "CreditsHitBox", false); //empty hit box so we dont click anything in the level

	}
	else if (bDrawAreYouSure)
	{
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		//draw green background , copied from pause menu
		//FVector2D IconHitBox = FVector2D(IconSize, IconSize);
		FVector2D BackgroundPos = FVector2D(float(SD.X / 2) - (SD.X / 16 * 3.5), float((SD.X / 2 / 2.7f) - (SD.X / 16 * 10 / 5)));
		//DrawTexture(GreenLayer, SD.X/4, SD.Y/2 - SD.X / 16, SD.X / 2, SD.X / 8, 0.0f, 0.0f, 1.0f, 0.23f);
		DrawTexture(GreenLayer, SD.X * 0.05f, SD.X * 0.1f, SD.X * 0.9f, SD.Y - SD.X * 0.2f, 0.0f, 0.25f, 1.0f, 0.75f);
		//		DrawText("Reset Game Data ??", FColor::Yellow, 50, 50, HUDFont);
		float tempfontsiz = 1.0;
		FVector2D QuestionTextSize;
		FString beseda = ScreenTexts[10];// TEXT("Reset Game Data ??")
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X > SD.X / 2 * 0.98f)
			{
				tempfontsiz -= 0.01f;
			}
			else
			{
				break;
			}
		}
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X < SD.X / 2 * 0.85f)
			{
				tempfontsiz += 0.01f;
			}
			else
			{
				break;
			}
		}
		//DrawText(beseda,MyColor, (SD.X - QuestionTextSize.X) / 2.0f,	(SD.Y - QuestionTextSize.Y) / 2.0f, HUDFont, tempfontsiz);
		DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 0.75f, HUDFont, tempfontsiz);
		//buttons yes and no , copied from library
		//DrawTexture(Buttons2, SD.X / 8, SD.Y / 8 * 5.9f, SD.X / 4, SD.Y / 5, 0.25f, 0.0f, 0.25f, 0.25f);
		/*
		DrawTexture(Buttons2, SD.X / 4, SD.Y / 2 + SD.X / 12 , SD.X / 8, SD.X / 8, 0.25f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X / 4, SD.Y / 2 + SD.X / 12), FVector2D(SD.X / 8, SD.X / 8), "No", false);
		//draw library NextTip button
		DrawTexture(Buttons2, SD.X - SD.X/4 - SD.X/8, SD.Y / 2 + SD.X / 12, SD.X / 8, SD.X / 8, 0.5f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X - SD.X / 4 - SD.X / 8, SD.Y / 2 + SD.X / 12), FVector2D(SD.X / 8, SD.X / 8), "Yes", false);
		*/

		FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
		float IconYPos = SD.X * 0.1f + (SD.Y - SD.X * 0.2f) * 0.75f - IconSizeR.X / 2;
		DrawTexture(Buttons2, SD.X * 0.25f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.25f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.25f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "No", false);

		DrawTexture(Buttons2, SD.X * 0.75f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.5f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.75f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "Yes", false);

	}
	/*
	else if (bDrawAreYouSure)
	{
	AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
	//draw green background , copied from pause menu
	//FVector2D IconHitBox = FVector2D(IconSize, IconSize);
	FVector2D BackgroundPos = FVector2D(float(SD.X / 2) - (SD.X / 16 * 3.5), float((SD.X / 2 / 2.7f) - (SD.X / 16 * 10 / 5)));
	DrawTexture(GreenLayer, SD.X/4, SD.Y/2 - SD.X / 16, SD.X / 2, SD.X / 8, 0.0f, 0.0f, 1.0f, 0.23f);

	//		DrawText("Reset Game Data ??", FColor::Yellow, 50, 50, HUDFont);
	float tempfontsiz = 1.0;
	FVector2D QuestionTextSize;
	FString beseda = ScreenTexts[10];// TEXT("Reset Game Data ??")
	for (int32 i = 0; i < 100; i++)
	{
	GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont , tempfontsiz);
	if (QuestionTextSize.X > SD.X/2 * 0.98f)
	{
	tempfontsiz -= 0.01f;
	}
	else
	{
	break;
	}
	}
	for (int32 i = 0; i < 100; i++)
	{
	GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
	if (QuestionTextSize.X < SD.X / 2 * 0.85f)
	{
	tempfontsiz += 0.01f;
	}
	else
	{
	break;
	}
	}
	DrawText(beseda,MyColor, (SD.X - QuestionTextSize.X) / 2.0f,	(SD.Y - QuestionTextSize.Y) / 2.0f, HUDFont, tempfontsiz);
	//buttons yes and no , copied from library
	//DrawTexture(Buttons2, SD.X / 8, SD.Y / 8 * 5.9f, SD.X / 4, SD.Y / 5, 0.25f, 0.0f, 0.25f, 0.25f);
	DrawTexture(Buttons2, SD.X / 4, SD.Y / 2 + SD.X / 12 , SD.X / 8, SD.X / 8, 0.25f, 0.0f, 0.25f, 0.25f);
	AddHitBox(FVector2D(SD.X / 4, SD.Y / 2 + SD.X / 12), FVector2D(SD.X / 8, SD.X / 8), "No", false);
	//draw library NextTip button
	DrawTexture(Buttons2, SD.X - SD.X/4 - SD.X/8, SD.Y / 2 + SD.X / 12, SD.X / 8, SD.X / 8, 0.5f, 0.0f, 0.25f, 0.25f);
	AddHitBox(FVector2D(SD.X - SD.X / 4 - SD.X / 8, SD.Y / 2 + SD.X / 12), FVector2D(SD.X / 8, SD.X / 8), "Yes", false);

	}
	*/
	else if (bDrawAreYouAbsSure)
	{
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false);
		//DrawTexture(GreenLayer, SD.X / 4, SD.Y / 2 - SD.X / 16, SD.X / 2, SD.X / 8, 0.0f, 0.0f, 1.0f, 1.0f);
		//DrawTexture(GreenLayer, SD.X / 4, SD.Y / 2 - SD.X / 16, SD.X / 2, SD.X / 8, 0.0f, 0.0f, 1.0f, 0.23f);
		DrawTexture(GreenLayer, SD.X * 0.05f, SD.X * 0.1f, SD.X * 0.9f, SD.Y - SD.X * 0.2f, 0.0f, 0.25f, 1.0f, 0.75f);
		float tempfontsiz = 1.0;
		FVector2D QuestionTextSize;
		FString beseda = ScreenTexts[11];// TEXT("Reset Game Data ??")
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X > SD.X / 2 * 0.98f)
			{
				tempfontsiz -= 0.01f;
			}
			else
			{
				break;
			}
		}
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X < SD.X / 2 * 0.85f)
			{
				tempfontsiz += 0.01f;
			}
			else
			{
				break;
			}
		}
		DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 0.75f, HUDFont, tempfontsiz);
		//DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, (SD.Y - QuestionTextSize.Y) / 2.0f, HUDFont, tempfontsiz);
		//buttons yes and no
		/*
		DrawTexture(Buttons2, SD.X / 4, SD.Y / 2 + SD.X / 12, SD.X / 8, SD.X / 8, 0.25f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X / 4, SD.Y / 2 + SD.X / 12), FVector2D(SD.X / 8, SD.X / 8), "No", false);

		DrawTexture(Buttons2, SD.X - SD.X / 4 - SD.X / 8, SD.Y / 2 + SD.X / 12, SD.X / 8, SD.X / 8, 0.5f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X - SD.X / 4 - SD.X / 8, SD.Y / 2 + SD.X / 12), FVector2D(SD.X / 8, SD.X / 8), "Yes", false);
		*/
		FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
		float IconYPos = SD.X * 0.1f + (SD.Y - SD.X * 0.2f) * 0.75f - IconSizeR.X / 2;
		DrawTexture(Buttons2, SD.X * 0.25f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.25f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.25f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "No", false);

		DrawTexture(Buttons2, SD.X * 0.75f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.5f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.75f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "Yes", false);

	}
	else if (bShowLangSel)
	{
		float PosX = SD.X / 4.0f;
		float PosY = (SD.Y - (SD.X / 2.0f)) / 2.0f;
		DrawTexture(Flags, PosX, PosY, SD.X / 2.0f, SD.X / 8.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		FVector2D FlagSize = FVector2D(SD.X / 8.0f, SD.X / 6.0f / 2.0f);
		for (int32 i = 0; i < 4; i++) //Change to 3 to remove chinese option for (int32 i = 0; i < 24; i++) 
		{
			AddHitBox(FVector2D(PosX, PosY), FlagSize, FName(*FString::FromInt(i)), false);
			if (i == 3 || i == 7 || i == 11 || i == 15 || i == 19) { PosY += FlagSize.Y; PosX = SD.X / 4.0f; }
			else { PosX += FlagSize.X; }
		}
	}
	else if (bShowChineseSel)
	{
		DrawTexture(ChinaLangSel, SD.X / 2 - (SD.Y / 4 * 1.5f), SD.Y / 4, SD.Y / 4, SD.Y / 2, 0.0f, 0.0f, 0.5f, 1.0f);
		AddHitBox(FVector2D(SD.X / 2 - (SD.Y / 4 * 1.5f), SD.Y / 4), FVector2D(SD.Y / 4, SD.Y / 2), "Tradi", false);
		DrawTexture(ChinaLangSel, SD.X / 2 + (SD.Y / 4 * 0.5f), SD.Y / 4, SD.Y / 4, SD.Y / 2, 0.5f, 0.0f, 0.5f, 1.0f);
		AddHitBox(FVector2D(SD.X / 2 + (SD.Y / 4 * 0.5f), SD.Y / 4), FVector2D(SD.Y / 4, SD.Y / 2), "Simpl", false);
	}
	else if (bDrawShareImage)
	{
		FrameCount++;
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false);
		DrawTexture(GreenLayer, SD.X / 4, SD.Y / 4, SD.X / 2, SD.Y / 2, 0.0f, 0.25f, 1.0f, 0.75f);

		//DrawTexture(GreenLayer, SD.X / 2, SD.Y / 2, SD.X / 4, SD.Y / 4, 0.0f, 0.0f, 1.0f, 1.0f);
		//DrawTexture(GreenLayer, SD.X / 2, SD.Y / 2, SD.X / 4, SD.Y / 4, 0.0f, 0.0f, 1.0f, 1.0f);

		FVector2D Velik;
		//FString FacebookShareText = ;
		//FacebookShareText.Reset();
		if (FrameCount % 15 == 0)
		{
			FacebookShareText.Append(TEXT("."));
		}
		if (FrameCount > 104)
		{
			FrameCount = 0;
			FacebookShareText.Reset();
		}
		//FacebookShareText.Append(TEXT("Sending Image To Facebook..."));
		FString Teststr;
		Teststr.Append(TEXT("......"));
		GetTextSize(Teststr, (float&)Velik.X, (float&)Velik.Y, HUDFont, FontScale);
		DrawText(FacebookShareText, MyColor, (SD.X - Velik.X) / 2, SD.Y / 2 - Velik.Y * 0.7f, HUDFont, FontScale);

		//DrawTexture(Buttons2, (SD.X + Velik.X) / 2, (SD.Y - Velik.Y) / 2, SD.X/12, SD.X / 12, 0.0f, 0.0f, 0.25f, 0.25f);
		//DrawTexture(Buttons1, (SD.X - Velik.X) / 2 - SD.X / 12, (SD.Y - Velik.Y) / 2, SD.X/12, SD.X / 12, 0.5f, 0.25f, 0.25f, 0.25f);
		if (ImagePosted)
		{
			bDrawShareImage = false;
			ImagePosted = false;
		}
	}
	else if (bLevelFailed)
	{
		
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		DrawTexture(GreenLayer, SD.X / 2 - SD.X / 16 * 5, SD.X / 2 / 2.9f, SD.X / 16 * 10, SD.X / 16 * 4, 0.0f, 0.25f, 1.0f, 0.75f);
		float FontSizze = 1.2f;
		FVector2D GameWonTextSize;
		int32 aewf; int32 TypeNmbr;
		if (CurrentLevel < 100) { aewf = CurrentLevel;	TypeNmbr = 1; }
		else if (CurrentLevel < 200) { aewf = CurrentLevel - 100; TypeNmbr = 2; }
		else if (CurrentLevel < 300) { TypeNmbr = 3; aewf = CurrentLevel - 200; }
		else { aewf = CurrentLevel - 300; TypeNmbr = 4; }
		//	FString LvlNmb = FString::FromInt(CurrentLevel);
		FString LevComp = (ScreenTexts[0] + FString::FromInt(TypeNmbr) + (TEXT(" - ") + FString::FromInt(aewf) + ScreenTexts[1]));// ("  Failed")));
		GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze);

		for (int32 i = 0; i < 70; i++)
		{
			if (GameWonTextSize.X > SD.X / 1.8f)
			{
				FontSizze -= 0.01f;
				GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze);
			}
			else { break; }
		}
		DrawText(LevComp, MyColor, (SD.X - GameWonTextSize.X) / 2.0f, SD.X / 5, HUDFont, FontSizze);

		FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
		float IconYPos = SD.X / 16 * 8 / 2 + IconSizeR.X / 3; //SD.X * 3 / 8

		DrawTexture(HUDbuttons1b, (SD.X / 16 * 8 - SD.X / 16 * 10 / 2) + SD.X / 16 * 10 / 6 - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.25f, 0.75f, 0.25f, 0.25f);
		AddHitBox(FVector2D((SD.X / 16 * 8 - SD.X / 16 * 10 / 2) + SD.X / 16 * 10 / 6 - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "LevelSelect", false);

		DrawTexture(HUDbuttons1b, SD.X / 16 * 8 - SD.X / 18, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.0f, 0.25f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X / 16 * 8 - SD.X / 18, IconYPos), IconSizeR, "Restart", false);

		//Next Level button
		if (!UnlockedArray[CurrentLevel] && !(CurrentLevel == 320))
		{
			DrawTexture(HUDbuttons1b, (SD.X / 16 * 8 + SD.X / 16 * 10 / 2) - SD.X / 16 * 10 / 6 * 2 + IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.0f, 0.75f, 0.25f, 0.25f);
			AddHitBox(FVector2D((SD.X / 16 * 8 + SD.X / 16 * 10 / 2) - SD.X / 16 * 10 / 6 * 2 + IconSizeR.X / 2.0f, IconYPos), IconSizeR, "NextLevel", false);
		}
		else
		{
			DrawTexture(HUDbuttons1b, (SD.X / 16 * 8 + SD.X / 16 * 10 / 2) - SD.X / 16 * 10 / 6 * 2 + IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.5f, 0.5f, 0.25f, 0.25f);
		}

		////////////////////////////////////////////////////////
		/*
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		DrawTexture(GreenLayer, SD.X / 16 * 8 - SD.X / 16 * 10 / 2, SD.X / 16 * 8 / 2 , SD.X / 16 * 10, SD.X / 16*4, 0.0f, 0.0f, 1.0f, 1.0f);

		FVector2D IconSizeR(FVector2D (SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
		//restart button
		DrawTexture(Buttons1, SD.X / 16 * 8 - SD.X/18 , SD.X / 16 * 8 / 2 + SD.X / 8 , (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.0f, 0.25f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X / 16 * 8 - SD.X / 18, SD.X *3 /8 ), IconSizeR, "Restart", false);

		//Next Level button
		if (!UnlockedArray[CurrentLevel])
		{
		DrawTexture(Buttons1, (SD.X / 16 * 8 + SD.X / 16 * 10 / 2) - SD.X / 16 * 10 / 6 * 2, SD.X / 16 * 8 / 2 + SD.X / 8, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.0f, 0.75f, 0.25f, 0.25f);
		AddHitBox(FVector2D((SD.X / 16 * 8 + SD.X / 16 * 10 / 2) - SD.X / 16 * 10 / 6 * 2, SD.X * 3 / 8), IconSizeR, "NextLevel", false);
		}
		else
		{
		DrawTexture(Buttons1, (SD.X / 16 * 8 + SD.X / 16 * 10 / 2) - SD.X / 16 * 10 / 6 * 2, SD.X / 16 * 8 / 2 + SD.X / 8, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.5f, 0.5f, 0.25f, 0.25f);
		}

		//Level Select button
		DrawTexture(Buttons1, (SD.X / 16 * 8 - SD.X / 16 * 10 / 2) + SD.X / 16 * 10 / 6, SD.X / 16 * 8 / 2 + SD.X / 8, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.25f, 0.75f, 0.25f, 0.25f);
		AddHitBox(FVector2D((SD.X / 16 * 8 - SD.X / 16 * 10 / 2) + SD.X / 16 * 10 / 6, SD.X * 3 / 8), IconSizeR, "LevelSelect", false);*/
	}
	/*
	else if (bAchievementUnlocked)
	{
	AddHitBox(FVector2D(0.0f, 0.0f), SD, "AchievementBox", false, 0); //empty hit box so we dont click anything in the level
	DrawTexture(GreenLayer, SD.X / 16 * 8 - SD.X / 16 * 10 / 2, SD.X / 16 * 8 / 2.9f, SD.X / 16 * 10, SD.X / 16 * 4, 0.0f, 0.0f, 1.0f, 1.0f);
	AddHitBox(FVector2D(SD.X / 16 * 8 - SD.X / 16 * 10 / 2, SD.X / 16 * 8 / 2.9f), FVector2D(SD.X / 16 * 10, SD.X / 16 * 4), "AchievementClicked", true, 1);

	FVector2D GameWonTextSize;
	int32 aewf; int32 TypeNmbr;
	if (CurrentLevel < 100) { aewf = CurrentLevel;	TypeNmbr = 1; }
	else if (CurrentLevel < 200) { aewf = CurrentLevel - 100; TypeNmbr = 2; }
	else if (CurrentLevel < 300) { TypeNmbr = 3; aewf = CurrentLevel - 200; }
	else { aewf = CurrentLevel - 300; TypeNmbr = 4; }
	//	FString LvlNmb = FString::FromInt(CurrentLevel);
	FString LevComp = (TEXT("Achievement Unlocked: "));
	GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, 1.2f);
	DrawText(LevComp, MyColor, (SD.X - GameWonTextSize.X) / 2.0f, SD.X / 5, HUDFont, 1.2f);

	FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 7, SD.X / 16 * 10 / 7));

	//	FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
	float IconYPos = SD.X / 16 * 8 / 2 + IconSizeR.X / 3; //SD.X * 3 / 8

	LevComp = AchievementsList[AchIndex];
	GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, 1.0f);
	DrawText(LevComp, MyColor, (SD.X - GameWonTextSize.X) / 2.0f, IconYPos + IconSizeR.X / 2.0f - GameWonTextSize.Y / 2.0f, HUDFont, 1.0f);
	//AddHitBox(FVector2D((SD.X / 16 * 8 - SD.X / 16 * 10 / 2) + SD.X / 16 * 10 / 6, IconYPos), IconSizeR, "LevelSelect", false);

	float XPoss = (SD.X / 16 * 8 - SD.X / 16 * 10 / 2) + SD.X / 16 * 10 / 6 - IconSizeR.X/2.0f;
	float UVSx = 0.0f;
	float UVSy = 0.5f;
	float UVSize = 0.25f;
	//	UTexture2D* Teex= Achievements;
	switch (AchIndex)
	{
	case 0:UVSx = 0.0f; UVSy = 0.0f; break;
	case 1:UVSx = 0.25f; UVSy = 0.0f; break;
	case 2:UVSx = 0.5f; UVSy = 0.0f; break;
	case 3:UVSx = 0.75f; UVSy = 0.0f; break;
	case 4:UVSx = 0.0f; UVSy = 0.25f; break;
	case 5:UVSx = 0.25f; UVSy = 0.25f; break;
	case 6:UVSx = 0.5f; UVSy = 0.25f; break;
	case 7:UVSx = 0.75f; UVSy = 0.25f; break;
	case 8:UVSx = 0.0f; UVSy = 0.5f; break;
	case 9:UVSx = 0.25f; UVSy = 0.5f; break;
	case 10:UVSx = 0.5f; UVSy = 0.5f; break;
	case 11:UVSx = 0.75f; UVSy = 0.5f; break;
	case 12:UVSx = 0.0f; UVSy = 0.75f; break;
	case 13:UVSx = 0.25f; UVSy = 0.75f; break;
	case 14:UVSx = 0.5f; UVSy = 0.75f; break;
	case 15:UVSx = 0.75f; UVSy = 0.75f; break;
	default:break;
	}
	DrawTexture(Achievements, XPoss, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, UVSx, UVSy, UVSize, UVSize);

	}
	*/
	else if (bLevelWon)
	{

		
		float FontSizze = 1.2f;
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false, 0); //empty hit box so we dont click anything in the level
		DrawTexture(GreenLayer, SD.X / 8, SD.X / 12, 6 * SD.X / 8, SD.X / 2 - SD.X / 8, 0.0f, 0.25f, 1.0f, 0.75f);

		// draw Level completed Text
		FVector2D GameWonTextSize;
		int32 aewf; int32 TypeNmbr;
		if (CurrentLevel < 100) { aewf = CurrentLevel;	TypeNmbr = 1; }
		else if (CurrentLevel < 200) { aewf = CurrentLevel - 100; TypeNmbr = 2; }
		else if (CurrentLevel < 300) { TypeNmbr = 3; aewf = CurrentLevel - 200; }
		else { aewf = CurrentLevel - 300; TypeNmbr = 4; }
		//	FString LvlNmb = FString::FromInt(CurrentLevel);
		FString LevComp = (ScreenTexts[0] + FString::FromInt(TypeNmbr) + (TEXT(" - ") + FString::FromInt(aewf) + ScreenTexts[2]));
		GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze);

		//if(bAdjustText)
		//{
		//bAdjustText = false;
		for (int32 i = 0; i < 70; i++)
		{
			if (GameWonTextSize.X > SD.X / 1.8f)
			{
				FontSizze -= 0.01f;
				GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze);
			}
			else { break; }
		}
		//now check if the up and down space is less then 0.42 * SD.Y, meaning 42% of height
		float velikostY = GameWonTextSize.Y + 4 * (GameWonTextSize.Y * 0.75f);
		for (int32 i = 0; i < 70; i++)
		{
			if (velikostY > SD.Y * 0.42f)
			{
				FontSizze -= 0.01f;
				GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze);
				velikostY = GameWonTextSize.Y + 4 * (GameWonTextSize.Y * 0.75f);
			}
			else if (velikostY < SD.Y * 0.38f)
			{
				FontSizze += 0.01f;
				GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze);
				velikostY = GameWonTextSize.Y + 4 * (GameWonTextSize.Y * 0.75f);
			}
			else { break; }
		}
		//}
		//FLinearColor MyColor = FLinearColor(0.287f, 0.25f, 0.25f);
		DrawText(LevComp, MyColor, (SD.X - GameWonTextSize.X) / 2.0f, SD.X / 11, HUDFont, FontSizze);

		// draw Level Score text
		//LevComp = (TEXT("Level Score:      ") + FString::FromInt(Score) );
		LevComp = (TEXT("123456789"));
		GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze * 0.75f);
		float distnc = GameWonTextSize.X;
		LevComp = ScreenTexts[4];//(TEXT("Level Score:"));
		GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze * 0.75f);
		float TextDist = GameWonTextSize.X;

		//LevComp = (TEXT("Level Score:"));
		//GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, 0.9f);
		DrawText(LevComp, MyColor, (SD.X / 2 - TextDist), SD.X / 11 + GameWonTextSize.Y + SD.X / 60, HUDFont, FontSizze * 0.75f);

		LevComp = (FString::FromInt(Score));
		GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze * 0.75f);
		DrawText(LevComp, MyColor, (SD.X / 2 + distnc - GameWonTextSize.X), SD.X / 11 + GameWonTextSize.Y + SD.X / 60, HUDFont, FontSizze * 0.75f);

		// draw bonus time score text
		//int32 TempScore = (TimeLimitsArray[CurrentLevel] - PlayTime ) * 17;

		//LevComp = ScreenTexts[5];//(TEXT("Time Bonus:") );
		//GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze * 0.75f);
		//DrawText(LevComp, MyColor, (SD.X / 2.0f - GameWonTextSize.X), SD.X / 11 + GameWonTextSize.Y * 2 + SD.X / 60, HUDFont, FontSizze * 0.75f);
		//LevComp = FString::FromInt(TimeBonus);
		//GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze * 0.75f);
		//DrawText(LevComp, MyColor, (SD.X / 2.0f - GameWonTextSize.X + distnc), SD.X / 11 + GameWonTextSize.Y * 2 + SD.X / 60, HUDFont, FontSizze * 0.75f);

		//// draw Total Score text
		//LevComp = ScreenTexts[6];//(TEXT("Total Score:"));
		//GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze * 0.75f);
		//DrawText(LevComp, MyColor, (SD.X / 2.0f - GameWonTextSize.X), SD.X / 11 + GameWonTextSize.Y * 3 + SD.X / 60, HUDFont, FontSizze * 0.75f);
		//int32 totalsc = (TimeBonus + Score);
		//LevComp = FString::FromInt(totalsc);
		//GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze * 0.75f);
		//DrawText(LevComp, MyColor, (SD.X / 2.0f - GameWonTextSize.X + distnc), SD.X / 11 + GameWonTextSize.Y * 3 + SD.X / 60, HUDFont, FontSizze * 0.75f);

		//float Widtt = OneStar->GetSizeX() *0.25;
		//UTexture2D* stars;
		FVector2D StarsUVPos;
		if (Score > HS3StarsLimitArray[CurrentLevel]) //if total score is higher than the three stars limit
		{
			//stars = ThreeStars;
			StarsUVPos = FVector2D(0.0f, 0.0f);
			///StarsUVPos = FVector2D(0.0f, 00 );
			StarsNumb = 3;
		}
		else if (Score > HS2StarsLimitArray[CurrentLevel])//if total score is higher than the two stars limit
		{
			//stars = TwoStars;
			StarsUVPos = FVector2D(0.0f, 0.333333f); StarsNumb = 2;
		}
		else {
			StarsUVPos = FVector2D(0.0f, 0.666666f); StarsNumb = 1;
		}// we only get one star
		DrawTexture(Stars, (SD.X / 2.0f - GameWonTextSize.Y * 2.8f + distnc), SD.X / 11 + GameWonTextSize.Y * 4 + SD.X / 60, GameWonTextSize.Y * 3.0f, GameWonTextSize.Y, StarsUVPos.X, StarsUVPos.Y, 1.0f, 0.333333f);
		//DrawTexture(OneStar, (SD.X / 2.0f + distnc - Widtt), SD.X / 11 + GameWonTextSize.Y * 4 + SD.X / 60, GameWonTextSize.Y * 3, GameWonTextSize.Y, 0.0f, 0.0f, 0.75f, 0.25f);

		// draw Rating text
		LevComp = ScreenTexts[7];// (TEXT("Rating:"));// +FString::FromInt(Score));
		GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, FontSizze * 0.75f);
		DrawText(LevComp, MyColor, (SD.X / 2.0f - GameWonTextSize.X), SD.X / 11 + GameWonTextSize.Y * 4 + SD.X / 60, HUDFont, FontSizze * 0.75f);
		// draw Rating Stars
		//GetSizeX()
		FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 7, SD.X / 16 * 10 / 7));
		float LayerSizeX = SD.X * 6 / 8;
		FVector2D IconSize2 = FVector2D(LayerSizeX / 8, LayerSizeX / 8);
		float Presledek = 3 * SD.X / 16;
		float PosX = SD.X / 8 + Presledek / 2 - IconSizeR.X / 2;
		float PosY = SD.X / 12 + (SD.X / 2 - SD.X / 8) - IconSize2.X * 1.25f;
		//highscore stamp
		//if(new highscore)
		//DrawTexture(Buttons2, PosX + 3 * Presledek - GameWonTextSize.Y/2, SD.X / 11 + GameWonTextSize.Y * 2 , (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.0f, 0.5f, 0.25f, 0.25f);
		if (Score > HighScoreArray[CurrentLevel])
		{
			DrawTexture(HUDbuttons1b, SD.X / 8 + LayerSizeX - IconSize2.X * 1.75f, PosY - IconSize2.X * 1.6f, IconSize2.X, IconSize2.Y, 0.5f, 0.25f, 0.25f, 0.25f);
		}
		//float PosY = SD.X / 11 + GameWonTextSize.Y * 5.6f ;
		//SD.X / 2 - SD.X / 4
		//float PosY = SD.X / 2 - SD.X / 6; // IconSizeR.X;

		//draw facebook share button
		//DrawTexture(HUDbuttons1b, SD.X / 8 + IconSize2.X / 2.0f, PosY, IconSize2.X, IconSize2.X, 0.25f, 0.25f, 0.25f, 0.25f);
		//restart button
		DrawTexture(HUDbuttons1b, SD.X / 8 + LayerSizeX / 2 + IconSize2.X / 2.0f, PosY, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.0f, 0.25f, 0.25f, 0.25f);
		//Level Select button
		DrawTexture(HUDbuttons1b, SD.X / 8 + LayerSizeX / 4 + IconSize2.X / 2.0f, PosY, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.25f, 0.75f, 0.25f, 0.25f);
		//if(!bAchievementUnlocked && !bNewLevUnlocked && !BlockClicks)
		//{
		if (!bAchievementUnlocked && !bBlockClicks)
		{
			//AddHitBox(FVector2D(SD.X / 8 + IconSize2.X / 2.0f, PosY), IconSize2, "FacebookShare", false, 1);
			AddHitBox(FVector2D(SD.X / 8 + LayerSizeX / 2 + IconSize2.X / 2.0f, PosY), IconSizeR, "Restart", false, 1);
			AddHitBox(FVector2D(SD.X / 8 + LayerSizeX / 4 + IconSize2.X / 2.0f, PosY), IconSizeR, "LevelSelect", false, 1);
		}
		//Next Level button
		if (!UnlockedArray[CurrentLevel] && !(CurrentLevel == 320))
		{
			DrawTexture(HUDbuttons1b, SD.X / 8 + LayerSizeX - IconSize2.X * 1.5f, PosY, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.0f, 0.75f, 0.25f, 0.25f);
			if (!bAchievementUnlocked && !bBlockClicks)
			{
				AddHitBox(FVector2D(SD.X / 8 + LayerSizeX - IconSize2.X * 1.5f, PosY), IconSizeR, "NextLevel", false, 1);
			}
		}
		else
		{
			DrawTexture(HUDbuttons1b, SD.X / 8 + LayerSizeX - IconSize2.X * 1.5f, PosY, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.5f, 0.5f, 0.25f, 0.25f);
		}


		float FontForTime = 1.4f;
		/*FString TimeCount;
		int32 ttt = PlayTime;
		if (ttt > 59)
		{
			int32 mins = ttt / 60;
			int32 secs = ttt % 60;

			TimeCount = FString::FromInt(mins) + TEXT(":") + FString::FromInt(secs);
		}
		else
		{
			TimeCount = FString::FromInt(ttt);
		}
		FVector2D TimeTextSize;
		GetTextSize(TimeCount, (float&)TimeTextSize.X, (float&)TimeTextSize.Y, JFont, FontForTime);
		DrawText(TimeCount, MyColorDark, (SD.X - TimeTextSize.X) / 2.0f, 0.0f, JFont, FontForTime);*/

		//Achievements stuff, if unlocked it shows otherwise it doesnt show
		if (bAchievementUnlocked)
		{
			if (bDrawAchBig)
			{
				AddHitBox(FVector2D(0.0f, 0.0f), SD, "WonHitBox", false, 1); //empty hit box so we dont click anything in the level
				FVector2D BoxSize = FVector2D(SD.X / 2, SD.X / 4);
				DrawTexture(GreenLayer, (SD.X / 2 - BoxSize.Y * 1.1f / 2), (SD.Y / 2 - SD.X / 8 * 1.1f), BoxSize.Y * 1.1f, BoxSize.Y * 1.1f, 0.0f, 0.25f, 1.0f, 0.75f);
				DrawTexture(Achievements, SD.X / 2 - BoxSize.Y / 2, SD.Y / 2 - SD.X / 8, BoxSize.Y, BoxSize.Y, AchievUVx, AchievUVy, 0.25f, 0.25f);
				AddHitBox(FVector2D(SD.X / 2 - BoxSize.Y / 2, SD.Y / 2 - SD.X / 8), FVector2D(BoxSize.Y, BoxSize.Y), "AchBigClicked", true, 1);
			}
			else if (bShowNormalAch)
			{
				AddHitBox(FVector2D(0.0f, 0.0f), SD, "WonHitBox", false, 1); //empty hit box so we dont click anything in the level
				FVector2D BoxSize = FVector2D(SD.X / 2, SD.X / 4);
				DrawTexture(GreenLayer, SD.X / 4, SD.Y / 2 - SD.X / 8, BoxSize.X, BoxSize.Y, 0.0f, 0.25f, 1.0f, 0.75f);
				if (!bNewLevUnlocked)
				{
					AddHitBox(FVector2D(SD.X / 4, SD.Y / 2 - SD.X / 8), BoxSize, "AchievementClicked", true, 1);
				}
				float Fntsizz = 1.0f;
				//FString LevComp = (TEXT(" Achievement Unlocked: "));
				LevComp = ScreenTexts[8];
				for (int32 i = 0; i < 100; i++)
				{
					GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, Fntsizz);
					if (GameWonTextSize.X > BoxSize.X * 0.99f)
					{
						Fntsizz -= 0.01f;
					}
					else
					{
						break;
					}
				}
				for (int32 i = 0; i < 100; i++)
				{
					GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, Fntsizz);
					if (GameWonTextSize.X < BoxSize.X * 0.8f)
					{
						Fntsizz += 0.01f;
					}
					else
					{
						break;
					}
				}
				DrawText(LevComp, MyColor, (SD.X / 2.0f - GameWonTextSize.X / 2.0f), SD.Y / 2 - SD.X / 16 - GameWonTextSize.Y / 2, HUDFont, Fntsizz);

				float IconYPos = SD.X / 16 * 8 / 2 + IconSizeR.X / 3; //SD.X * 3 / 8
				//LevComp = AchievementsList[AchIndex] + " ";
				LevComp = AchievTexts[AchIndex] + " ";
				Fntsizz = 1.0f;
				for (int32 i = 0; i < 100; i++)
				{
					GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, Fntsizz);
					if (GameWonTextSize.X > BoxSize.X - IconSizeR.X * 2.05f)
					{
						Fntsizz -= 0.01f;
					}
					else
					{
						break;
					}
				}
				for (int32 i = 0; i < 100; i++)
				{
					GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, Fntsizz);
					if (GameWonTextSize.X < BoxSize.X - IconSizeR.X * 2.25f)
					{
						Fntsizz += 0.01f;
					}
					else
					{
						break;
					}
				}
				DrawText(LevComp, MyColor, SD.X / 4 + IconSizeR.X * 1.8f + (BoxSize.X - IconSizeR.X * 2.0f) / 2 - GameWonTextSize.X / 2, IconYPos + IconSizeR.X / 2.0f - GameWonTextSize.Y / 2.0f, HUDFont, Fntsizz);

				float XPoss = (SD.X / 16 * 8 - SD.X / 16 * 10 / 2) + SD.X / 16 * 10 / 6 - IconSizeR.X / 2.0f;
				DrawTexture(Achievements, XPoss + IconSizeR.X * 0.5f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, AchievUVx, AchievUVy, 0.25f, 0.25f);
				if (!bNewLevUnlocked)
				{
					AddHitBox(FVector2D(XPoss + IconSizeR.X * 0.5f, IconYPos), FVector2D(IconSizeR.X, IconSizeR.Y), "AchEnlarge", true, 2);
				}

			}
			else if (bShowGlobAch)//show global achievements
			{
				AddHitBox(FVector2D(0.0f, 0.0f), SD, "WonHitBox", false, 1); //empty hit box so we dont click anything in the level
				FVector2D BoxSize = FVector2D(SD.X / 2, SD.X / 4);
				DrawTexture(GreenLayer, SD.X / 4, SD.Y / 2 - SD.X / 8, BoxSize.X, BoxSize.Y, 0.0f, 0.25f, 1.0f, 0.75f);
				AddHitBox(FVector2D(SD.X / 4, SD.Y / 2 - SD.X / 8), BoxSize, "AchStCl", true, 1);
				float Fntsizz = 1.0f;
				//FString LevComp = (TEXT(" Achievement Unlocked: "));
				LevComp = ScreenTexts[8];
				for (int32 i = 0; i < 100; i++)
				{
					GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, Fntsizz);
					if (GameWonTextSize.X > BoxSize.X * 0.99f)
					{
						Fntsizz -= 0.01f;
					}
					else
					{
						break;
					}
				}
				for (int32 i = 0; i < 100; i++)
				{
					GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, Fntsizz);
					if (GameWonTextSize.X < BoxSize.X * 0.8f)
					{
						Fntsizz += 0.01f;
					}
					else
					{
						break;
					}
				}
				DrawText(LevComp, MyColor, (SD.X - GameWonTextSize.X) / 2.0f, SD.Y / 2 - SD.X / 16 - GameWonTextSize.Y / 2, HUDFont, Fntsizz);

				float IconYPos = SD.X / 16 * 8 / 2 + IconSizeR.X / 3; //SD.X * 3 / 8
				//LevComp = AchievementsList[GlobAchIndex+12] + " ";
				LevComp = AchievTexts[GlobAchIndex + 12] + " ";
				Fntsizz = 1.0f;
				for (int32 i = 0; i < 100; i++)
				{
					GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, Fntsizz);
					if (GameWonTextSize.X > BoxSize.X - IconSizeR.X * 2.05f)
					{
						Fntsizz -= 0.01f;
					}
					else
					{
						break;
					}
				}
				for (int32 i = 0; i < 100; i++)
				{
					GetTextSize(LevComp, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, Fntsizz);
					if (GameWonTextSize.X < BoxSize.X - IconSizeR.X * 2.25f)
					{
						Fntsizz += 0.01f;
					}
					else
					{
						break;
					}
				}
				DrawText(LevComp, MyColor, SD.X / 4 + IconSizeR.X * 1.8f + (BoxSize.X - IconSizeR.X * 2.0f) / 2 - GameWonTextSize.X / 2, IconYPos + IconSizeR.X / 2.0f - GameWonTextSize.Y / 2.0f, HUDFont, Fntsizz);

				float XPoss = (SD.X / 16 * 8 - SD.X / 16 * 10 / 2) + SD.X / 16 * 10 / 6 - IconSizeR.X / 2.0f;
				DrawTexture(Achievements, XPoss + IconSizeR.X * 0.5f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, AchievUVx, AchievUVy, 0.25f, 0.25f);
				if (!bNewLevUnlocked)
				{
					AddHitBox(FVector2D(XPoss + IconSizeR.X * 0.5f, IconYPos), FVector2D(IconSizeR.X, IconSizeR.Y), "AchEnlarge", true, 2);
				}
			}
		}
		if (bNewLevUnlocked) ///this is for showing "new tip unlocked" " Zanimivost Odklenjena"
		{
			if (bModeUnlocked) // if we unlocked new mode
			{
				AddHitBox(FVector2D(0.0f, 0.0f), SD, "NewLevelHitBox", false, 1); //empty hit box so we dont click anything in the level
				//	FVector2D BoxSize = FVector2D(SD.X / 2, SD.X / 8);
				FVector2D BoxSize = FVector2D(SD.X / 2, SD.X / 4);
				FVector2D PicSize = FVector2D(SD.X / 4, SD.X / 4 / 4 * 3);
				//DrawTexture(GreenLayer, SD.X/2 - , BoxSize.Y, BoxSize.X * 0.9f, BoxSize.Y, 0.0f, 0.25f, 1.0f, 0.75f);
				//AddHitBox(FVector2D(SD.X / 4 + BoxSize.X * 0.05f, SD.Y / 2 - SD.X / 16), FVector2D(BoxSize.X* 0.9f, BoxSize.Y), "LevUnlClickd", true, 1);
				//AddHitBox(FVector2D(float(SD.X / 4), float(SD.X / 8)), BoxTexSize, "Classic", false);
				//DrawTexture(GreenLayer, SD.X / 2 - SD.X / 8, SD.Y / 2 - SD.X / 16 * 1.5f, SD.X / 4, SD.X / 16 * 1.5f, 0.0f, 0.0f, 1.0f, 0.75f);
				DrawTexture(GreenLayer, SD.X / 4, SD.Y / 2 - SD.X / 8, BoxSize.X, BoxSize.Y, 0.0f, 0.25f, 1.0f, 0.75f);
				float XCoord = 0.5f;
				float YCoord = 0.25f;
				if (UnlockedArray[300] == false)
				{
					XCoord = 0.5f;
					YCoord = 0.625f;
				}
				else if (UnlockedArray[200] == false)
				{
					XCoord = 0.0f;
					YCoord = 0.625f;
				}
				/*else
				{
				XCoord = 0.5f;
				YCoord = 0.25f;
				}*/
				DrawTexture(LevelSelectFrontMenu, SD.X / 2 - PicSize.X / 2, SD.Y / 2 - PicSize.Y / 2, PicSize.X, PicSize.Y, XCoord, YCoord, 0.5f, 0.375f);
				AddHitBox(FVector2D(SD.X / 4, SD.Y / 2 - SD.X / 8), BoxSize, "LevUnlClickd", true, 1);
				if (bDrawLock)
				{
					DrawTexture(LockTexture_256, SD.X / 2 - PicSize.Y / 2, SD.Y / 2 - PicSize.Y / 2.25f, PicSize.Y, PicSize.Y, 0.0f, 0.0f, 1.0f, 1.0f);
				}

				//DrawTexture(LevelSelectFrontMenu , SD.X / 2 - SD.X / 8, SD.Y/2 - SD.X / 16 * 1.5f, SD.X / 4, SD.X / 4 * 3, 0.0f, 0.0f, 1.0f, 0.75f);
			}
			else
			{
				AddHitBox(FVector2D(0.0f, 0.0f), SD, "NewLevelHitBox", false, 1); //empty hit box so we dont click anything in the level
				FVector2D BoxSize = FVector2D(SD.X / 2, SD.X / 8);
				//DrawTexture(GreenLayer, SD.X / 4 + BoxSize.X * 0.05f, SD.Y / 2 - SD.X / 16, BoxSize.X * 0.9f, BoxSize.Y, 0.0f, 0.0f, 1.0f, 0.23f);
				DrawTexture(WideButton, SD.X / 4 + BoxSize.X * 0.05f, SD.Y / 2 - SD.X / 16, BoxSize.X * 0.9f, BoxSize.Y, 0.0f, 0.0f, 1.0f, 1.0f);
				AddHitBox(FVector2D(SD.X / 8, SD.X / 12), FVector2D(6 * SD.X / 8, SD.X / 2 - SD.X / 8), "LevUnlClickd", true, 2);
				//AddHitBox(FVector2D(SD.X / 4 + BoxSize.X * 0.05f, SD.Y / 2 - SD.X / 16), FVector2D(BoxSize.X* 0.9f, BoxSize.Y), "LevUnlClickd", true, 1);
				float Fntsizz = 1.0f;
				FString strring = ScreenTexts[9];
				for (int32 i = 0; i < 100; i++)
				{
					GetTextSize(strring, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, Fntsizz);
					if (GameWonTextSize.X < BoxSize.X * 0.65f)
					{
						Fntsizz += 0.01f;
					}
					else
					{
						break;
					}
				}
				for (int32 i = 0; i < 100; i++)
				{
					GetTextSize(strring, (float&)GameWonTextSize.X, (float&)GameWonTextSize.Y, HUDFont, Fntsizz);
					if (GameWonTextSize.X > BoxSize.X * 0.80f)
					{
						Fntsizz -= 0.01f;
					}
					else
					{
						break;
					}
				}
				DrawText(strring, FLinearColor(0.03f, 0.03f, 0.03f), (SD.X - GameWonTextSize.X) / 2.0f, SD.Y / 2 - GameWonTextSize.Y / 2, HUDFont, Fntsizz);
			}
		}
	}
	else if (bDrawRestPurchase) //restore purchase menu
	{
		
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		//DrawTexture(GreenLayer, SD.X / 16 * 8 - SD.X / 16 * 10 / 2, SD.X / 16 * 8 / 2.9f , SD.X / 16 * 10, SD.X / 16 * 4, 0.0f, 0.25f, 1.0f, 0.75f);
		DrawTexture(GreenLayer, SD.X * 0.05f, SD.X * 0.1f, SD.X * 0.9f, SD.Y - SD.X * 0.2f, 0.0f, 0.25f, 1.0f, 0.75f);

		FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
		//float IconYPos = SD.X / 16 * 8 / 2; //SD.X * 3 / 8

		float IconYPos = SD.X * 0.1f + (SD.Y - SD.X * 0.2f) * 0.75f - IconSizeR.X / 2;

		DrawTexture(HUDbuttons1b, SD.X * 0.25f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.75f, 0.5f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.25f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "Cancel", false);

		/*DrawTexture(HUDbuttonsBuy, SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.5f, 0.0f, 0.5f, 1.0f);
		AddHitBox(FVector2D(SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "RestorePurch", false);*/

		DrawTexture(HUDbuttonsBuy, SD.X * 0.75f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.5f, 0.0f, 0.5f, 0.5f);
		AddHitBox(FVector2D(SD.X * 0.75f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "ConfRestPurch", false);

		float tempfontsiz = 1.0;
		FVector2D QuestionTextSize;
		FString beseda = ScreenTexts[18]; // TEXT("Restore Purchase!")
		FString beseda2 = ScreenTexts[19];
		FString beseda3 = ScreenTexts[20];

		FString LongerWord;

		if (beseda2.Len() > beseda3.Len())
		{
			LongerWord = beseda2;
		}
		else
		{
			LongerWord = beseda3;
		}
		if (SelLang == 3 || SelLang == 4) //added so that chinese letters are not too big
		{
			for (int32 i = 0; i < 100; i++)
			{
				GetTextSize(LongerWord, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
				if (QuestionTextSize.Y * 3.0f > SD.Y * 0.25f)
				{
					tempfontsiz -= 0.02f;
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			for (int32 i = 0; i < 100; i++)
			{
				GetTextSize(LongerWord, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
				if (QuestionTextSize.X > SD.X * 0.85f)
				{
					tempfontsiz -= 0.01f;
				}
				else
				{
					break;
				}
			}
			for (int32 i = 0; i < 100; i++)
			{
				GetTextSize(LongerWord, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
				if (QuestionTextSize.X < SD.X * 0.7f)
				{
					tempfontsiz += 0.01f;
				}
				else
				{
					break;
				}
			}
		}

		//DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, (SD.Y - QuestionTextSize.Y) / 2.0f, HUDFont, tempfontsiz);
		GetTextSize(beseda2, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
		DrawText(beseda2, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 1.5f, HUDFont, tempfontsiz);
		GetTextSize(beseda3, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
		//DrawText(beseda2, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, (SD.Y - QuestionTextSize.Y) / 2.0f + QuestionTextSize.Y * 2 , HUDFont, tempfontsiz);
		DrawText(beseda3, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 3.0f, HUDFont, tempfontsiz);
		GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
		DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f, HUDFont, tempfontsiz);
	}
	else if (bDrawThankYou) //restore purchase menu
	{
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		DrawTexture(GreenLayer, SD.X * 0.05f, SD.X * 0.1f, SD.X * 0.9f, SD.Y - SD.X * 0.2f, 0.0f, 0.25f, 1.0f, 0.75f);
		FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
		float IconYPos = SD.X * 0.1f + (SD.Y - SD.X * 0.2f) * 0.75f - IconSizeR.X / 2;

		DrawTexture(HUDbuttons1b, SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.75f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "Thanks", false);
		float tempfontsiz = 1.0;
		FVector2D QuestionTextSize;
		FString beseda = ScreenTexts[22]; // TEXT("Purchase completed, thank you.")

		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X > SD.X * 0.85f)
			{
				tempfontsiz -= 0.01f;
			}
			else
			{
				break;
			}
		}
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X < SD.X * 0.7f)
			{
				tempfontsiz += 0.01f;
			}
			else
			{
				break;
			}
		}
		//GetTextSize(beseda2, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
		DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 1.0f, HUDFont, tempfontsiz);
	}
	else if (bDrawRestoreSuccessful) //restore purchase menu
	{
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		DrawTexture(GreenLayer, SD.X * 0.05f, SD.X * 0.1f, SD.X * 0.9f, SD.Y - SD.X * 0.2f, 0.0f, 0.25f, 1.0f, 0.75f);
		FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
		float IconYPos = SD.X * 0.1f + (SD.Y - SD.X * 0.2f) * 0.75f - IconSizeR.X / 2;

		DrawTexture(HUDbuttons1b, SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.75f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "Thanks", false);
		float tempfontsiz = 1.0;
		FVector2D QuestionTextSize;
		FString beseda = ScreenTexts[26]; // TEXT("Purchase completed, thank you.")
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X > SD.X * 0.85f)
			{
				tempfontsiz -= 0.01f;
			}
			else
			{
				break;
			}
		}
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X < SD.X * 0.7f)
			{
				tempfontsiz += 0.01f;
			}
			else
			{
				break;
			}
		}
		//GetTextSize(beseda2, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
		DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 1.0f, HUDFont, tempfontsiz);
	}
	else if (bDrawPurchaseFailed) //restore purchase menu
	{
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		DrawTexture(GreenLayer, SD.X * 0.05f, SD.X * 0.1f, SD.X * 0.9f, SD.Y - SD.X * 0.2f, 0.0f, 0.25f, 1.0f, 0.75f);
		FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
		float IconYPos = SD.X * 0.1f + (SD.Y - SD.X * 0.2f) * 0.75f - IconSizeR.X / 2;

		DrawTexture(HUDbuttons1b, SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.75f, 0.5f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "ConfirmFail", false);
		float tempfontsiz = 1.0;
		FVector2D QuestionTextSize;
		FString beseda = ScreenTexts[23]; // TEXT("Restoring purchase failed.")
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X > SD.X * 0.85f)
			{
				tempfontsiz -= 0.01f;
			}
			else
			{
				break;
			}
		}
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X < SD.X * 0.7f)
			{
				tempfontsiz += 0.01f;
			}
			else
			{
				break;
			}
		}
		DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 1.0f, HUDFont, tempfontsiz);
		//DrawText(FailedMessage, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 2.0f, HUDFont, tempfontsiz);
	}
	else if (bDrawRestoreFailed) //restore purchase menu
	{
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		DrawTexture(GreenLayer, SD.X * 0.05f, SD.X * 0.1f, SD.X * 0.9f, SD.Y - SD.X * 0.2f, 0.0f, 0.25f, 1.0f, 0.75f);
		FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
		float IconYPos = SD.X * 0.1f + (SD.Y - SD.X * 0.2f) * 0.75f - IconSizeR.X / 2;

		DrawTexture(HUDbuttons1b, SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.75f, 0.5f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "ConfirmFail", false);
		float tempfontsiz = 1.0;
		FVector2D QuestionTextSize;

		FString beseda = ScreenTexts[24]; // TEXT("Purchase completed, thank you.")
		FString beseda2 = ScreenTexts[25];
		/*							  FString beseda3 = ScreenTexts[20];

		FString LongerWord;

		if (beseda2.Len() > beseda3.Len())
		{
		LongerWord = beseda2;
		}
		else
		{
		LongerWord = beseda3;
		}*/

		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda2, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X > SD.X * 0.85f)
			{
				tempfontsiz -= 0.01f;
			}
			else
			{
				break;
			}
		}
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda2, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X < SD.X * 0.7f)
			{
				tempfontsiz += 0.01f;
			}
			else
			{
				break;
			}
		}
		GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
		DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 0.8f, HUDFont, tempfontsiz);
		GetTextSize(beseda2, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
		DrawText(beseda2, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 2.3f, HUDFont, tempfontsiz);
		//DrawText(FailedMessage, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 2.0f, HUDFont, tempfontsiz);
	}
	else if (bDrawPleaseWait) //restore purchase menu
	{
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		DrawTexture(GreenLayer, SD.X * 0.05f, SD.X * 0.1f, SD.X * 0.9f, SD.Y - SD.X * 0.2f, 0.0f, 0.25f, 1.0f, 0.75f);

		float tempfontsiz = 1.0;
		FVector2D QuestionTextSize;
		FString beseda = ScreenTexts[27];

		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X > SD.X * 0.85f)
			{
				tempfontsiz -= 0.01f;
			}
			else
			{
				break;
			}
		}
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X < SD.X * 0.7f)
			{
				tempfontsiz += 0.01f;
			}
			else
			{
				break;
			}
		}
		GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
		DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, (SD.Y - QuestionTextSize.Y) / 2.0f, HUDFont, tempfontsiz);
	}
	else if (bDrawAskUser) //restore purchase menu 
	{
		AddHitBox(FVector2D(0.0f, 0.0f), SD, "EmptyHitBox", false); //empty hit box so we dont click anything in the level
		//DrawTexture(GreenLayer, SD.X / 16 * 8 - SD.X / 16 * 10 / 2, SD.X / 16 * 8 / 2.9f , SD.X / 16 * 10, SD.X / 16 * 4, 0.0f, 0.25f, 1.0f, 0.75f);
		DrawTexture(GreenLayer, SD.X * 0.05f, SD.X * 0.1f, SD.X * 0.9f, SD.Y - SD.X * 0.2f, 0.0f, 0.25f, 1.0f, 0.75f);

		FVector2D IconSizeR(FVector2D(SD.X / 16 * 10 / 6, SD.X / 16 * 10 / 6));
		//float IconYPos = SD.X / 16 * 8 / 2; //SD.X * 3 / 8

		float IconYPos = SD.X * 0.1f + (SD.Y - SD.X * 0.2f) * 0.75f - IconSizeR.X / 2;

		//DrawTexture(HUDbuttons1b, SD.X * 0.25f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.75f, 0.5f, 0.25f, 0.25f);
		DrawTexture(Buttons2, SD.X * 0.25f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.25f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.25f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "Disable", false);

		/*DrawTexture(HUDbuttonsBuy, SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.5f, 0.0f, 0.5f, 1.0f);
		AddHitBox(FVector2D(SD.X * 0.5f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "RestorePurch", false);*/

		DrawTexture(Buttons2, SD.X * 0.75f - IconSizeR.X / 2.0f, IconYPos, (float&)IconSizeR.X, (float&)IconSizeR.Y, 0.5f, 0.0f, 0.25f, 0.25f);
		AddHitBox(FVector2D(SD.X * 0.75f - IconSizeR.X / 2.0f, IconYPos), IconSizeR, "Enable", false);

		float tempfontsiz = 1.0;
		FVector2D QuestionTextSize;
		int32 df = 28;
		if (PLATFORM_IOS)
		{
			////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("running PLATFORM_IOS"));
			df = 28;
		}
		else if (PLATFORM_ANDROID)
		{
			////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("running PLATFORM_ANDROID!"));
			df = 29;
		}
		else if (PLATFORM_WINDOWS)
		{
			////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("running PLATFORM_WINDOWS!"));
			df = 29;
		}

		FString beseda = ScreenTexts[df]; // [28]- game center // [29] GooglePlay game services
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X > SD.X * 0.8f)
			{
				tempfontsiz -= 0.01f;
			}
			else
			{
				break;
			}
		}
		for (int32 i = 0; i < 100; i++)
		{
			GetTextSize(beseda, (float&)QuestionTextSize.X, (float&)QuestionTextSize.Y, HUDFont, tempfontsiz);
			if (QuestionTextSize.X < SD.X * 0.6f)
			{
				tempfontsiz += 0.01f;
			}
			else
			{
				break;
			}
		}
		DrawText(beseda, MyColor, (SD.X - QuestionTextSize.X) / 2.0f, SD.X * 0.125f + QuestionTextSize.Y * 0.75f, HUDFont, tempfontsiz);
	}
}
void AJumpyFrogsHUD::EnableClick()
{
	bCanClick = true;
}

void AJumpyFrogsHUD::SavePurchase()
{
	if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
	{
		if (GM->Implements<UGameModeInterface>())
		{
			//GameModeReference->PlayerLocation.Y = 777.7f; //TODO: check this 777.7 location shit when saving, its used to chech in app purchases 
			if(IGameModeInterface::Execute_SaveGameDataToFile(GM))
			{
				bDrawPleaseWait = false;
				bDrawThankYou = true;
				UE_LOG(LogTemp, Warning, TEXT("SavePurchase GAME DATA SAVED, all is ok."));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("SavePurchase ERROR: GAME DATA WAS NOT SAVED."));
			}
		}
	}
	/*class UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	AJumpyFrogsGameModeBase* GameModeReference = (AJumpyFrogsGameModeBase*)GetWorld()->GetAuthGameMode();*/
	
	//UndoFrGgAnlytcs::]RecordGoogleEvent("Purchase Completed!", "Language nmbr: " + FString::FromInt(SelLang), "Bought From Level: " + FString::FromInt(GameModeReference->CurrentLevel), GameModeReference->CurrentLevel);
	//UndoFrGgAnlytcs::]RecordGoogleScreen("Purchase Completed from level: " + FString::FromInt(GameModeReference->CurrentLevel) + "and Language: " + FString::FromInt(SelLang));
}

void AJumpyFrogsHUD::SaveRestoredPurchase()
{
	if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
	{
		if (GM->Implements<UGameModeInterface>())
		{
			//GameModeReference->PlayerLocation.Y = 777.7f; //TODO: check this 777.7 location shit when saving, its used to chech in app purchases 
			if (IGameModeInterface::Execute_SaveGameDataToFile(GM))
			{
				bDrawPleaseWait = false;
				bDrawRestoreSuccessful = true;
				UE_LOG(LogTemp, Warning, TEXT("SaveRestoredPurchase GAME DATA SAVED, all is ok."));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("SaveRestoredPurchase ERROR: GAME DATA WAS NOT SAVED."));
			}
		}
	}
}
void AJumpyFrogsHUD::PurchaseFailed()
{
	bDrawPleaseWait = false;
	bDrawPurchaseFailed = true;
}
void AJumpyFrogsHUD::RestoreFailed(FText OutMessage)
{
	bDrawPleaseWait = false;
	bDrawRestoreFailed = true;
}

void AJumpyFrogsHUD::ReturnPriceInfo(FString PriceLocalized)
{
	Price = PriceLocalized;
}




void AJumpyFrogsHUD::NotifyHitBoxClick(FName BoxName)
{
	if (bCanClick)
	{
		if (BoxName == FName("EmptyHitBox") || BoxName == FName("WonHitBox") || BoxName == FName("NewLevelHitBox"))
		{
			//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("EmptyHitBox clicked!"));
		}
		else
		{
			//AJumpyFrogsGameModeBase* GameModeReference = (AJumpyFrogsGameModeBase*)GetWorld()->GetAuthGameMode();
			//UndoFrGgAnlytcs::]RecordGoogleEvent("ClicksAndTouches", "HitboxName: " + BoxName.ToString(), BoxName.ToString(), GameModeReference->CurrentLevel);
			bCanClick = false;
			FTimerHandle clkrst;
			GetWorld()->GetTimerManager().SetTimer(clkrst, this, &AJumpyFrogsHUD::EnableClick, 0.11f, false);
			//PlayClickSound(); //TODO: play sound
			if (bDrawHudIcons)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("bDrawHudIcons is true , any buttons pressed or just an error?"));
				if (BoxName == FName("Pause"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Pause clicked ..."));
					//if (!GameModeReference->bIsFrogInAction)
					{
						bDrawHudIcons = false;
						bDrawPauseMenu = true;
						bStartMenu = false;
						bDrawHudIcons = false;
					}
					//UndoFrGgAnlytcs::]RecordGoogleScreen("Pause");
				}
			}
			else if (bDrawPauseMenu)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("bDrawPauseMenu is true!?"));
				if (BoxName == FName("HomeMenu"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" HomeMenu clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawPauseMenu-HomeMenu clicked");
					//bStartMenu = true;
					bDrawPauseMenu = false;
					//GameModeReference->CameraHome();
					//bTransitionHitBox = true;
					//bTransitionHitBox = false;

					bStartMenu = true;
					/*FTimerHandle HomeHandle;
					GetWorld()->GetTimerManager().SetTimer(HomeHandle, this, &AJF_HUD::GoToHome, 3.0f, false);*/
					//AJF_HUD::GoToHome();
				}
				else if (BoxName == FName("Restart"))
				{
					if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
					{
						if (GM->Implements<UGameModeInterface>())
						{
							UE_LOG(LogTemp, Warning, TEXT("Load Restart Level"));
							IGameModeInterface::Execute_LoadLevel(GM, CurrentLevel);
						}
					}

					//class UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Restart clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawPauseMenu-Restart clicked");
					////////bDrawHudIcons = true;
					//bDrawPauseMenu = false;
					//bShouldSetFrogMats = true;
					//SaveVarsBeforeMapLoad();
					//GameModeReference->LoadMap();
					//GameModeReference->SpawnFrogsAndProps(GameModeReference->CurrentLevel);
					//CheckIfCameraChanges();
				}
				else if (BoxName == FName("Continue"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Continue clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawPauseMenu-Continue clicked");
					APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
					if (MyPlayer != NULL)
					{
						MyPlayer->SetPause(false);
					}
					bDrawHudIcons = true;
					bDrawPauseMenu = false;
					//GameModeReference->CamDirector->bTimeCounting = true;
				}
				else if (BoxName == FName("LevelSelect"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" LevelSelect clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawPauseMenu-LevelSelect clicked");
					bDraw4LevelsType = true;
					bDrawPauseMenu = false;
					bLevelsFromPause = true;
				}
				else if (BoxName == FName("NextLevel"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" NextLevel clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawPauseMenu-NextLevel clicked");
					//bDrawHudIcons = true;
					//bDrawPauseMenu = false;

					if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
					{
						if (GM->Implements<UGameModeInterface>())
						{
							UE_LOG(LogTemp, Warning, TEXT("Load NextLevel"));
							CurrentLevel++;
							IGameModeInterface::Execute_LoadLevel(GM, CurrentLevel);
								
						}
					}
					//GameModeReference->CurrentLevel++;
					//SaveVarsBeforeMapLoad();
					//GameModeReference->LoadMap();

					//GameModeReference->SpawnFrogsAndProps(GameModeReference->CurrentLevel + 1);
					//CheckIfCameraChanges();
					//load next level
				}
				//else if (BoxName == FName("SoundOnOff"))
				//{
				//	//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" SoundOnOff clicked ..."));
				//	//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawPauseMenu-SoundOnOff clicked");
				//	//bDrawHudIcons = true;
				//	//bDrawPauseMenu = false;bDraw4LevelsType
				//	TurnSoundOnOff();
				//	//bSoundOn = !bSoundOn;
				//}

			}
			else if (bDraw4LevelsType)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("bDraw4LevelsType is true!?"));
				if (BoxName == FName("Back"))
				{
					bDraw4LevelsType = false;
					if (bLevelsFromPause)
					{
						bDrawPauseMenu = true;
					}
					else
					{
						bStartMenu = true;
					}
					bLevelsFromPause = false;
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Back clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDraw4LevelsType-Back clicked");
					//if (GameModeReference->bIsCameraHome)
					//{
					//	GameModeReference->DestroyFlareBlocker();
					//	bDraw4LevelsType = false;
					//	bStartMenu = true;
					//}
					////if we have to go back to game over or won screen 

					////	implement the game over logic first then use the variables that define game state

					//else if (GameModeReference->IsLevelWon)
					//{
					//	bDraw4LevelsType = false;
					//	bLevelWon = true; //todotdo

					//}
					//else if (GameModeReference->bLevelFailed)
					//{
					//	bDraw4LevelsType = false;
					//	bLevelFailed = true; //todotdo
					//}
					//else
					//{
					//	bDraw4LevelsType = false;
					//	bDrawPauseMenu = true;
					//}
				}
				else if (BoxName == FName("Classic"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Classic clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDraw4LevelsType-Classic clicked");
					bDrawLevelSelectMenu = true;
					DeltaLevel = 0;
					//	bDrawClassicL = true;
					//	bDrawTeleporterL = false;
					//	bDrawTeleporterBombL = false;
					//	bDrawBombL = false;

					bDraw4LevelsType = false;
				}
				else if (BoxName == FName("Teleporters"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Teleporters clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDraw4LevelsType-Teleporters clicked");
					bDrawLevelSelectMenu = true;
					//bDrawClassicL = false;
					//bDrawTeleporterL = true;
					//bDrawTeleporterBombL = false;
					//bDrawBombL = false;
					DeltaLevel = 100;
					bDraw4LevelsType = false;
				}
				else if (BoxName == FName("Bombs"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Bombs clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDraw4LevelsType-Bombs clicked");
					bDrawLevelSelectMenu = true;
					//bDrawClassicL = false;
					//bDrawTeleporterL = false;
					//bDrawTeleporterBombL = false;
					//bDrawBombL = true;
					DeltaLevel = 200;
					bDraw4LevelsType = false;
				}
				else if (BoxName == FName("TeleporterBombs"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" TeleporterBombs clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDraw4LevelsType-TeleporterBombs clicked");
					bDrawLevelSelectMenu = true;
					//bDrawClassicL = false;
					//bDrawTeleporterL = false;
					//bDrawTeleporterBombL = true;
					//bDrawBombL = false;
					DeltaLevel = 300;
					bDraw4LevelsType = false;
					//load next level
				}
			}
			else if (bStartMenu)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" bStartMenu clicked ..."));
				if (BoxName == FName("Play"))
				{
					bStartMenu = false;
					bDraw4LevelsType = true;
					//GameModeReference->SpawnFlareBlocker();
				}
				else if (BoxName == FName("SwissKnife"))
				{
					bSwissKnife = !bSwissKnife;
				}
				else if (BoxName == FName("Credits"))
				{
					bStartMenu = false;
					//bTransitionHitBox = false;
					bDrawCredits = true;
					bDrawCreditsNames = true;

					//navigate camera to the credits wooden post
					//GameModeReference->CreditsCamera();
					//AJumpyFrogsHUD::GoToCredits();
				}
				else if (BoxName == FName("SoundOnOff"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" SoundOnOff clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-SoundOnOff clicked");
					TurnSoundOnOff();
					//	bSoundOn = !bSoundOn;
				}
				else if (BoxName == FName("ResetGame"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" ResetGame clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-ResetGame clicked");
					bStartMenu = false;
					bDrawAreYouSure = true;
					//GameModeReference->SpawnFlareBlocker();
				}
				else if (BoxName == FName("Leaderboard"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Leaderboard clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-Leaderboard clicked");
					//bDrawLevelSelectMenu = true;
					//bDraw4LevelsType = false;
					//if (GameModeReference->PlayerLocation.Z == 22.2f)
					{
						ShowLeaderboard();
					}
					//load next level
				}
				else if (BoxName == FName("Language"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Language select clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-Language clicked");
					bStartMenu = false;
					//GameModeReference->GoToTheSky();
					//FTimerHandle Shwlng;
					//GetWorld()->GetTimerManager().SetTimer(Shwlng, this, &AJF_HUD::ShowLangSel, 2.6f, false);
					//AJF_HUD::ShowLangSel();
					//bTransitionHitBox = false;
					bShowLangSel = true;

				}
				else if (BoxName == FName("Library"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Library clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-Library clicked");
					bStartMenu = false;
					bDrawLibrary = true;
					LoadTheTips();
					//Vrstice.Reset();
					FontScale = 1.0f;
					bCutStrNextDraw = true;
					//GameModeReference->SpawnFlareBlocker();
					UnlockedTips = 0;

					/*FactsUserWidget = CreateWidget<UFactsWidget>(GetWorld(), FactsUserWidgetReference);
					FactsUserWidget->AddToViewport();*/

				/*	if (FactsUserWidgetReference)
					{
						FactsUserWidget = CreateWidget<UFactsWidget>(GetWorld(), FactsUserWidgetReference);
						if (FactsUserWidget)
						{
							FactsUserWidget->AddToViewport();
							FactsUserWidget->SetFactText(FText::FromString(TEXT("The Ornate Horned Frog lives in the rainforests of South America. It is the most aggressive and will attack an animal way larger that itself. They are not poisonous but they are fearless. When they feel threatened they will jump toward the enemy and bite them! When hunting, they prefer to wait for their prey to come to them and will eat other frogs, lizards, mice, and large insects.")));
						}
					}*/

					if (GEngine && GEngine->GameViewport)
					{
						FrogFactsWidget = SNew(SFrogFacts).OwningHUD(this);
						GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(FrogFactsContainer, SWeakWidget).PossiblyNullContent(FrogFactsWidget.ToSharedRef()));
						UpdateFrogFact();
					}

					//(English="The Ornate Horned Frog lives in the rainforests of South America. It is the most aggressive and will attack an animal way larger that itself. They are not poisonous but they are fearless. When they feel threatened they will jump toward the enemy and bite them! When hunting, they prefer to wait for their prey to come to them and will eat other frogs, lizards, mice, and large insects.")
					//FactsUserWidget->SetFactText(FText::FromString(TEXT("Frogs can breathe through their skin!")));

					// Create the widget entirely in C++
					//CreatedWidget = CreateWidget<UUserWidget>(GetWorld(), UFactsWidget::StaticClass());
					//CreatedWidget->Add

					//UFactsWidget* Widget = CreateWidget<UFactsWidget>(GetWorld(), UFactsWidget::StaticClass());
					//if (Widget)
					//{
					//	Widget->AddToViewport();
					//	UE_LOG(LogTemp, Warning, TEXT("Widget added"));
					//	// Example: set a frog fact
					//	Widget->SetFactText(FText::FromString(TEXT("Frogs can breathe through their skin and jump 20x their body length!")));
					//}
					//else
					//{
					//	UE_LOG(LogTemp, Warning, TEXT("Adding widget failed"));
					//}

				/*	for (int32 g = 0; g < 320; g++)
					{
						if (g == 32) { g = 100; }
						else if (g == 140) { g = 200; }
						else if (g == 228) { g = 300; }
						if (!UnlockedArray[g])
						{
							UnlockedTips++;
						}
					}*/
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" UnlockedTips UnlockedTips ..."));
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::FromInt(UnlockedTips));
					//CutTheStringIntoPiesces(TheTipsArray[TipsIndex], SD );
					//bDrawLibrary = true;
					//load next level
				}
				else if (BoxName == FName("Achievements"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Achievements clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-Achievements clicked");

					//if (GameModeReference->PlayerLocation.Z == 22.2f)
					{
						ShowAchievements();
						//bStartMenu = false;
						//bDraw4LevelsType = false;
						//load next level
					}
				}
				else if (BoxName == FName("SocialMedia"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" SocialMedia clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-SocialMedia clicked");
					if (bSocialMedia) { bDrawFbLike = false; }
					bSocialMedia = !bSocialMedia;

				}
				//else if (BoxName == FName("Language"))
				//{
				//	//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Language select clicked ..."));
				//	//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-Language clicked");
				//	bStartMenu = false;
				//	//GameModeReference->GoToTheSky();
				//	//FTimerHandle Shwlng;
				//	//GetWorld()->GetTimerManager().SetTimer(Shwlng, this, &AJF_HUD::ShowLangSel, 2.6f, false);
				//	//AJF_HUD::ShowLangSel();
				//	bTransitionHitBox = false;
				//	bShowLangSel = true;

				//}
				else if (BoxName == FName("AskUser"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" AskUser clicked ..."));
					//GameModeReference->SpawnFlareBlocker();
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-AskUser (game center) clicked");
					bStartMenu = false;
					bDrawAskUser = true;

					//link to Youtube video
				}
				if (bSocialMedia)
				{
					if (BoxName == FName("Facebook"))
					{
						//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Facebook clicked ..."));
						FPlatformProcess::LaunchURL(TEXT("https://www.facebook.com/Jumpy-Frogs-315368245153704/"), NULL, NULL);
						//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-Facebook clicked");
						/*bool IsLogged =
						UOnlineSubsystemExtendedFacebookBlueprintLibrary::CheckIfPlayerLoggedIn(
						);
						//open Facebook page
						//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, IsLogged ? "true" : "false");*/

						//FBLogIn();
						//bDrawFbLike = !bDrawFbLike;
					}
					else if (BoxName == FName("Friends"))
					{
						//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Friends clicked ..."));
						//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-Friends clicked");
						//InvFriends();
					}
					else if (BoxName == FName("FbPage"))
					{
						//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" FbPage clicked ..."));
						FPlatformProcess::LaunchURL(TEXT("https://www.facebook.com/Jumpy-Frogs-315368245153704/"), NULL, NULL);
						//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-FbPage clicked");
						//FbPage();

					}
					else if (BoxName == FName("Tweeter"))
					{
						//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Tweeter clicked ..."));
						FPlatformProcess::LaunchURL(TEXT("https://twitter.com/jumpyfrogs"), NULL, NULL);
						//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-Tweeter clicked");
						//Tweeter();

						//FBLogOut();
						//open Tweeter page
					}
					else if (BoxName == FName("Instagram"))
					{
						//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Instagram clicked ..."));
						//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-Instagram clicked");
						FPlatformProcess::LaunchURL(TEXT("https://www.instagram.com/jumpyfrogs/"), NULL, NULL);
						//Instagram();
						//link to instagram profile
					}
					else if (BoxName == FName("Youtube"))
					{
						//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Youtube clicked ..."));
						FPlatformProcess::LaunchURL(TEXT("https://www.youtube.com/channel/UCUSj8kN6VlLyK5tLH1aKAsg"), NULL, NULL);
						//UndoFrGgAnlytcs::]RecordGoogleScreen("bStartMenu-Youtube clicked");
						//Youtube();
						//link to Youtube video
					}

					/*
					else if (BoxName == FName("Origami"))
					{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Origami clicked ..."));
					//C:\Users\Jurif\Documents\Unreal Projects\JumpyFrogs 4.15\Saved\Screenshots\Windows
					//	TEXT("/Saved/Screenshots/Windows")
					//TEXT("C:/Users/Jurif/Documents/Unreal Projects/JumpyFrogs 4.15/Saved/Screenshots/Windows")
					//open origami videos
					Origami();
					*/
					/*
					FString TestPath = FPaths::GameDir();
					TestPath.Append("/Saved/Screenshots/");
					if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*TestPath))
					{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Screenshots Directory exists"));
					TestPath.Append(CheckOperSys());
					UE_LOG(LogTemp, Warning, TEXT("the path of this OS for screenshots is :: "), *TestPath);
					if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*TestPath))
					{
					UE_LOG(LogTemp, Warning, TEXT("Deleting Existing Screenshots now..."));
					DeleteAnyExistingScreenshots();
					}
					else
					{
					UE_LOG(LogTemp, Warning, TEXT("Could not find the OS folder with screenshots."));
					}
					}
					else
					{
					UE_LOG(LogTemp, Warning, TEXT("Screenshots Directory has not been created yet, no screenshots taken yet."));
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Screenshots Directory has not been created yet, no screenshots taken."));
					}
					FBShare(); //here we send event to take a screenshot from the blueprint
					FTimerHandle ConvScr;
					GetWorld()->GetTimerManager().SetTimer(ConvScr, this, &AJF_HUD::ConvertScrShotToImage, 0.15f, false);

					*/
					//}
				}

			}
			else if (bShowLangSel)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" bShowLangSel clicked ..."));
				if (BoxName == FName("0"))
				{
					HUDFont = JFont;
					//Language = "English";
					FlagUVPos.X = 0.0f;
					//FlagUVPos.Y = 0.0f;
					SelLang = 0;
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bShowLangSel-USEnglish clicked");
				}
				else if (BoxName == FName("1"))
				{
					HUDFont = JFont;
					//Language = "English";
					FlagUVPos.X = 0.25f;
					//FlagUVPos.Y = 0.0f;
					SelLang = 1;
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bShowLangSel-English clicked");
				}
				else if (BoxName == FName("2"))
				{
					HUDFont = JFont;
					//Language = "Slovenian";
					FlagUVPos.X = 0.5f;
					//FlagUVPos.Y = 0.0f;
					SelLang = 2;
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bShowLangSel-Slovenian clicked");

					//LoadScreenTexts(1);
				}
				else if (BoxName == FName("3"))
				{

					bShowLangSel = false;
					bShowChineseSel = true;
					return;
				}
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" bShowLangSel code continues to execute fully, this is ok if chinese isn't selected"));
				bShowLangSel = false;
				//bTransitionHitBox = true;
				//GameModeReference->ExitSky();
				//FTimerHandle HomeHandle;
				//GetWorld()->GetTimerManager().SetTimer(HomeHandle, this, &AJF_HUD::GoToHome, 2.6f, false); // sets //bDrawCredits = true;
				//AJF_HUD::GoToHome();
				//bTransitionHitBox = false;
				bStartMenu = true;
				bSwissKnife = false;
				LoadScreenTexts();
				SaveLanguage();
				
				
			}
			else if (bShowChineseSel)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" bShowChineseSel  is true ..."));
				//bool AllGood = false;
				//UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
				if (BoxName == FName("Tradi"))
				{
					HUDFont = ChineseFont;
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" TraditionalChinese clicked..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("TraditionalChinese clicked");
					//Language = "TraditionalChinese";
					FlagUVPos.X = 0.75f;
					FlagUVPos.Y = 0.0f;
					SelLang = 4;
					//	AllGood = true;
				}
				else if (BoxName == FName("Simpl"))
				{
					HUDFont = ChineseFont;
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Simplified Chinese clicked..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("SimplifiedChinese clicked");
					//Language = "SimplifiedChinese";
					FlagUVPos.X = 0.75f;
					FlagUVPos.Y = 0.0f;
					SelLang = 3;
				}
				bSwissKnife = false;
				bStartMenu = true;
				bShowChineseSel = false;
				LoadScreenTexts();
				SaveLanguage();
			}
			else if (bDrawLibrary)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" bDrawLibrary  is true ..."));
				if (BoxName == FName("NextTip"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" NextTip clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLibrary-NextTip clicked");
					//TipsIndex = FMath::RandRange(0, 116);

					TipsIndex++;					
					UpdateFrogFact();
					//if (TipsIndex > UnlockedTips)
					//{
					//	bLockedTip = true;
					//}
					//else
					//{
					//	bLockedTip = false;
					//}
					////Vrstice.Reset();
					//FontScale = 1.0f;
					//bCutStrNextDraw = true;
					//CutTheStringIntoPiesces(TheTipsArray[TipsIndex], SD);

				}
				else if (BoxName == FName("PrevTip"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" PrevTip clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLibrary-PrevTip clicked");
					//TipsIndex = FMath::RandRange(0, 116);

					TipsIndex--;					
					UpdateFrogFact();

					////Vrstice.Reset();
					//if (TipsIndex > UnlockedTips)
					//{
					//	bLockedTip = true;
					//}
					//else
					//{
					//	bLockedTip = false;
					//}
					//FontScale = 1.0f;
					//bCutStrNextDraw = true;
					//CutTheStringIntoPiesces(TheTipsArray[TipsIndex], SD);
				}
				else if (BoxName == FName("plusten"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" PrevTip clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLibrary-plusten clicked");
					//TipsIndex = FMath::RandRange(0, 116);

					TipsIndex += 10;
					UpdateFrogFact();

					//Vrstice.Reset();
					/*if (TipsIndex > UnlockedTips)
					{
						bLockedTip = true;
					}
					else
					{
						bLockedTip = false;
					}
					FontScale = 1.0f;
					bCutStrNextDraw = true;*/
					//CutTheStringIntoPiesces(TheTipsArray[TipsIndex], SD);
				}
				else if (BoxName == FName("minusten"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" PrevTip clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLibrary-minusten clicked");
					//TipsIndex = FMath::RandRange(0, 116);

					TipsIndex -= 10;
					UpdateFrogFact();

					////Vrstice.Reset();
					//if (TipsIndex > UnlockedTips)
					//{
					//	bLockedTip = true;
					//}
					//else
					//{
					//	bLockedTip = false;
					//}
					//FontScale = 1.0f;
					//bCutStrNextDraw = true;
					//CutTheStringIntoPiesces(TheTipsArray[TipsIndex], SD);
				}
				else if (BoxName == FName("sound"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" sound clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLibrary-sound clicked");
					//bSoundOn = !bSoundOn;
					TurnSoundOnOff();
				}
				else if (BoxName == FName("Close"))
				{
					//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" Close clicked ..."));
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLibrary-Close clicked");
					bDrawLibrary = false;
					bStartMenu = true;

					if (GEngine && GEngine->GameViewport && FrogFactsContainer.IsValid())
					{
						GEngine->GameViewport->RemoveViewportWidgetContent(FrogFactsContainer.ToSharedRef());
						FrogFactsContainer.Reset();
						FrogFactsWidget.Reset(); // optional, also release the SFrogFacts shared pointer
					}
					
					//GameModeReference->DestroyFlareBlocker();
				}

			}
			else if (bDrawLevelSelectMenu)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" bDrawLevelSelectMenu  is true ..."));

				//int32 Lev = (int32)BoxName.ToString;
				//FString sttr = BoxName.ToString();
				int32 Lev = FCString::Atoi(*BoxName.ToString());
				if (BoxName == FName("Back"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLevelSelectMenu-Back clicked");
					bDrawLevelSelectMenu = false;
					bDraw4LevelsType = true;
				}
				else if (Lev > 0 && Lev < 13)
				{
					bDrawLevelSelectMenu = false;
					CurrentLevel = Lev + DeltaLevel;
					LoadLevel();
					
					
					///////GameModeReference->SpawnFrogsAndProps(Lev + DeltaLevel);
					//CheckIfCameraChanges();
				}
				else if (BoxName == FName("NextPage"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLevelSelectMenu-NextPage clicked");
					bDrawLevelSelectMenu = false;
					bDrawLevelSelectMenu2 = true;
				}
			}
			else if (bDrawLevelSelectMenu2)
			{
				int32 Lev = FCString::Atoi(*BoxName.ToString());
				if (BoxName == FName("Back"))
				{
					bDrawLevelSelectMenu2 = false;
					bDraw4LevelsType = true;
				}
				else if (Lev > 12 && Lev < 25)
				{
					bDrawLevelSelectMenu2 = false;
					CurrentLevel = Lev + DeltaLevel;
					LoadLevel();
				}
				else if (BoxName == FName("NextPage"))
				{
					bDrawLevelSelectMenu2 = false;
					bDrawLevelSelectMenu3 = true;
				}
				else if (BoxName == FName("PrevPage"))
				{
					bDrawLevelSelectMenu2 = false;
					bDrawLevelSelectMenu = true;
				}
			}
			else if (bDrawLevelSelectMenu3)
			{
				int32 Lev = FCString::Atoi(*BoxName.ToString());
				if (BoxName == FName("Back"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLevelSelectMenu3-Back clicked");
					bDrawLevelSelectMenu3 = false;
					bDraw4LevelsType = true;
				}
				else if (Lev > 24 && Lev < 37)
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLevelSelectMenu3-Level 25-36 clicked");
					bDrawLevelSelectMenu3 = false;
					CurrentLevel = Lev + DeltaLevel;
					LoadLevel();
					//GameModeReference->SpawnFrogsAndProps(Lev + DeltaLevel);
					//CheckIfCameraChanges();
				}
				else if (BoxName == FName("NextPage"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLevelSelectMenu3-NextPage clicked");
					bDrawLevelSelectMenu3 = false;
					bDrawLevelSelectMenu4 = true;
				}
				else if (BoxName == FName("PrevPage"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLevelSelectMenu3-PrevPage clicked");
					bDrawLevelSelectMenu3 = false;
					bDrawLevelSelectMenu2 = true;
				}
			}
			else if (bDrawLevelSelectMenu4)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" bDrawLevelSelectMenu4  is true ..."));
				int32 Lev = FCString::Atoi(*BoxName.ToString());
				if (BoxName == FName("Back"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLevelSelectMenu4-Back clicked");
					bDrawLevelSelectMenu4 = false;
					bDraw4LevelsType = true;
				}
				else if (Lev > 35 && Lev < 41)
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLevelSelectMenu4-Level 36-40 clicked");
					bDrawLevelSelectMenu4 = false;
					CurrentLevel = Lev + DeltaLevel;
					//SaveVarsBeforeMapLoad();
					LoadLevel();
					//GameModeReference->SpawnFrogsAndProps(Lev + DeltaLevel);
					//CheckIfCameraChanges();
				}
				else if (BoxName == FName("PrevPage"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawLevelSelectMenu4-PrevPage clicked");
					bDrawLevelSelectMenu4 = false;
					bDrawLevelSelectMenu3 = true;
				}

			}

			else if (bDrawCredits)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" bDrawCredits  is true ..."));
				if (BoxName == FName("CreditsHitBox"))
				{
					if (bDrawCreditsNames)
					{
						//GameModeReference->DestroyFlareBlocker(); 
						//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawCreditsNames clicked first");
						bDrawCreditsNames = false;
						bDrawCredits = false;
						//bTransitionHitBox = true;
						//GameModeReference->CameraHome();
						//FTimerHandle HandlerLw;
						//GetWorld()->GetTimerManager().SetTimer(HandlerLw, this, &AJumpyFrogsGameModeBase::LevelWonSound, 3.0f, false);
						//AJF_HUD::GoToHome();
						//FTimerHandle HomeHandle;
						//GetWorld()->GetTimerManager().SetTimer(HomeHandle, this, &AJF_HUD::GoToHome, 3.0f, false); // sets //bDrawCredits = true;
					}
					else
					{
						//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawCreditsNames clicked second");
						bDrawCreditsNames = true;
					}

				}
			}
			else if (bDrawAreYouSure)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" bDrawAreYouSure  is true ..."));
				if (BoxName == FName("Yes"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawAreYouSure-Yes clicked");
					bDrawAreYouSure = false;
					bDrawAreYouAbsSure = true;
				}
				else if (BoxName == FName("No"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawAreYouSure-No clicked");
					bDrawAreYouSure = false;
					bStartMenu = true;
					bSwissKnife = false;
					//GameModeReference->DestroyFlareBlocker();
				}
			}
			else if (bDrawAreYouAbsSure)
			{
				//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT(" bDrawAreYouAbsSure  is true ..."));
				if (BoxName == FName("Yes"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawAreYouAbsSure-Yes clicked");
					bDrawAreYouAbsSure = false;
					bStartMenu = true;
					bSwissKnife = false;
					//GameModeReference->ResetGameData();
					//GameModeReference->DestroyFlareBlocker();
				}
				else if (BoxName == FName("No"))
				{
					//UndoFrGgAnlytcs::]RecordGoogleScreen("bDrawAreYouAbsSure-No clicked");
					bDrawAreYouAbsSure = false;
					bStartMenu = true;
					bSwissKnife = false;
					//GameModeReference->DestroyFlareBlocker();
				}
			}
			//else if (bLevelFailed || bLevelWon)
			//{
			//	//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("bLevelFailed || bLevelWon  is true ..."));
			//	if (BoxName == FName("LevelSelect"))
			//	{
			//		/*if (!GameModeReference->bAchievementUnlocked && !GameModeReference->bNewLevUnlocked && !GameModeReference->bBlockClicks)
			//		{*/
			//		//UndoFrGgAnlytcs::]RecordGoogleScreen("bLevelFailed||bLevelWon-LevelSelect clicked");
			//		bLevelFailed = false;
			//		bLevelWon = false;
			//		bDraw4LevelsType = true;
			//		//}
			//	}
			//	else if (BoxName == FName("Restart"))
			//	{
			//		/*if (!GameModeReference->bAchievementUnlocked && !GameModeReference->bNewLevUnlocked && !GameModeReference->bBlockClicks)
			//		{*/
			//		//UndoFrGgAnlytcs::]RecordGoogleScreen("bLevelFailed||bLevelWon-Restart clicked");
			//		class UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
			//		bLevelFailed = false;
			//		bLevelWon = false;
			//		bShouldSetFrogMats = true;
			//		LoadLevel();
			//		//GameModeReference->SpawnFrogsAndProps(GameModeReference->CurrentLevel);
			//		//CheckIfCameraChanges();
			//		//RestartLevel
			//		//}
			//	}
			//	else if (BoxName == FName("NextLevel"))
			//	{
			//		/*if (!GameModeReference->bAchievementUnlocked && !GameModeReference->bNewLevUnlocked && !GameModeReference->bBlockClicks)
			//		{*/
			//		//UndoFrGgAnlytcs::]RecordGoogleScreen("bLevelFailed||bLevelWon-NextLevel clicked");
			//		bLevelFailed = false;
			//		bLevelWon = false;
			//		CurrentLevel++;
			//		LoadLevel();
			//		//GameModeReference->SpawnFrogsAndProps(GameModeReference->CurrentLevel + 1);
			//		//CheckIfCameraChanges();
			//		//}
			//	}
			//	else if (BoxName == FName("AchievementClicked"))// && !bBlockClicks)
			//	{
			//		//bDrawAchievement = false;
			//		/*if (!GameModeReference->bBlockClicks && !GameModeReference->bNewLevUnlocked)
			//		{*/
			//		bShowNormalAch = false;
			//		if (!bShowGlobAch)
			//		{
			//			//bAchievementUnlocked = false;
			//		}
			//		else
			//		{
			//			//GameModeReference->PlayPopUpSound(); //TODO:PlayAudio
			//			CheckWhatAch();
			//		}
			//		//UndoFrGgAnlytcs::]RecordGoogleScreen("bLevelFailed||bLevelWon-AchievementClicked clicked");
			//		//GameModeReference->bBlockClicks = false;
			//		//}
			//	}
			//	else if (BoxName == FName("AchEnlarge"))
			//	{
			//		bDrawAchBig = true;
			//	}
			//	else if (BoxName == FName("AchBigClicked"))
			//	{
			//		bDrawAchBig = false;
			//	}
			//	else if (BoxName == FName("LevUnlClickd"))
			//	{
			//		//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("LevUnlClickd clicked!"));
			//		//UndoFrGgAnlytcs::]RecordGoogleScreen("bLevelFailed||bLevelWon-LevUnlClickd clicked");
			//		//bDrawAchievement = false;
			//		if (GameModeReference->bNewModeUnlocked)
			//		{
			//			bModeUnlocked = true;
			//			GameModeReference->bNewModeUnlocked = false;
			//			//GameModeReference->bBlockClicks = false;
			//			//	GameModeReference->bNewLevUnlocked = false;
			//			bDrawLock = true;
			//			GameModeReference->PlayPopUpSound();
			//		}
			//		else if (bDrawLock) //if(bModeUnlocked)
			//		{
			//			bDrawLock = false;
			//			GameModeReference->PlayNewTipSound();
			//		}
			//		else
			//		{
			//			GameModeReference->bNewLevUnlocked = false;
			//			GameModeReference->bBlockClicks = false;
			//			//bModeUnlocked = false;
			//		}

			//	}
			//	/*else if (BoxName == FName("ModeUnlClickd"))
			//	{
			//	//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("ModeUnlClickd clicked!"));
			//	GameModeReference->bNewLevUnlocked = false;
			//	GameModeReference->bBlockClicks = false;
			//	bModeUnlocked = false;
			//	}*/
			//	else if (bShowGlobAch)
			//	{
			//		if (BoxName == FName("AchStCl"))
			//		{
			//			if (GlobAchIndex == 1)
			//			{
			//				//bDrawAchievement = false;
			//				//GameModeReference->bAchievementUnlocked = true;
			//				//bShowGlobAch = true;
			//				if (GameModeReference->PlayerLocation.Z == 22.2f)
			//				{
			//					if (PLATFORM_ANDROID)
			//					{
			//						WriAchs(*(AchievementsList[13]), 13);
			//					}
			//					else if (PLATFORM_IOS)
			//					{
			//						WriAchs(*(AchievementsListiOS[13]), 13);
			//					}
			//				}
			//				bShowAch1Stars = false;
			//				//UndoFrGgAnlytcs::]RecordGoogleScreen("bLevelFailed||bLevelWon-bShowGlobAch-AchStCl 1 clicked");
			//			}
			//			else if (GlobAchIndex == 2)
			//			{
			//				//bDrawAchievement = false;
			//				//GameModeReference->bAchievementUnlocked = true;
			//				//bShowGlobAch = true;
			//				if (GameModeReference->PlayerLocation.Z == 22.2f)
			//				{
			//					if (PLATFORM_ANDROID)
			//					{
			//						WriAchs(*(AchievementsList[14]), 14);
			//					}
			//					else if (PLATFORM_IOS)
			//					{
			//						WriAchs(*(AchievementsListiOS[14]), 14);
			//					}
			//				}
			//				bShowAch2Stars = false;
			//				//UndoFrGgAnlytcs::]RecordGoogleScreen("bLevelFailed||bLevelWon-bShowGlobAch-AchStCl 2 clicked");
			//			}
			//			else if (GlobAchIndex == 3)
			//			{
			//				//bDrawAchievement = false;
			//				//GameModeReference->bAchievementUnlocked = true;
			//				//bShowGlobAch = true;
			//				if (GameModeReference->PlayerLocation.Z == 22.2f)
			//				{
			//					if (PLATFORM_ANDROID)
			//					{
			//						WriAchs(*(AchievementsList[15]), 15);
			//					}
			//					else if (PLATFORM_IOS)
			//					{
			//						WriAchs(*(AchievementsListiOS[15]), 15);
			//					}
			//				}
			//				bShowAch3Stars = false;
			//				//UndoFrGgAnlytcs::]RecordGoogleScreen("bLevelFailed||bLevelWon-bShowGlobAch-AchStCl 3 clicked");
			//			}

			//			if (!(bShowAch1Stars || bShowAch2Stars || bShowAch3Stars))
			//			{
			//				bShowGlobAch = false;
			//				GameModeReference->bAchievementUnlocked = false;
			//				//GameModeReference->CheckAchievements();
			//				//	//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("!(bShowAch1Stars || bShowAch1Stars || bShowAch1Stars)"));
			//			}
			//			else
			//			{
			//				GameModeReference->PlayPopUpSound();
			//				CheckWhatAch();
			//			}
			//		}
			//	}
			//	else if (BoxName == FName("FacebookShare")) // && !GameModeReference->bNewLevUnlocked && !GameModeReference->bBlockClicks)
			//	{
			//		//open a new screen saying "Posting to Facebook..."
			//		//UndoFrGgAnlytcs::]RecordGoogleScreen(" FacebookShare clicked");
			//		FString TestPath = FPaths::ProjectDir();
			//		TestPath.Append("/Saved/Screenshots/");
			//		if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*TestPath))
			//		{
			//			//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Screenshots Directory exists"));
			//			TestPath.Append(CheckOperSys());
			//			UE_LOG(LogTemp, Warning, TEXT("the path of this OS for screenshots is :: "), *TestPath);
			//			if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*TestPath))
			//			{
			//				UE_LOG(LogTemp, Warning, TEXT("Deleting Existing Screenshots now..."));
			//				DeleteAnyExistingScreenshots();
			//			}
			//			else
			//			{
			//				UE_LOG(LogTemp, Warning, TEXT("Could not find the OS folder with screenshots."));
			//			}
			//		}
			//		else
			//		{
			//			UE_LOG(LogTemp, Warning, TEXT("Screenshots Directory has not been created yet, no screenshots taken yet."));
			//			//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Screenshots Directory has not been created yet, no screenshots taken."));
			//		}
			//		FTimerHandle ConvScr;
			//		GetWorld()->GetTimerManager().SetTimer(ConvScr, this, &AJF_HUD::ConvertScrShotToImage, 0.15f, false);
			//	}
			//}
			//else if (bDrawThankYou || bDrawPurchaseFailed || bDrawRestoreSuccessful || bDrawRestoreFailed)
			//{
			//	if (BoxName == FName("Thanks"))
			//	{
			//		bDrawThankYou = false;
			//		bDrawRestoreSuccessful = false;
			//		bDrawHudIcons = true;
			//		GameModeReference->CamDirector->bTimeCounting = true;
			//	}
			//	else if (BoxName == FName("ConfirmFail"))
			//	{
			//		bDrawPurchaseFailed = false;
			//		bDrawRestoreFailed = false;
			//		bDrawHudIcons = true;
			//		GameModeReference->CamDirector->bTimeCounting = true;					
			//	}
			//}
			//else if (bDrawAskUser)
			//{
			//	if (BoxName == FName("Enable"))
			//	{
			//		bDrawAskUser = false;
			//		GameModeReference->DestroyFlareBlocker();
			//		bStartMenu = true;
			//		GameModeReference->PlayerLocation.Z = 22.2f;
			//		FString Path = FPaths::ProjectDir();
			//		Path.Append("\\SavedData\\jumpyfrogs.save");
			//		GameModeReference->SaveGameDataToFile(Path);
			//		LogInPlatform();					

			//	}
			//	else if (BoxName == FName("Disable"))
			//	{
			//		bDrawAskUser = false;
			//		GameModeReference->DestroyFlareBlocker();
			//		bStartMenu = true;
			//		GameModeReference->PlayerLocation.Z = 11.0f;
			//		FString Path = FPaths::ProjectDir();
			//		Path.Append("\\SavedData\\jumpyfrogs.save");
			//		GameModeReference->SaveGameDataToFile(Path);
			//		LogOutPlatform();

			//	}
			//}
		}
	}
}



void AJumpyFrogsHUD::LoadTheTips()
{
	int32 Max;
	TheTipsArray.Reset();
	class UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	if (SelLang == 0 || SelLang == 1)
	{
		TArray<FLibraryData*> LibTipsList;
		LibDataTable->GetAllRows<FLibraryData>("loading english DataTable", LibTipsList);
		Max = LibTipsList.Num();
		for (int32 i = 0; i < Max; i++)
		{
			TheTipsArray.Add(LibTipsList[i]->English);
		}
	}
	else if (SelLang == 2)
	{
		TArray<FLibraryData*> LibSlovenianTipsList;
		LibDataTableSlovenian->GetAllRows<FLibraryData>("loading Slovenian DataTable", LibSlovenianTipsList);
		Max = LibSlovenianTipsList.Num();
		for (int32 i = 0; i < Max; i++)
		{
			TheTipsArray.Add(LibSlovenianTipsList[i]->English);
		}
	}
	else if (SelLang == 3)//Simplified chinese
	{
		//HUDFont = ChineseFont;
		//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Simplified Chinese Language Selected, Loading tips now..."));

		TArray<FLibraryData*> LibChineseTipsList; //simplified chinese
		LibDataTableChinese->GetAllRows<FLibraryData>("loading simplified Chinese DataTable", LibChineseTipsList);
		Max = LibChineseTipsList.Num();
		for (int32 i = 0; i < Max; i++)
		{
			TheTipsArray.Add(LibChineseTipsList[i]->English);
		}
		//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Simplified Chinese Language Loaded..."));
	}
	else if (SelLang == 4) //traditional chinese
	{
		//HUDFont = ChineseFont;
		//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Traditional Chinese Language Selected, Loading tips now..."));

		TArray<FLibraryData*> LibChineseTipsList;
		LibDataTableTrChinese->GetAllRows<FLibraryData>("loading Traditional Chinese DataTable", LibChineseTipsList);
		Max = LibChineseTipsList.Num();
		for (int32 i = 0; i < Max; i++)
		{
			TheTipsArray.Add(LibChineseTipsList[i]->English);
		}
		//uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Traditional Chinese Language Loaded..."));
	}
}


void AJumpyFrogsHUD::SaveLanguage()
{
	if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
	{
		if (GM->Implements<UGameModeInterface>())
		{
			//GameModeReference->PlayerLocation.Y = 777.7f; //TODO: check this 777.7 location shit when saving, its used to chech in app purchases 
			if (IGameModeInterface::Execute_SaveLanguage(GM))
			{
				UE_LOG(LogTemp, Warning, TEXT("SaveLanguage executed, all is ok."));
				LoadTheTips();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("SaveLanguage ERROR: Language WAS NOT SAVED."));
			}
		}
	}
}

void AJumpyFrogsHUD::LoadLevel()
{
	if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
	{
		if (GM->Implements<UGameModeInterface>())
		{
			IGameModeInterface::Execute_LoadLevel(GM, CurrentLevel);
			UE_LOG(LogTemp, Warning, TEXT("LOAD LEVEL: %s"), *FString::FromInt(CurrentLevel));
		}
	}
}
void AJumpyFrogsHUD::TurnSoundOnOff()
{
	/*AJumpyFrogsGameMode* GameModeReference = (AJumpyFrogsGameModeBase*)GetWorld()->GetAuthGameMode();
	
	if (bSoundOn)
	{
		GameModeReference->PondAudioComponent->Stop();
	}
	else
	{
		GameModeReference->PondAudioComponent->Play(0.0f);
	}
	if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
	{
		if (GM->Implements<UGameModeInterface>())
		{
			IGameModeInterface::Execute_LoadLevel(GM, CurrentLevel);
			UE_LOG(LogTemp, Warning, TEXT("LOAD LEVEL: %s"), *FString::FromInt(CurrentLevel));
		}
	}*/
	UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	bSoundOn = !bSoundOn;
}



void AJumpyFrogsHUD::LoadScreenTexts()
{
	TArray<FScreenTextData*> ScrTextsList;

	ScreenTextDataTable->GetAllRows<FScreenTextData>("Some Debug Message String if Fails", ScrTextsList);

	ScreenTexts.Reset();
	ScreenTexts.Add(ScrTextsList[SelLang]->LevelStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->FailedStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->CompleteStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->UnlockedStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->LevScoreStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->TimeBonStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->TotScoreStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->RatingStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->AchUnlockStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->TipUnlockStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->ResetStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->SureStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->BuyStr);
	ScreenTexts.Add(ScrTextsList[SelLang]->Buy2Str);
	ScreenTexts.Add(ScrTextsList[SelLang]->Buy3Str);
	ScreenTexts.Add(ScrTextsList[SelLang]->BuyConfirm);
	ScreenTexts.Add(ScrTextsList[SelLang]->BuyConfirm2);
	ScreenTexts.Add(ScrTextsList[SelLang]->BuyConfirm3);
	ScreenTexts.Add(ScrTextsList[SelLang]->RestorePurch);
	ScreenTexts.Add(ScrTextsList[SelLang]->RestorePurch2);
	ScreenTexts.Add(ScrTextsList[SelLang]->RestorePurch3);
	ScreenTexts.Add(ScrTextsList[SelLang]->Price);
	ScreenTexts.Add(ScrTextsList[SelLang]->Thanks);
	ScreenTexts.Add(ScrTextsList[SelLang]->Failed);
	ScreenTexts.Add(ScrTextsList[SelLang]->Failed2);
	ScreenTexts.Add(ScrTextsList[SelLang]->Failed3);
	ScreenTexts.Add(ScrTextsList[SelLang]->Restored);
	ScreenTexts.Add(ScrTextsList[SelLang]->Wait);
	ScreenTexts.Add(ScrTextsList[SelLang]->Askios);
	ScreenTexts.Add(ScrTextsList[SelLang]->AskAndroid);

	TArray<FAchText*> FAchTextsList;
	AchDT->GetAllRows<FAchText>("Some Debug Message String if Fails", FAchTextsList);
	AchievTexts.Reset();
	AchievTexts.Add(FAchTextsList[SelLang]->First);
	AchievTexts.Add(FAchTextsList[SelLang]->Second);
	AchievTexts.Add(FAchTextsList[SelLang]->Third);
	AchievTexts.Add(FAchTextsList[SelLang]->Fourth);
	AchievTexts.Add(FAchTextsList[SelLang]->Fifth);
	AchievTexts.Add(FAchTextsList[SelLang]->Sixth);
	AchievTexts.Add(FAchTextsList[SelLang]->Seven);
	AchievTexts.Add(FAchTextsList[SelLang]->Eight);
	AchievTexts.Add(FAchTextsList[SelLang]->Nine);
	AchievTexts.Add(FAchTextsList[SelLang]->Ten);
	AchievTexts.Add(FAchTextsList[SelLang]->Eleven);
	AchievTexts.Add(FAchTextsList[SelLang]->Twelwe);
	AchievTexts.Add(FAchTextsList[SelLang]->Thirteen);
	AchievTexts.Add(FAchTextsList[SelLang]->Fourteen);
	AchievTexts.Add(FAchTextsList[SelLang]->Fifteen);
	AchievTexts.Add(FAchTextsList[SelLang]->Sixteen);
}

void AJumpyFrogsHUD::FirstSave()
{
	bStartMenu = false;
	bDrawAskUser = true;
	bBlockClicks = false;
}

void AJumpyFrogsHUD::StartGame()
{
	bStartMenu = false;
	bDrawHudIcons = true;
}

void AJumpyFrogsHUD::LoadTextsAtStart()
{
	HUDFont = SelLang == 3 || SelLang == 4 ? ChineseFont : JFont;
	LoadRatingLimits();
	LoadScrOff();
	//class UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	//LoadScreenTexts(GameInstanceReference->SelLang);

	if (UObject* GM = (UObject*)GetWorld()->GetAuthGameMode())
	{
		if (GM->Implements<UGameModeInterface>())
		{
			UnlockedArray = IGameModeInterface::Execute_GetUnlockedArray(GM);
			HighScoreArray = IGameModeInterface::Execute_GetHighScoreArray(GM);
			//PlayTime = IGameModeInterface::Execute_GetPlayTime(GM);
			CurrentLevel = IGameModeInterface::Execute_GetCurrentLevel(GM);
			Score = IGameModeInterface::Execute_GetScore(GM);
			//TimeBonus = IGameModeInterface::Execute_GetTimeBonus(GM);

			bBlockClicks = IGameModeInterface::Execute_GetBlockClicks(GM);
			bAchievementUnlocked = IGameModeInterface::Execute_GetAchievementUnlocked(GM);
			bNewLevUnlocked = IGameModeInterface::Execute_GetNewLevUnlocked(GM);
			AchIndex = IGameModeInterface::Execute_GetAchIndex(GM);

			//UJumpyFrogsGameInstance* GameInstanceReference = Cast<UJumpyFrogsGameInstance>(GetWorld()->GetGameInstance());
			//const int32 SelLang = SelLang;
		}
	}
}
void AJumpyFrogsHUD::LoadRatingLimits()
{
	HS2StarsLimitArray.Reset();
	HS3StarsLimitArray.Reset();
	//GameModeReference->TimeLimitsArray.Reset();
	TArray<FRatingLimitsDT*> RatingLimitsList;

	RatingStarsDT->GetAllRows<FRatingLimitsDT>("Rating stars Data Table failed loading...", RatingLimitsList);
	uint16 Max = RatingLimitsList.Num();
	for (uint16 i = 0; i < Max; i++)
	{
		HS2StarsLimitArray.Add(RatingLimitsList[i]->TwoStars);
		HS3StarsLimitArray.Add(RatingLimitsList[i]->ThreeStars);
		//GameModeReference->TimeLimitsArray.Add(RatingLimitsList[i]->TimeLimit);
	}
}


void AJumpyFrogsHUD::LoadScrOff()
{
	bDrawLoadingScreen = false;
	bStartMenu = true;
	//bStartMenu = true;
}

void AJumpyFrogsHUD::BeginPlay()
{
	Super::BeginPlay();

	//RandomizeButtonColors();

	

	//class AJumpyFrogsGameModeBase* GameModeReference = (AJumpyFrogsGameModeBase*)GetWorld()->GetAuthGameMode();
	//class UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	//GameModeReference = (AJumpyFrogsGameModeBase*)GetWorld()->GetAuthGameMode();
	//GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();

	//UGameInstance* World = GetGameInstance();

	/*bShowStartCountdown = GameInstanceReference->bShowStartCountdown;
	bDrawAIActive = GameInstanceReference->bDrawAIActive;
	bDrawAIMenu = GameInstanceReference->bDrawAIMenu;
	bDrawAiSolver = GameInstanceReference->bDrawAiSolver;
	bDrawAiSolverMenu = GameInstanceReference->bDrawAiSolverMenu;
	bDrawHudIcons = GameInstanceReference->bDrawHudIcons;
	bStartMenu = GameInstanceReference->bStartMenu;
	IsSaveProgressOn = GameInstanceReference->IsSaveProgressOn;
	bTransitionHitBox = GameInstanceReference->bTransitionHitBox;*/

	//if (!GameInstanceReference->bFirstMapLoad)
	//{
	//	//CheckIfCameraChanges();

	//	FTimerHandle smss;
	//	GetWorld()->GetTimerManager().SetTimer(smss, this, &AJumpyFrogsHUD::CheckIfCameraChanges, 0.1f, false);
	//}
	FTimerHandle LoadTextsAtStartTimer;
	GetWorld()->GetTimerManager().SetTimer(LoadTextsAtStartTimer, this, &AJumpyFrogsHUD::LoadTextsAtStart, 0.4f, false);
	
}
void AJumpyFrogsHUD::RandomizeButtonColors()
{
	// Shuffle
	for (int32 i = Buttons.Num() - 1; i > 0; --i)
	{
		int32 j = FMath::RandRange(0, i);
		Buttons.Swap(i, j);
	}
	//Buttons.Empty();
	//for (int32 i = 0; i < 16; i++)
	//{
	//	uint8 RandNumber = FMath::RandRange(0, 15);
	//	if (RandNumber  != PreviousNumber)
	//	{
	//		RandomizedArray.Add(RandNumber);
	//	}
	//	FVector2D NewColor;
	//	while (FVector2D NewColor GetRandomColor() != Buttons[Buttons.Num() - 1])
	//	{

	//	}
	//	Buttons.Add(GetRandomColor());
	//}
}
FVector2D AJumpyFrogsHUD::GetRandomColor()
{
	FVector2D TextCoord = FVector2D::ZeroVector;
	uint8 RandNumber = FMath::RandRange(0, 15);
	uint8 Sector = RandNumber+1 % 4;
	switch (Sector)
	{
		case 1: TextCoord.X = 0.f; break;
		case 2: TextCoord.X = 0.25f; break;
		case 3: TextCoord.X = 0.5f; break;
		case 0: TextCoord.X = 0.75f; break;

	}
	Sector = RandNumber  / 4;
	switch (Sector)
	{
		case 0: TextCoord.Y = 0.f; break;
		case 1: TextCoord.Y = 0.25f; break;
		case 2: TextCoord.Y = 0.5f; break;
		case 3: TextCoord.Y = 0.75f; break;
	}
	return TextCoord;
}
void AJumpyFrogsHUD::UpdateFrogFact()
{
	if (TipsIndex > 121) { TipsIndex = 121; }
	else if (TipsIndex < 1) { TipsIndex = 0; }

	if (FrogFactsWidget.IsValid())
	{
		FrogFactsWidget->SetFactText(FText::FromString(TheTipsArray[TipsIndex]), FText::FromString(FString::FromInt(TipsIndex + 1) + "/" + FString::FromInt(TheTipsArray.Num())), SelLang == 3 || SelLang == 4);
		//FrogFactsWidget->SetFactText(LOCTEXT("NewFact", "Here is a new frog fact!"));
	}
}