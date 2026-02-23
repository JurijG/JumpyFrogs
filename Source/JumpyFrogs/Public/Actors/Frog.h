// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Frog.generated.h"


class USkeletalMeshComponent;

UCLASS()
class JUMPYFROGS_API AFrog : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFrog();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//USkeletalMeshComponent* FrogMesh;
	TObjectPtr<USkeletalMeshComponent> FrogMesh;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	TArray<UAnimMontage*> JumpAnims;


	//USkeletalMeshComponent* FrogSkelMesh;
	//USkeletalMeshComponent* FrogLOD0;
	//USkeletalMeshComponent* FrogLOD0NoBones;
	//USkeletalMeshComponent* FrogLOD1;
	//USkeletalMeshComponent* FrogLOD2; //no bones

	bool FirstClick = false;
	bool DoubleClick = false;
	bool IsThisBomb = false;
	bool bShrinkFrog = false;
	bool bEnlargeFrog = false;
	float FrogSizeTime = 1.0f;

	void ReApplyMaterial(int32  WhichMaterial);
	void ReApplyBlackMat();//Added this because sometimes after AI helper, next level has blue mat for bomb frog instead of black so we add this reapply
	
	
	class UMaterial* MatBlue;
	class UMaterialInstance* MatOrange;
	class UMaterialInstance* MatGreen;
	class UMaterialInstance* MatRedEye;
	class UMaterialInstance* MatStrawberry;
	class UMaterialInstance* MatBombFrog;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
