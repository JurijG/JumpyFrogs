// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/NiagaraSpawnInterface.h"
#include "NiagaraSpawner.generated.h"


class UNiagaraSystem;

UCLASS()
class JUMPYFROGS_API ANiagaraSpawner : public AActor, public INiagaraSpawnInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANiagaraSpawner();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	void SpawnNiagara_Implementation(ENiagaraFX NiagaraType, FVector SpawnLoc) override;

	UNiagaraSystem* TeleportIn;
	UNiagaraSystem* TeleportOut;
	UNiagaraSystem* WaterMagic;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
