// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EmptySlot.generated.h"

class UBoxComponent;
UCLASS()
class JUMPYFROGS_API AEmptySlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEmptySlot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UBoxComponent* BoxMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
