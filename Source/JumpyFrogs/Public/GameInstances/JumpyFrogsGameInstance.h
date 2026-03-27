// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JumpyFrogsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JUMPYFROGS_API UJumpyFrogsGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:


	UJumpyFrogsGameInstance(const FObjectInitializer& ObjectInitializer);

	//bTransitionCam = false;
	//LevelNumber = 1;
	//bIsCamHome = true;
	//Distancee = 512.0f;
	//FlowerColors = {};
	//bDrawHudIcons = false;
	//bStartMenu = true;
	//bTransitionHitBox = false;
	//FlagUVPos = FVector2D(0.0f, 0.0f);
	//IsAiActive = false;
	
	//IsSaveProgressOn = true;
	//bShouldSetFrogMats = true;
	////FrogColors = {};
	////bFadeIn = true;

	//AudioStartTime = 0.0f;

	bool bSoundOn = true;
	uint16 CurrentLevel = 1;
	bool bFirstMapLoad = true;
	uint8 SelLang = 0;

	//Hud variables_:
	//bool IsSaveProgressOn;
	//bool bDrawHudIcons = false;
	//bool bStartMenu;
	//bool bTransitionHitBox;

	//bool bFadeIn;
	//bool bTransitionCam;
	//float AudioStartTime;
	//bool bShouldSetFrogMats;
	//TArray<int32> FrogColors;
	//TArray<int32> FlowerColors;

	////FString Language;
	//int32 SelLang = 1;
	//FVector2D FlagUVPos;
};
