// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Actors/EmptySlot.h"
#include "Components/BoxComponent.h"

// Sets default values
AEmptySlot::AEmptySlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxMesh = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxMesh->bHiddenInGame = false;
	BoxMesh->SetBoxExtent(FVector(50.f, 50.f, 10.f));
	BoxMesh->SetCollisionProfileName(TEXT("EmptySlotProfile"));

}

// Called when the game starts or when spawned
void AEmptySlot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEmptySlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

