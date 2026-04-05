// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"


class UNiagaraComponent;
UCLASS()
class JUMPYFROGS_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

	void RepositionTeleportersAndApplyMaterial(float StartRot, float EndRot, FVector TeleportEndLoc, int32 WhichMaterial, FVector EndLocation, FVector StartLocation);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UNiagaraComponent* NiagaraEffectStart;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UNiagaraComponent* NiagaraEffectEnd;

	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	///** Dummy root component */
	//UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* DummyRoot;

	//UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TeleporterStartMesh;

	//UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TeleporterEndMesh;

	//UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* LilyPadMesh;

	class UMaterial* TeleportMatStoneBase;
	class UMaterialInstance* TeleportMatBlue;
	class UMaterialInstance* TeleportMatYellow;
	class UMaterialInstance* TeleportMatPurple;
	class UMaterialInstance* TeleportMatGreen;

	

	FVector EndPosition;
	FVector TelEndLoc;
	FVector TelStartLoc;

	bool IsTelDead;
	/** Handle the slot being touched  */
	UFUNCTION()
	void OnFingerPressedTeleport(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void OnFingerPressedEndTeleport(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);
	UFUNCTION()
	void TeleporterStartClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);
	UFUNCTION()
	void TeleporterEndClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void TeleporterStartTouchedOrClicked();
	void TeleporterEndTouchedOrClicked();

//public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
