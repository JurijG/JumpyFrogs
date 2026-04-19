// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LilyPad.generated.h"

UCLASS()
class JUMPYFROGS_API ALilyPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALilyPad();

	//void SpawnLilyPads(TArray<FVector>& Locations);
	void AddLilyPad(FVector2D Location);

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	TArray<UStaticMeshComponent*> Pads;
	UMaterial* LilyPadBaseMat;
	UStaticMesh* PlaneMesh;

	USceneComponent* DummyRoot;
public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
