// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LilyPads.generated.h"

UCLASS()
class JUMPYFROGS_API ALilyPads : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALilyPads();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ReApplyStaticMesh(int32 WhichMesh);

	/** StaticMesh component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LilyPadsMesh;

public:	
	UDataTable* LillyPadsDataTable;
};

USTRUCT(BlueprintType)
struct FLillyPadsData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	/*
	FLillyPadsData()
	: LillyPadMeshAssetLink(0)
	{}*/

	// The 'Name' column is the same as the XP Level 

	//XP to get to the given level from the previous level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
	FString LillyPadMeshAssetLink;
};
//
//USTRUCT()
//struct FAiSolverList : public FTableRowBase
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//
//	FAiSolverList()
//		: AiOrder({ 0 })
//		, AiLevel({ FVector2D(0.0f,0.0f), FVector2D(0.0f,0.0f) })
//	{}
//
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ai Solver")
//	TArray<int32> AiOrder;
//	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ai Solver")
//	TArray<FVector2D> AiLevel;
//	//FVector2D AiLevel;
//	// FVector2D TestVector;
//	//int32 IntegerTest;
//	//TArray<FVector2D> AiOrder;
//
//};
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
	{}

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
	{}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	int32 NumOfBombsList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	TArray<float> TelDataList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnLevels")
	TArray<FVector> TeleportersList;
};
