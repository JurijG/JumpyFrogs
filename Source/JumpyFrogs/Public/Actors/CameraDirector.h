// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class JUMPYFROGS_API ACameraDirector : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACameraDirector();

	// Called every frame
	//virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
	AActor* CameraOne;

	UPROPERTY(EditAnywhere)
	AActor* CameraTwo;

	UPROPERTY(EditAnywhere)
	AActor* CameraThree;
	UPROPERTY(EditAnywhere)
	AActor* CameraSky;

	float TimeToNextCameraChange;
	void SetCameraAtStart();
	//PROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	//class AJumpyFrogsGameModeBase* GameModeReference;
	//class UJumpyFrogsGameInstance* GameInstanceReference;
	void TurnOffbFirstMapLoad();

	float RunTime;
	float PlayTime;
	bool bTimeCounting;
	//float GetRunTime();

	//UPROPERTY()
	bool bGameOver;
	//UPROPERTY()
	bool startGameOverCount;
	//UPROPERTY()
	float timeTillGameOver;
	//UPROPERTY()
	float gameOverTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;



};

