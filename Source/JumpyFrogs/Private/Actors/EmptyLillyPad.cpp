// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/EmptyLillyPad.h"

// Sets default values
AEmptyLillyPad::AEmptyLillyPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEmptyLillyPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEmptyLillyPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

