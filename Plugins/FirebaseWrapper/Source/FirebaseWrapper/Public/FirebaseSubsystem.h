// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "UObject/Object.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FirebaseSubsystem.generated.h"


//// Forward declare Firebase App to avoid including full Firebase headers in a public header if possible
//// This is important for faster compile times and cleaner dependencies.
namespace firebase {
    class App;
}

class FSubsystemCollectionBase;
/**
 * 
 */
UCLASS()
class FIREBASEWRAPPER_API UFirebaseSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

private:

    firebase::App* FirebaseApp = nullptr;
    bool bInitialized = false;

    void InitFirebase();
};
