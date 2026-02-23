// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Audio/AudioPlayer.h"
#include "Sound/SoundCue.h"

// Sets default values
AAudioPlayer::AAudioPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<USoundCue> RandomFrogCallObj;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> TreeFrogCallObj;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> StrawberyDartFrogCallObj;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> GoldenFrogCallObj;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> BlueDartFrogCallObj;
		//ConstructorHelpers::FObjectFinderOptional<USoundCue> WickSound;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> BombFrogObj;
		//ConstructorHelpers::FObjectFinderOptional<USoundCue> SelectedLoop;
		FConstructorStatics()
			: RandomFrogCallObj(TEXT("/Game/Audio/Frogs/RandomFrogCall_Cue"))
			, TreeFrogCallObj(TEXT("/Game/Audio/Frogs/TreeFrogCall1_Cue"))
			, StrawberyDartFrogCallObj(TEXT("/Game/Audio/Frogs/StrawberyDartFrogCall_Cue"))
			, GoldenFrogCallObj(TEXT("/Game/Audio/Frogs/GoldenFrogCall_Cue"))
			, BlueDartFrogCallObj(TEXT("/Game/Audio/Frogs/BlueDartFrogCall1_Cue"))
			, BombFrogObj(TEXT("/Game/Audio/Frogs/BombFrog_Cue"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	FrogSounds.Add(ConstructorStatics.RandomFrogCallObj.Get());
	FrogSounds.Add(ConstructorStatics.TreeFrogCallObj.Get());
	FrogSounds.Add(ConstructorStatics.StrawberyDartFrogCallObj.Get());
	FrogSounds.Add(ConstructorStatics.GoldenFrogCallObj.Get());
	FrogSounds.Add(ConstructorStatics.BlueDartFrogCallObj.Get());
	FrogSounds.Add(ConstructorStatics.BombFrogObj.Get());
}

// Called when the game starts or when spawned
void AAudioPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAudioPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

