// Fill out your copyright notice in the Description page of Project Settings.


#include "FirebaseSubsystem.h"
//#include "Logging/LogMacros.h"
#include "Subsystems/SubsystemCollection.h"
//#include "Subsystems/GameInstanceSubsystem.h"

#include "firebase/app.h"
#include "firebase/analytics.h"
//#include "firebase/crashlytics.h"

DEFINE_LOG_CATEGORY_STATIC(LogFirebase, Log, All);

void UFirebaseSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    UE_LOG(LogFirebase, Log, TEXT("FirebaseSubsystem Initialize"));
   // UE_LOG(LogFirebase, Warning, TEXT("FirebaseSubsystem Initialize"));

    InitFirebase();
}

void UFirebaseSubsystem::InitFirebase()
{
    if (bInitialized)
    {
        UE_LOG(LogFirebase, Warning, TEXT("Firebase already initialized - skipping"));
        return;
    }

    // -----------------------------
    // 1. Settings for Firebase App
    // -----------------------------
    firebase::AppOptions Options;
    Options.set_api_key("AIzaSyDtjpwPapiRUYzRv_xy8aJP5fkf-NDSCmU");
    Options.set_app_id("1:1039962166441:web:173c3cc49245ef37a385b8");
    Options.set_project_id("jumpyfrogs");
    Options.set_messaging_sender_id("1039962166441");
    Options.set_storage_bucket("jumpyfrogs.firebasestorage.app");

    //Options.set_auth("1039962166441");
    //Options.set_database_url("YOUR_DB_URL"); // optional

    // -----------------------------
    // 1. Create Firebase App
    // -----------------------------
 
    FirebaseApp = firebase::App::Create(Options);

    if (!FirebaseApp)
    {
        UE_LOG(LogFirebase, Error, TEXT("Failed to create Firebase App"));
        return;
    }

    UE_LOG(LogFirebase, Log, TEXT("Firebase App created successfully"));

    // -----------------------------
    // 2. Initialize Analytics
    // -----------------------------
    firebase::analytics::Initialize(*FirebaseApp);
    firebase::analytics::SetAnalyticsCollectionEnabled(true);
    UE_LOG(LogFirebase, Log, TEXT("Firebase Analytics initialized"));

    // -----------------------------
    // 3. Test Event
    // -----------------------------
    firebase::analytics::SetUserProperty("build", "sandbox");
    firebase::analytics::LogEvent("firebase_init_test");
    firebase::analytics::LogEvent("ue_boot_test");
    firebase::analytics::LogEvent("ue_second_test");
    firebase::analytics::LogEvent("ue_menu_open");

    UE_LOG(LogFirebase, Log, TEXT("Firebase test event sent"));

    bInitialized = true;
}

void UFirebaseSubsystem::Deinitialize()
{
    UE_LOG(LogFirebase, Log, TEXT("FirebaseSubsystem Deinitialize"));

    // Firebase SDK usually does NOT require manual shutdown,
    // but we clean pointer for safety.

    FirebaseApp = nullptr;
    bInitialized = false;

    Super::Deinitialize();
}