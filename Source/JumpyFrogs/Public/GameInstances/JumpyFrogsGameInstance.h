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

	bool bIsSoundOnOff;

	int32 LevelNumber;
	bool bIsCamHome;
	FVector CamLocc;
	float  Distancee;
	bool bFirstMapLoad;
	bool IsAiActive;

	//Hud variables_:
	bool IsSaveProgressOn;
	bool bShowStartCountdown;
	bool bDrawAIActive;
	bool bDrawAIMenu;
	bool bDrawAiSolver;
	bool bDrawAiSolverMenu;
	bool bDrawHudIcons;
	bool bStartMenu;
	bool bTransitionHitBox;

	bool bFadeIn;
	bool bTransitionCam;
	float AudioStartTime;
	bool bShouldSetFrogMats;
	TArray<int32> FrogColors;
	TArray<int32> FlowerColors;

	//FString Language;
	int32 SelLang;
	FVector2D FlagUVPos;
};
