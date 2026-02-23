
#include "Actors/CameraDirector.h"
#include "Kismet/GameplayStatics.h"
#include "JumpyFrogsGameMode.h"
#include "GameInstances/JumpyFrogsGameInstance.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bTimeCounting = false;
	PlayTime = 0.0f;
	RunTime = 0.0f;

	bGameOver = false;
	startGameOverCount = false;
	timeTillGameOver = 2.0f;
	gameOverTimer = 0.0f;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	class AJumpyFrogsGameMode* GameModeReference = (AJumpyFrogsGameMode*)GetWorld()->GetAuthGameMode();
	GameModeReference->CamDirector = this;
	//GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	FTimerHandle ch334;
	GetWorld()->GetTimerManager().SetTimer(ch334, this, &ACameraDirector::SetCameraAtStart, 0.05f, false);
	//////SetCameraAtStart();
}
void ACameraDirector::SetCameraAtStart()
{
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	class UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	if (GameInstanceReference->bFirstMapLoad)
	{
		if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
		{
			// Cut instantly to camera one.
			OurPlayerController->SetViewTarget(CameraOne);
			FTimerHandle ch3;
			GetWorld()->GetTimerManager().SetTimer(ch3, this, &ACameraDirector::TurnOffbFirstMapLoad, 0.5f, false);
			//GameInstanceReference->bFirstMapLoad = false;
		}
	}
	else
	{
		class AJumpyFrogsGameMode* GameModeReference = (AJumpyFrogsGameMode*)GetWorld()->GetAuthGameMode();
		if (GameModeReference->bIsCameraHome)
		{
			OurPlayerController->SetViewTarget(CameraOne);
			GameModeReference->bIsCameraHome = false;
		}
		else
		{
			//GameModeReference->AdjustCamera();
			OurPlayerController->SetViewTarget(CameraTwo);
		}
		//const float SmoothBlendTime = 2.25f;
		GameModeReference->CamLoc.Z = GameModeReference->Distance + 512.0f;
		this->CameraTwo->SetActorLocation(GameModeReference->CamLoc);
		//OurPlayerController->SetViewTargetWithBlend(this->CameraTwo, SmoothBlendTime);
		OurPlayerController->SetViewTarget(this->CameraTwo);
	}
}

void ACameraDirector::TurnOffbFirstMapLoad()
{
	class UJumpyFrogsGameInstance* GameInstanceReference = (UJumpyFrogsGameInstance*)GetWorld()->GetGameInstance();
	GameInstanceReference->bFirstMapLoad = false;
}

/*
// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
Super::BeginPlay();

}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
Super::Tick(DeltaTime);

}*/

void ACameraDirector::Tick(float DeltaSeconds)
{
	//Super::Tick(DeltaSeconds);
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::SanitizeFloat(DeltaSeconds));

	RunTime += DeltaSeconds;
	int32 ttt = (int32)DeltaSeconds;
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::FromInt(ttt));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::SanitizeFloat(RunTime));
	if (!startGameOverCount)
	{
		if (bTimeCounting)
		{
			PlayTime += DeltaSeconds;
		}
	}
	else
	{
		gameOverTimer += DeltaSeconds;
		if (gameOverTimer >= timeTillGameOver)
			bGameOver = true;

	}
}