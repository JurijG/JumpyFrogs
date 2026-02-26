// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/FrogInterface.h"
#include "Frog.generated.h"


class USkeletalMeshComponent;
class UBoxComponent;
class UMaterialInstance;
//class UAnimMontage;
UENUM(BlueprintType)
enum class EFrogJump : uint8
{
	None			   UMETA(DisplayName = "None"),
	Right              UMETA(DisplayName = "Right"),
	Left               UMETA(DisplayName = "Left"),
	UpRight            UMETA(DisplayName = "Up Right"),
	UpLeft             UMETA(DisplayName = "Up Left"),
	DownRight          UMETA(DisplayName = "Down Right"),
	DownLeft           UMETA(DisplayName = "Down Left"),

	RightShortIn       UMETA(DisplayName = "Right - Short In"),
	RightShortOut      UMETA(DisplayName = "Right - Short Out"),
	RightShortInOut    UMETA(DisplayName = "Right - Short In/Out"),

	LeftShortIn        UMETA(DisplayName = "Left - Short In"),
	LeftShortOut       UMETA(DisplayName = "Left - Short Out"),
	LeftShortInOut     UMETA(DisplayName = "Left - Short In/Out"),

	LeftToDownLeft     UMETA(DisplayName = "Left To DownLeft"),
	RightToDownRight   UMETA(DisplayName = "Right To DownRight"),
	/*UpRightShortOut    UMETA(DisplayName = "Up Right - Short Out"),
	UpRightShortInOut  UMETA(DisplayName = "Up Right - Short In/Out"),
	UpRightShortIn     UMETA(DisplayName = "Up Right - Short In"),

	UpLeftShortOut     UMETA(DisplayName = "Up Left - Short Out"),
	UpLeftShortInOut   UMETA(DisplayName = "Up Left - Short In/Out"),
	UpLeftShortIn      UMETA(DisplayName = "Up Left - Short In"),*/

	DownRightShortOut  UMETA(DisplayName = "Down Right - Short Out"),
	DownRightShortInOut UMETA(DisplayName = "Down Right - Short In/Out"),
	DownRightShortIn   UMETA(DisplayName = "Down Right - Short In"),

	DownLeftShortOut   UMETA(DisplayName = "Down Left - Short Out"),
	DownLeftShortInOut UMETA(DisplayName = "Down Left - Short In/Out"),
	DownLeftShortIn    UMETA(DisplayName = "Down Left - Short In"),

	// New swap variants
	DownRightToDownLeft UMETA(DisplayName = "Down Right to Down Left"),
	DownLeftToDownRight UMETA(DisplayName = "Down Left to Down Right"),

	DownRightToRight	UMETA(DisplayName = "Down Right to Right"),
	DownRightToLeft		UMETA(DisplayName = "Down Right to Right"),
	DownLeftToRight		UMETA(DisplayName = "Down Left to Right"),
	DownLeftToLeft		UMETA(DisplayName = "Down Left to Left"),

};

UCLASS()
class JUMPYFROGS_API AFrog : public AActor, public IFrogInterface
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
	//TArray<UAnimMontage*> JumpAnims;

	//void Jump(const TArray<FVector> InMarkedSlots)
	void Jump_Implementation(const TArray<FVector>& InMarkedSlots);
	void Eliminate_Implementation();
	TArray<EFrogJump> MarkedJumpDirections;
	TArray<EFrogJump> MarkedJumps;
	TArray<FVector> MarkedSlots;
	uint8 CurrentJumpIndex = 0;
	void PerformJump();
	void AddMergedDirection(EFrogJump Single, EFrogJump Out, EFrogJump InOut, EFrogJump In, int32 RepeatCount);
	void GenerateMergedJumps();
	void AnalyzeInBetweenJumps();
	UFUNCTION()
	void OnAnyMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	/*UFUNCTION()
	void OnJumpMontageEnded(UAnimMontage* Montage, bool bInterrupted);*/
	
	UPROPERTY(EditDefaultsOnly, Category = "Jump Montages")
	TMap<EFrogJump, UAnimMontage*> JumpMontages;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpUpRightMontage;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpUpLeftMontage;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpDownRightMontage;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpDownLeftMontage;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpRightMontage;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpLeftMontage;

	UAnimMontage* JumpRightShortIn;
	UAnimMontage* JumpRightShortOut;
	UAnimMontage* JumpRightShortInOut;

	UAnimMontage* JumpLeftShortIn;
	UAnimMontage* JumpLeftShortOut;
	UAnimMontage* JumpLeftShortInOut;
	
	/*UAnimMontage* JumpUpRightShortOut;
	UAnimMontage* JumpUpRightShortInOut;
	UAnimMontage* JumpUpRightShortIn;

	UAnimMontage* JumpUpLeftShortOut;
	UAnimMontage* JumpUpLeftShortInOut;
	UAnimMontage* JumpUpLeftShortIn;*/

	UAnimMontage* JumpDownRightShortOut;
	UAnimMontage* JumpDownRightShortInOut;
	UAnimMontage* JumpDownRightShortIn;

	UAnimMontage* JumpDownLeftShortOut;
	UAnimMontage* JumpDownLeftShortInOut;
	UAnimMontage* JumpDownLeftShortIn;

	UAnimMontage* JumpDownRightToDownLeft;
	UAnimMontage* JumpDownLeftToDownRight;

	UAnimMontage* JumpDownRightToRight;
	UAnimMontage* JumpDownRightToLeft;
	UAnimMontage* JumpDownLeftToRight;
	UAnimMontage* JumpDownLeftToLeft;

	UPROPERTY(EditDefaultsOnly, Category = "Jump Montages")
	TMap<EFrogJump, UAnimMontage*> JumpMontageMap;
	
	//USkeletalMeshComponent* FrogSkelMesh;
	//USkeletalMeshComponent* FrogSkelMesh;
	//USkeletalMeshComponent* FrogLOD0;
	//USkeletalMeshComponent* FrogLOD0NoBones;
	//USkeletalMeshComponent* FrogLOD1;
	//USkeletalMeshComponent* FrogLOD2; //no bones
	UBoxComponent* BoxMesh;

	/*bool FirstClick = false;
	bool DoubleClick = false;
	bool IsThisBomb = false;
	bool bShrinkFrog = false;
	bool bEnlargeFrog = false;
	float FrogSizeTime = 1.0f;*/

	//void ReApplyMaterial(int32  WhichMaterial);
	//void ReApplyBlackMat();//Added this because sometimes after AI helper, next level has blue mat for bomb frog instead of black so we add this reapply
	
	
	UMaterial* MatBlue;
	UMaterialInstance* MatOrange;
	UMaterialInstance* MatGreen;
	UMaterialInstance* MatRedEye;
	UMaterialInstance* MatStrawberry;
	UMaterialInstance* MatBombFrog;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
