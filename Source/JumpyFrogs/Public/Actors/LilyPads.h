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



	void ReApplyStaticMesh(int32 WhichMesh);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
