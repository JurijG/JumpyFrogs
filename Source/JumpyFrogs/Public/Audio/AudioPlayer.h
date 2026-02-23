// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/AudioPlayerInterface.h"
#include "AudioPlayer.generated.h"


class USoundCue;

UCLASS()
class JUMPYFROGS_API AAudioPlayer : public AActor, public IAudioPlayerInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<USoundCue*> FrogSounds;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
