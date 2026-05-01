//// FirebaseWrapper/Public/FirebaseManager.h
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "FirebaseManager.generated.h"
//
//// Forward declare Firebase App to avoid including full Firebase headers in a public header if possible
//// This is important for faster compile times and cleaner dependencies.
//namespace firebase {
//    class App;
//}
//
//UCLASS()
//class FIREBASEWRAPPER_API UFirebaseManager : public UObject
//{
//    GENERATED_BODY()
//
//public:
//     Constructor
//    UFirebaseManager();
//
//    // Destructor (important for cleaning up Firebase App)
//    virtual ~UFirebaseManager();
//
//    /**
//     * @brief Initializes Firebase for the current platform.
//     * Call this early in your game's lifecycle (e.g., GameInstance Init).
//     */
//    UFUNCTION(BlueprintCallable, Category = "Firebase")
//    void InitializeFirebase();
//
//    /**
//     * @brief Logs a custom Analytics event.
//     * @param EventName The name of the event to log.
//     * @param Params A map of string key-value pairs for event parameters.
//     */
//    UFUNCTION(BlueprintCallable, Category = "Firebase")
//    void LogAnalyticsEvent(const FString& EventName, const TMap<FString, FString>& Params);
//
//    // Add other Firebase functionalities here (e.g., Crashlytics, Remote Config)
//
//private:
//    firebase::App* FirebaseApp;
//
//    // Internal helper for Android configuration
//    void ConfigureFirebaseAndroid();
//    // Internal helper for iOS configuration
//    void ConfigureFirebaseIOS();
//};
//


#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FirebaseManager.generated.h"

// Forward declaration (good practice)
//namespace firebase {
//    class App;
//}

UCLASS()
class FIREBASEWRAPPER_API UFirebaseManager : public UObject
{
    GENERATED_BODY()

public:
    UFirebaseManager();

    //UFUNCTION(BlueprintCallable, Category = "Firebase")
   // void InitializeFirebase();
    void  TestFirebaseLink();

private:
    //firebase::App* FirebaseApp;
};