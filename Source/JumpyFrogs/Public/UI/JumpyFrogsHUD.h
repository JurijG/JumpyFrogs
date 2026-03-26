// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/DataTable.h"
//#include "TextProperty.h"
#include "JumpyFrogsHUD.generated.h"


/**
 * 
 */
UCLASS()
class JUMPYFROGS_API AJumpyFrogsHUD : public AHUD
{
	GENERATED_BODY()
	
	AJumpyFrogsHUD();

public:
	void FirstSave();

protected:

	TArray <bool> UnlockedArray;
	TArray <int32> HighScoreArray;
	//int32 PlayTime;
	//CurrentLevel
	uint16 Score = 0;
	//int32 TimeBonus; //TODO:REmove time entirely

	bool bBlockClicks = true;
	bool bAchievementUnlocked = false;
	bool bNewLevUnlocked = false;
	int32 AchIndex = 0;


	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	UPROPERTY() UFont* HUDFont; //placeholder to know which font is actively selected, used in DrawText function
	UPROPERTY() UFont* JFont; //my jumpy frogs custom font
	UPROPERTY() UFont* ChineseFont; //chinese font


	
	/*UFUNCTION(BlueprintImplementableEvent, category = "JumpyFrogsHUD_BP")
void FBLogIn();
UFUNCTION(BlueprintImplementableEvent, category = "JumpyFrogsHUD_BP")
void FBLogOut();*/

/*
UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void Tweeter();
UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void Instagram();
UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void FBShare();
UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void FbPage();
UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void InvFriends();
UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void Youtube();
UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void Origami();

	*/
	UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void ShowLeaderboard();
	UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void ShowAchievements();

	UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void WriteLeaderboard(const int32 TotScr);
	UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP)
	void WriAchs(FName TheName, int32 Indexx);

	UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP) //used in BP for logging in GoogloePlay/GameCenter 
		void LogInPlatform();// (const TArray <bool> LocalSavedAch);
	UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP) //used in BP for logging out GoogloePlay/GameCenter 
		void LogOutPlatform();// (const TArray <bool> LocalSavedAch);

	UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP) //used in BP for logging in GoogloePlay/GameCenter at first load
		void BuyNow();
	UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP) //used in BP for logging in GoogloePlay/GameCenter at first load
		void RestorePurchase();
	UFUNCTION(BlueprintImplementableEvent, category = JumpyFrogsHUD_BP) //used in BP for logging in GoogloePlay/GameCenter at first load
		void ReadPurchaseInfo();

	UFUNCTION(BlueprintCallable, Category = JumpyFrogs)
	void ReturnPriceInfo(FString PriceLocalized);


	//UFUNCTION(BlueprintCallable, Category = JumpyFrogs)

	UFUNCTION(BlueprintCallable, Category = JumpyFrogs)
	void SaveRestoredPurchase();
	UFUNCTION(BlueprintCallable, Category = JumpyFrogs)
	void SavePurchase();
	UFUNCTION(BlueprintCallable, Category = JumpyFrogs)
	void PurchaseFailed();
	UFUNCTION(BlueprintCallable, Category = JumpyFrogs)
	void RestoreFailed(FText OutMessage);


	//void RequestLogInPlatform();

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	TArray<bool> LocalSavedAch; //only for use in blueprint at first load for syncing achievements
	*/
	/*UFUNCTION(BlueprintCallable , Category = JumpyFrogs)
	void RequestLogIn();*/


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	int32 HighScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = JumpyFrogs)
	FString FacebookShareText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = JumpyFrogs)
	FString FbImageText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = JumpyFrogs)
	bool ImagePosted; //wheter the image was posted on facebook or it failed

	//void AJF_HUD::NotifyHitBoxClick(FName BoxName) override;
	void NotifyHitBoxClick(FName BoxName) override;


	//void ReceiveHitBoxClick	(const FName BoxName)  override;
	//void UpdateAndDispatchHitBoxClickEvents() override;

	//	event ReceiveHitBoxClick(const FName BoxName) override;
	//AJF_HUD(const FObjectInitializer& ObjectInitializer);
	//void ReceiveHitBoxClick(const FName BoxName) implement;
	//void ReceiveHitBoxClick(const FName BoxName) override;
	//void AJF_HUD::ReceiveHitBoxClick() override;// ReceiveHitBoxClick(FName BoxName) override;
	//void GetHitBoxAtCoordinates(FVector2D ) override;
	//const FHUDHitBox* GetHitBoxAtCoordinates(FVector2D InHitLocation, bool bConsumingInput = false) const override;
	//void ReceiveHitBoxRelease(FName BoxName) override;

	//ReceiveHitBoxRelease
	//	virtual void AJF_HUD::HandleBugScreenShot() override;


	//virtual void AJF_HUD::PostRender() override;


	//virtual void AJF_HUD::NotifyHitBoxRelease(FName BoxName) override;
	//	void AJF_HUD::ReceiveHitBoxClick(const FName BoxName) override;
	static TArray<FString> GetAllFilesInDirectory(const FString directory, const bool fullPath = true, const FString onlyFilesStartingWith = TEXT(""), const FString onlyFilesEndingWith = TEXT(""));

	bool bCutStrNextDraw;
	//void CutString(FString zanimivost, int32 length);
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	TArray <FString> TheTipsArray;
	TArray <FString> Vrstice = { TEXT(" "), TEXT(" ") };
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica1;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica2;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica3;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica4;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica5;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica6;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica7;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica8;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica9;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica10;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	FString Vrstica11;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)
	int32 LineLength;

	int32 TipsIndex = 0;
	int32 DeltaLevel = 0;

	int32 CurrentLevel;

	//UFUNCTION(Exec, BlueprintCallable, Category = JumpyFrogs)
	void LoadLevel();
	void LoadTheTips();
	void SaveLanguage();
	//UFUNCTION(Exec, BlueprintCallable, Category = JumpyFrogs)
	//void CutTheStringIntoPiesces(FString CurrentTip, FVector2D ScreenDimensions); //, FVector2D ScreenDimensions

	FVector2D SD;
	//camera moving related functions, they trigger things after a timer, main camera function are in gamemode script
	void GoToCredits();
	void GoToHome();
	void ShowHudIcons();
	void CheckIfCameraChanges(); //check if the camera will change now and we need to add delay before showing HUD
	void Countdown();
	void StartCounting();
	void SaveVarsBeforeMapLoad();
	//void DisplayTime();
	//void HandleGlobalAch(int32 NumbOfStars);
	bool bTransitionHitBox;
	void HandleAchievements();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = JumpyFrogs)//used for sharing image to facebook temporary image variable
		UTexture2D* ScreenShot;

	TArray <int32> HS2StarsLimitArray;
	TArray <int32> HS3StarsLimitArray;
	bool bShowNormalAch;
	bool bShowGlobAch;
	bool bShowAch1Stars;
	bool bShowAch2Stars;
	bool bShowAch3Stars;
	void CheckWhatAch();

	void RecordGoogleEvent(FString Category, FString Action, FString Label, int32 Nmbr);
	void RecordGoogleScreen(FString ScreenName);

	bool bStartMenu = false;
	bool bDrawAskUser = false;

	bool bDrawHudIcons = false;
	bool bDrawAIActive = false;
	bool bDrawAiSolverMenu = false;
	bool bLevelWon = false;
	bool bLevelFailed = false;
	bool bDrawPauseMenu = false;

private:
	//USoundCue* CountdownSound;

	FString Price = TEXT("");

	bool bDrawAchBig;

	//FString FailedMessage;
	int32 UnlockedTips = 0;
	bool bLockedTip = false;
	bool bModeUnlocked = false;
	bool bDrawLock = false;
	bool bDrawCreditsNames = false;
	FLinearColor MyColor = FLinearColor(0.701f, 0.68f, 0.672f);
	FLinearColor MyColorDark = FColor::Black;
	void EnableClick();
	bool bCanClick = true;
	//void CheckWhatAch();
	//bool bWaitForPopups;


	int32 GlobAchIndex = 0;

	int32 StarsNumb = 0; //to use with posting image text to facebook, showing how many stars we have earned
	int32 FrameCount = 0; //to use with gif animation on uploading the image to facebook

	FString CheckOperSys();
	void DeleteAnyExistingScreenshots();
	//void RecordGoogleUserTiming(FString TimingCategory, int32 Nmbr, FString TimingName);

	void ConvertScrShotToImage();
	/** Crosshair asset pointer */
	//class UTexture2D* CrosshairTex;

	TArray <FString> AchievementsList;
	TArray <FString> AchievementsListiOS;

	float AchievUVx = 0.0f;
	float AchievUVy = 0.0f;

	bool bAdjustText;
	int32 StartCountdown = 3;
	float FontScale = 1.4f;
	//bool bShowStartCountdown = false;

	//bool bDrawAIMenu = false;
	//bool bDrawAiSolver = false;

	//bool bDrawBuyAiSolverMenu = false;
	//bool bDrawConfBuy = false;
	bool bDrawRestPurchase = false;

	bool bDrawLevelSelectMenu = false;
	bool bDrawLevelSelectMenu2 = false;
	bool bDrawLevelSelectMenu3 = false;
	bool bDrawLevelSelectMenu4 = false;
	bool bDraw4LevelsType = false;


	bool bDrawLibrary = false;
	bool bDrawCredits = false;

	bool bDrawClassicL = false;
	bool bDrawTeleporterL = false;
	bool bDrawTeleporterBombL = false;
	bool bDrawBombL = false;

	bool bDrawThankYou = false;
	bool bDrawPurchaseFailed = false;
	bool bDrawRestoreSuccessful = false;
	bool bDrawPleaseWait = false;
	bool bDrawRestoreFailed = false;





	//bool bDrawAchievement;
	bool bDrawAreYouSure = false;
	bool bDrawAreYouAbsSure = false;
	bool bDrawLoadingScreen = true;
	bool bDrawShareImage = false;

	bool bDrawFbLike = false;

	//bool bIsSoundOnOff;
	bool bSwissKnife = false;
	bool bSocialMedia = false;
	bool IsSaveProgressOn = false;
	bool bShowLangSel = false;
	bool bShowChineseSel = false;

	
	void ShowLangSel();
	void BeginAnalyticsSession();

	void LoadTextsAtStart();
	void LoadScrOff();
	bool CheckInAppPurchase();

	bool bSoundOn = true;

	FVector2D FlagUVPos = FVector2D::ZeroVector;
	uint8 SelLang = 0;

	UTexture2D* CreditsText;
	UTexture2D* ChinaLangSel;
	UTexture2D* Flags;
	UTexture2D* Achievements;
	UTexture2D* Stars;
	//  UTexture2D* TwoStars;
	//class UTexture2D* ThreeStars;

	UTexture2D* HUDbuttons1;	UTexture2D* HUDbuttons1b;
	UTexture2D* HUDbuttons2;	UTexture2D* HUDbuttonsBuy;
	//UTexture2D* HUDbuttons2b;
	//UTexture2D* HUDbuttons3;
	//class UTexture2D* GoBackArrow;

	UTexture2D* Arrows;
	UTexture2D* GreenLayer;
	UTexture2D* WideButton;
	//class UTexture2D* LevelFailedCleared;
	UTexture2D* LevelSelectFrontMenu;
	UTexture2D* LockTexture_256;
	//class UTexture2D* NextClose;
	//class UTexture2D* PlayIcon;
	UTexture2D* PlayLevelMenu_1;
	UTexture2D* PlayLevelMenu_2;
	UTexture2D* PlayLevelMenu_3;
	UTexture2D* PlayLevelMenu_4;
	//class UTexture2D* Classic_Background;
	void TurnSoundOnOff();
	void LoadScreenTexts();
	void LoadRatingLimits();
	UDataTable* RatingStarsDT;
	UDataTable* LibDataTable;
	UDataTable* LibDataTableSlovenian;
	UDataTable* LibDataTableChinese;
	UDataTable* LibDataTableTrChinese;
	UDataTable* ScreenTextDataTable;
	UDataTable* AchDT;


	TArray<FString> ScreenTexts;
	TArray<FString> AchievTexts;

};
