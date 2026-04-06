// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameModeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameModeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JUMPYFROGS_API IGameModeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/*UFUNCTION(BlueprintNativeEvent)
	void LoadNextLevel();*/

	/*UFUNCTION(BlueprintNativeEvent)
	bool ShouldTeleport(FVector FrogLoc) const;*/

	UFUNCTION(BlueprintNativeEvent)
	void LoadLevel(int32 LevelNumber);

	UFUNCTION(BlueprintNativeEvent)
	bool SaveLanguage();

	UFUNCTION(BlueprintNativeEvent)
	bool SaveGameDataToFile();

	UFUNCTION(BlueprintNativeEvent)
	bool IsMoveValidCheck(FVector Location);

	UFUNCTION(BlueprintNativeEvent)
	void RemoveFrogAddSlot(const FVector StartFrogLoc, const  FVector EndFrogLoc);

	UFUNCTION(BlueprintNativeEvent)
	void RemoveFrogsAndAddSlots(FVector SelectedFrogLoc, TArray<FVector>& InMarkedSlots);

	UFUNCTION(BlueprintNativeEvent)
	void FrogJumpingEnded(AActor* FrogInAction);
	//void FrogJumpingEnded(FVector FrogLoc);

	UFUNCTION(BlueprintNativeEvent)
	int32 GetScore() const;

	UFUNCTION(BlueprintNativeEvent)
	TArray<bool> GetUnlockedArray() const;

	UFUNCTION(BlueprintNativeEvent)
	TArray<int32> GetHighScoreArray() const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetCurrentLevel() const;

	UFUNCTION(BlueprintNativeEvent)
	bool GetAchievementUnlocked() const;

	UFUNCTION(BlueprintNativeEvent)
	bool GetBlockClicks() const;

	UFUNCTION(BlueprintNativeEvent)
	bool GetNewLevUnlocked() const;

	UFUNCTION(BlueprintNativeEvent)
	int32 GetAchIndex() const;

	
};
