// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpVisualizer.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class JUMPYFROGS_API AJumpVisualizer : public AActor
{
	GENERATED_BODY()
	AJumpVisualizer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTraceNiagaraVectorArray(TArray<FVector> TracePathLocations);
	void AddDestinationRing(FVector RingLocation, TArray<FVector> TracePathLocations);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRVisualizer")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VRVisualizer|Effects")
	//UNiagaraComponent* NS_TeleportRing; // NiagaraComponent;
	TArray<UNiagaraComponent*> NS_TeleportRingArray;  // NiagaraSystem;

	//// Niagara System to use
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VRVisualizer|Effects")
	UNiagaraComponent* NS_PlayAreaBounds;  */
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VRVisualizer|Effects")
	UNiagaraComponent* TeleportTraceNiagaraSystem; // NiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VRVisualizer|Effects")
	UNiagaraComponent* TeleportTraceNiagaraSystem2; // NiagaraSystem;

	/*UPROPERTY(VisibleAnywhere, Category = "VRVisualizer")
	UNiagaraActor* NS_TeleportRing;

	UPROPERTY(VisibleAnywhere, Category = "VRVisualizer")
	UNiagaraActor* NS_PlayAreaBounds;*/


};
