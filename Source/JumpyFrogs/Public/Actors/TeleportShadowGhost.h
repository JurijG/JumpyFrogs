// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportShadowGhost.generated.h"

//class UStaticMeshComponent;
UCLASS()
class JUMPYFROGS_API ATeleportShadowGhost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportShadowGhost();
	void SetRelativeEndLocation(FVector FrogEndMeshLoc);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//float ElapsedTime = 0.f;

	/*FVector StartScale = FVector(1.f, 1.f, 1.f);
	FVector EndScale = FVector::ZeroVector;*/
	float StartOpacity = 1.0f;
	float EndOpacity = 0.0f;

	UMaterialInstanceDynamic* StartMID;
	UMaterialInstanceDynamic* EndMID;

	//void UpdateScale();
	void UpdateOpacity();

	USceneComponent* DummyRoot;
	//UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FrogStartMesh;

	//UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FrogEndMesh;


public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
