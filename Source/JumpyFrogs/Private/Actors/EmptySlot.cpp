// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Actors/EmptySlot.h"
#include "Components/BoxComponent.h"

// Sets default values
AEmptySlot::AEmptySlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	Box->bHiddenInGame = false;
	Box->SetBoxExtent(FVector(100.f, 100.f, 10.f));	
	Box->SetCollisionProfileName(TEXT("EmptySlotProfile"));
	Box->ShapeColor = FColor::Orange;
	//Box->SetLineThickness(2.0f);
	RootComponent = Box;

}

// Called when the game starts or when spawned
void AEmptySlot::BeginPlay()
{
	Super::BeginPlay();
	
}
//
//FVector AEmptySlot::GetLocation_Implementation()
//{
//	return GetActorLocation();
//}
// Called every frame
void AEmptySlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

