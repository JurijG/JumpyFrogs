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

UENUM() //UENUM(BlueprintType)
enum class EJumpMontage : uint8
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
	RightShort    UMETA(DisplayName = "Right - Short "),

	LeftShortIn        UMETA(DisplayName = "Left - Short In"),
	LeftShortOut       UMETA(DisplayName = "Left - Short Out"),
	LeftShort     UMETA(DisplayName = "Left - Short "),

	LeftToDownLeft     UMETA(DisplayName = "Left To DownLeft"),
	RightToDownRight   UMETA(DisplayName = "Right To DownRight"),


	DownRightShortOut  UMETA(DisplayName = "Down Right - Short Out"),
	DownRightShort		 UMETA(DisplayName = "Down Right - Short"),
	DownRightShortIn   UMETA(DisplayName = "Down Right - Short In"),

	DownLeftShortOut   UMETA(DisplayName = "Down Left - Short Out"),
	DownLeftShort UMETA(DisplayName = "Down Left - Short "),
	DownLeftShortIn    UMETA(DisplayName = "Down Left - Short In"),

	// New swap variants
	DownRightToDownLeft UMETA(DisplayName = "Down Right to Down Left"),
	DownLeftToDownRight UMETA(DisplayName = "Down Left to Down Right"),

	/*These need animations:*/
	DownRightToRight	UMETA(DisplayName = "Down Right to Right"), //done
	DownRightToLeft		UMETA(DisplayName = "Down Right to Right"),
	DownLeftToRight		UMETA(DisplayName = "Down Left to Right"),
	DownLeftToLeft		UMETA(DisplayName = "Down Left to Left"),

	LeftShortInToDownLeft UMETA(DisplayName = "Down Left to Left"),
	LeftToDownRight	      UMETA(DisplayName = "Down Left to Left"),
	LeftShortToDownRight  UMETA(DisplayName = "Down Left to Left"),
	RightShortInToDownRight  UMETA(DisplayName = "Down Left to Left"),
	RightToDownLeft  UMETA(DisplayName = "Down Left to Left"),
	RightShortToDownLeft  UMETA(DisplayName = "Down Left to Left"),

	DownLeftShortToLeft  UMETA(DisplayName = "Down Left to Left"),
	DownLeftShortToDownRight  UMETA(DisplayName = "Down Left to Left"),
	DownRightShortToRight  UMETA(DisplayName = "Down Left to Left"),
	DownRightShortToDownLeft  UMETA(DisplayName = "Down Left to Left"),


	
	RightShortToDownRight  UMETA(DisplayName = ""),
	LeftShortToDownLeft  UMETA(DisplayName = ""),
	
	
	/*UpRightShortOut    UMETA(DisplayName = "Up Right - Short Out"),
	UpRightShort  UMETA(DisplayName = "Up Right - Short "),
	UpRightShortIn     UMETA(DisplayName = "Up Right - Short In"),

	UpLeftShortOut     UMETA(DisplayName = "Up Left - Short Out"),
	UpLeftShort   UMETA(DisplayName = "Up Left - Short "),
	UpLeftShortIn      UMETA(DisplayName = "Up Left - Short In"),*/
};

UENUM() //UENUM(BlueprintType)
enum class EJumpDirection : uint8
{
	None			   UMETA(DisplayName = "None"),
	Right              UMETA(DisplayName = "Right"),
	Left               UMETA(DisplayName = "Left"),
	UpRight            UMETA(DisplayName = "Up Right"),
	UpLeft             UMETA(DisplayName = "Up Left"),
	DownRight          UMETA(DisplayName = "Down Right"),
	DownLeft           UMETA(DisplayName = "Down Left"),

	//RightShortIn       UMETA(DisplayName = "Right - Short In"),
	//RightShortOut      UMETA(DisplayName = "Right - Short Out"),
	//RightShort    UMETA(DisplayName = "Right - Short "),

	//LeftShortIn        UMETA(DisplayName = "Left - Short In"),
	//LeftShortOut       UMETA(DisplayName = "Left - Short Out"),
	//LeftShort     UMETA(DisplayName = "Left - Short "),

	//LeftToDownLeft     UMETA(DisplayName = "Left To DownLeft"),
	//RightToDownRight   UMETA(DisplayName = "Right To DownRight"),
	///*UpRightShortOut    UMETA(DisplayName = "Up Right - Short Out"),
	//UpRightShort  UMETA(DisplayName = "Up Right - Short "),
	//UpRightShortIn     UMETA(DisplayName = "Up Right - Short In"),

	//UpLeftShortOut     UMETA(DisplayName = "Up Left - Short Out"),
	//UpLeftShort   UMETA(DisplayName = "Up Left - Short "),
	//UpLeftShortIn      UMETA(DisplayName = "Up Left - Short In"),*/

	//DownRightShortOut  UMETA(DisplayName = "Down Right - Short Out"),
	//DownRightShort UMETA(DisplayName = "Down Right - Short "),
	//DownRightShortIn   UMETA(DisplayName = "Down Right - Short In"),

	//DownLeftShortOut   UMETA(DisplayName = "Down Left - Short Out"),
	//DownLeftShort UMETA(DisplayName = "Down Left - Short "),
	//DownLeftShortIn    UMETA(DisplayName = "Down Left - Short In"),

	//// New swap variants
	//DownRightToDownLeft UMETA(DisplayName = "Down Right to Down Left"),
	//DownLeftToDownRight UMETA(DisplayName = "Down Left to Down Right"),

	//DownRightToRight	UMETA(DisplayName = "Down Right to Right"),
	//DownRightToLeft		UMETA(DisplayName = "Down Right to Right"),
	//DownLeftToRight		UMETA(DisplayName = "Down Left to Right"),
	//DownLeftToLeft		UMETA(DisplayName = "Down Left to Left"),

};

USTRUCT() //USTRUCT(BlueprintType)
struct FFrogJump
{
	GENERATED_BODY()
	
	EJumpDirection Prev = EJumpDirection::None;
	EJumpDirection Current = EJumpDirection::None;
	EJumpDirection Next = EJumpDirection::None;
	EJumpMontage MontageName = EJumpMontage::None;
	UAnimMontage* Montage;

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
	TArray<EJumpDirection> MarkedJumpDirections;

	TArray<FFrogJump> MappedJumps;
	TArray<UAnimMontage*> MarkedJumpAnims;
	TArray<EJumpMontage> MarkedJumps;

	TArray<FVector> MarkedSlots;

	uint8 CurrentJumpIndex = 0;
	void PerformJump();
	//void AddMergedDirection(EFrogJump Single, EFrogJump Out, EFrogJump InOut, EFrogJump In, int32 RepeatCount);
	void GenerateMergedJumps();
	UFUNCTION()
	void OnAnyMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	/*UFUNCTION()
	void OnJumpMontageEnded(UAnimMontage* Montage, bool bInterrupted);*/
	
	UPROPERTY(EditDefaultsOnly, Category = "Jump Montages")
	TMap<EJumpDirection, UAnimMontage*> JumpMontages;
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpUpRight;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpUpLeft;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpDownRight;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpDownLeft;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpRight;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animations)
	UAnimMontage* JumpLeft;

	UAnimMontage* JumpRightShortIn;
	UAnimMontage* JumpRightShortOut;
	UAnimMontage* JumpRightShort;

	UAnimMontage* JumpLeftShortIn;
	UAnimMontage* JumpLeftShortOut;
	UAnimMontage* JumpLeftShort;
	
	/*UAnimMontage* JumpUpRightShortOut;
	UAnimMontage* JumpUpRightShort;
	UAnimMontage* JumpUpRightShortIn;

	UAnimMontage* JumpUpLeftShortOut;
	UAnimMontage* JumpUpLeftShort;
	UAnimMontage* JumpUpLeftShortIn;*/

	UAnimMontage* JumpDownRightShortOut;
	UAnimMontage* JumpDownRightShort;
	UAnimMontage* JumpDownRightShortIn;

	UAnimMontage* JumpDownLeftShortOut;
	UAnimMontage* JumpDownLeftShort;
	UAnimMontage* JumpDownLeftShortIn;

	UAnimMontage* JumpDownRightToDownLeft;
	UAnimMontage* JumpDownLeftToDownRight;

	UAnimMontage* JumpDownRightToRight;
	UAnimMontage* JumpDownRightToLeft;
	UAnimMontage* JumpDownLeftToRight;
	UAnimMontage* JumpDownLeftToLeft;

	UAnimMontage* JumpLeftToDownLeft;
	UAnimMontage* JumpLeftShortInToDownLeft;

	UAnimMontage* JumpLeftToDownRight;
	UAnimMontage* JumpLeftShortToDownRight;

	UAnimMontage* JumpRightToDownRight;
	UAnimMontage* JumpRightShortInToDownRight;

	UAnimMontage* JumpRightToDownLeft;
	UAnimMontage* JumpRightShortToDownLeft;

	UAnimMontage* JumpDownLeftShortToLeft;
	UAnimMontage* JumpDownLeftShortToDownRight;

	UAnimMontage* JumpDownRightShortToRight;
	UAnimMontage* JumpDownRightShortToDownLeft;

	UAnimMontage* JumpRightShortToDownRight;
	UAnimMontage* JumpLeftShortToDownLeft;

	UPROPERTY(EditDefaultsOnly, Category = "Jump Montages")
	TMap<EJumpDirection, UAnimMontage*> JumpMontageMap;

	//TMap<TPair<EJumpDirection, EJumpDirection>> JumpTransitions;

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
