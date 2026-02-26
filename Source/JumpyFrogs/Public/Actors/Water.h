// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Water.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class JUMPYFROGS_API AWater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UBoxComponent* Box;
	UStaticMeshComponent* WaterMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
