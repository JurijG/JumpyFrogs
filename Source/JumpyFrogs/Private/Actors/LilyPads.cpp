// Fill out your copyright notice in the Description page of Project Settings.
#include "Actors/LilyPads.h"

// Sets default values
ALilyPads::ALilyPads()
{
	PrimaryActorTick.bCanEverTick = false;
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> LilyPadsMeshObj;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> LilyPadGreenMat;
		ConstructorHelpers::FObjectFinderOptional<UDataTable> LillyPadsDataTable_DT;
		//ConstructorHelpers::FObjectFinderOptional<UDataTable> ScoringDataTable_BP;
		FConstructorStatics()
			: LilyPadsMeshObj(TEXT("/Game/LilyPads/StaticMesh/LP_01"))
			, LilyPadGreenMat(TEXT("/Game/LilyPads/Materials/WaterLily_Pad_Green"))
			, LillyPadsDataTable_DT(TEXT("/Game/DataTables/LillyPadsMeshDataT.LillyPadsMeshDataT"))
			//, ScoringDataTable_BP(TEXT("/Game/DataTables/DataTableFloatMultiplier.DataTableFloatMultiplier"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	//UDataTable* LillyPadsDataTable;
	LillyPadsDataTable = ConstructorStatics.LillyPadsDataTable_DT.Get();
	//ScoringDataTable = ConstructorStatics.ScoringDataTable_BP.Get();
	// Create static mesh component
	LilyPadsMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LilyPadsMesh"));
	RootComponent = LilyPadsMesh;
	LilyPadsMesh->SetStaticMesh(ConstructorStatics.LilyPadsMeshObj.Get());
	LilyPadsMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	LilyPadsMesh->SetRelativeLocation(FVector(8.0f, 8.0f, 200.0f));
	LilyPadsMesh->SetMaterial(0, ConstructorStatics.LilyPadGreenMat.Get());
	//LilyPadsMesh->SetupAttachment(DummyRoot);//AttachTo(DummyRoot);
	LilyPadsMesh->bCastDynamicShadow = false;
}

// Called when the game starts or when spawned
void ALilyPads::BeginPlay()
{
	Super::BeginPlay();
	
}
void ALilyPads::ReApplyStaticMesh(int32 WhichMesh)
{
	UStaticMesh* NewMesh;
	TArray<FLillyPadsData*> LillyPadsRowList;
	//TArray<FStatScoringData*> StatScoringRowList;

	//	ScoringDataTable->GetAllRows<FStatScoringData>("Some Debug Message String if Fails", StatScoringRowList);
	////uncomment31fs:GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::SanitizeFloat(StatScoringRowList[3]->Multiplier));
	LillyPadsDataTable->GetAllRows<FLillyPadsData>("Some Debug Message String if Failes", LillyPadsRowList);

	const TCHAR* chars = *LillyPadsRowList[WhichMesh - 1]->LillyPadMeshAssetLink;
	//const TCHAR* chars = *LilyPadsList[WhichMesh];
	NewMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, chars));

	LilyPadsMesh->SetStaticMesh(NewMesh);
	this->SetActorEnableCollision(false);
}
