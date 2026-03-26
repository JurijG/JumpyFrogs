// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#include "GameInstances/JumpyFrogsGameInstance.h"

UJumpyFrogsGameInstance::UJumpyFrogsGameInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bTransitionCam = false;
	LevelNumber = 1;
	bIsCamHome = true;
	CamLocc = FVector(0.0f, 0.0f, 0.0f);
	Distancee = 512.0f;
	bFirstMapLoad = true;
	FlowerColors = {};
	bShowStartCountdown = false;
	bDrawAIActive = false;
	bDrawAIMenu = false;
	bDrawAiSolver = false;
	bDrawAiSolverMenu = false;
	bDrawHudIcons = false;
	bStartMenu = true;
	bTransitionHitBox = false;
	FlagUVPos = FVector2D(0.0f, 0.0f);
	IsAiActive = false;
	SelLang = 0;
	IsSaveProgressOn = true;
	bShouldSetFrogMats = true;
	//FrogColors = {};
	bFadeIn = true;

	AudioStartTime = 0.0f;
}
