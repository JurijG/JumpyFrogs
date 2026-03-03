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

	int32 CurrentLevel = 100; //  100 -> TESTLEVEL;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 FrogsRemaining = 0;
	TArray <AFrog*> FrogsArray;
	TArray <AEmptySlot*> TheSlotsArray;
	//TArray <AEmptySlot*> TheSlotsArray;

#pragma region DataTableVars
	//UDataTable* AiLevelsDT;
	UDataTable* TelAndBombsDT;
	UDataTable* SpawnLevelsDT;

#pragma endregion

#pragma region SpawningLevels
	
	void AddFrog(FVector2D Pos);

	void AddSlot(FVector2D Pos);

	bool IsMoveValidCheck_Implementation(FVector Location);
	void RemoveFrogsAndAddSlots_Implementation(FVector SelectedFrogLoc, TArray<FVector>& InMarkedSlots);
	void SpawnFrogsAndProps(int32 SelectedLevel);


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

