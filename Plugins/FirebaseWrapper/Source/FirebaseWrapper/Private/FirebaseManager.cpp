//// FirebaseWrapper/Private/FirebaseManager.cpp
//
//#include "FirebaseManager.h" // This should always be the first include for a .cpp file
//
//// Include Firebase SDK headers
//#include "firebase/app.h"
//#include "firebase/analytics.h"
//// #include "firebase/crashlytics.h" // Uncomment this line when you add Crashlytics functionality
////
////// Platform-specific includes for configuration
////#if PLATFORM_ANDROID
////#include "Android/AndroidApplication.h"
////#include "Android/AndroidJNI.h"
////#elif PLATFORM_IOS
////#include "IOS/IOSAppDelegate.h"
////#endif
////
////// Guard against compiling Firebase code on unsupported platforms (like Editor/Windows standalone
////// unless specifically set up to handle it, which is more advanced).
////// For now, we only enable Firebase C++ SDK code for Android and iOS builds.
////#if PLATFORM_ANDROID || PLATFORM_IOS
////
////// Constructor
////UFirebaseManager::UFirebaseManager()
////    : FirebaseApp(nullptr) // Initialize FirebaseApp pointer to null
////{
////}
////
////// Destructor
////UFirebaseManager::~UFirebaseManager()
////{
////    if (FirebaseApp)
////    {
////        // Clean up the Firebase App instance when the manager is destroyed
////        delete FirebaseApp;
////        FirebaseApp = nullptr;
////    }
////}
////
////void UFirebaseManager::InitializeFirebase()
////{
////    if (FirebaseApp)
////    {
////        UE_LOG(LogTemp, Warning, TEXT("Firebase App already initialized. Skipping initialization."));
////        return;
////    }
////
////    UE_LOG(LogTemp, Log, TEXT("Attempting to initialize Firebase..."));
////
////    // firebase::App::Options options; // This line might not be needed as CreateAppOptions handles it
////
////    // Call platform-specific configuration helpers (these are mostly placeholders for now)
////#if PLATFORM_ANDROID
////    ConfigureFirebaseAndroid();
////#elif PLATFORM_IOS
////    ConfigureFirebaseIOS();
////#else
////    // This block should ideally not be reached if the #if PLATFORM_ANDROID || PLATFORM_IOS guard is working.
////    // Included for defensive programming.
////    UE_LOG(LogTemp, Warning, TEXT("Firebase C++ SDK initialization for this platform is not fully implemented."));
////    return;
////#endif
////
////    // Retrieve default options. The Firebase C++ SDK typically finds
////    // google-services.json (Android) or GoogleService-Info.plist (iOS) implicitly
////    // if they are packaged correctly into the app's assets/resources.
////    firebase::AppOptions options = firebase::App::CreateAppOptions();
////    if (options.app_id().empty()) {
////        UE_LOG(LogTemp, Error, TEXT("Firebase App Options could not be loaded. Ensure google-services.json (Android) or GoogleService-Info.plist (iOS) are correctly configured and packaged."));
////        return;
////    }
////
////    // Create the Firebase App instance
////    FirebaseApp = firebase::App::Create(options);
////
////    if (FirebaseApp)
////    {
////        UE_LOG(LogTemp, Log, TEXT("Firebase App initialized successfully!"));
////
////        // Initialize Firebase Analytics
////        firebase::analytics::Initialize(*FirebaseApp);
////        UE_LOG(LogTemp, Log, TEXT("Firebase Analytics initialized."));
////
////        // Initialize Firebase Crashlytics (uncomment the include at the top and this line when ready)
////        // firebase::crashlytics::Initialize(*FirebaseApp);
////        // UE_LOG(LogTemp, Log, TEXT("Firebase Crashlytics initialized."));
////    }
////    else
////    {
////        UE_LOG(LogTemp, Error, TEXT("Failed to initialize Firebase App. Please check your project setup and configuration files."));
////    }
////}
////
////void UFirebaseManager::LogAnalyticsEvent(const FString& EventName, const TMap<FString, FString>& Params)
////{
////    if (!FirebaseApp)
////    {
////        UE_LOG(LogTemp, Warning, TEXT("Firebase App not initialized. Cannot log event: %s"), *EventName);
////        return;
////    }
////
////    // Convert FString parameters to std::string for Firebase C++ SDK
////    std::vector<firebase::analytics::Parameter> parameters;
////    for (const auto& KVP : Params)
////    {
////        parameters.push_back(firebase::analytics::Parameter(
////            TCHAR_TO_UTF8(*KVP.Key), TCHAR_TO_UTF8(*KVP.Value) // TCHAR_TO_UTF8 converts FString to const char*
////        ));
////    }
////
////    // Log the event
////    firebase::analytics::LogEvent(TCHAR_TO_UTF8(*EventName), parameters.data(), parameters.size());
////    UE_LOG(LogTemp, Log, TEXT("Logged Firebase Analytics event: %s with %d parameters."), *EventName, parameters.size());
////}
////
////// Android-specific configuration helper (currently a placeholder)
////void UFirebaseManager::ConfigureFirebaseAndroid()
////{
////#if PLATFORM_ANDROID
////    // The Firebase C++ SDK typically handles finding google-services.json itself
////    // when firebase::App::CreateAppOptions() is called.
////    // If you ever needed to explicitly pass JNI environment variables, you would do it here:
////    // FJavaVM* JavaVM = FAndroidApplication::GetJavaVM();
////    // JNIEnv* Env = FAndroidApplication::GetJNIEnv();
////    // firebase::App::Set ;
////    // firebase::App::SetActivity(Env, FAndroidApplication::GetGameActivity());
////#endif
////}
////
////// iOS-specific configuration helper (currently a placeholder)
////void UFirebaseManager::ConfigureFirebaseIOS()
////{
////#if PLATFORM_IOS
////    // Similar to Android, firebase::App::CreateAppOptions() typically finds GoogleService-Info.plist.
////    // No explicit configuration is usually needed here for basic setup, but this function
////    // serves as a placeholder for more advanced iOS-specific configurations if required.
////#endif
////}
////
////#else // This block executes if not PLATFORM_ANDROID or PLATFORM_IOS
////// Placeholder implementations for platforms where Firebase C++ SDK is not compiled
////// This prevents compilation errors if you try to use the manager on, say, Windows Editor.
////UFirebaseManager::UFirebaseManager() : FirebaseApp(nullptr) {}
////UFirebaseManager::~UFirebaseManager() {}
////void UFirebaseManager::InitializeFirebase() { UE_LOG(LogTemp, Warning, TEXT("Firebase C++ SDK not enabled for this platform. InitializeFirebase called but will do nothing.")); }
////void UFirebaseManager::LogAnalyticsEvent(const FString& EventName, const TMap<FString, FString>& Params) { UE_LOG(LogTemp, Warning, TEXT("Firebase C++ SDK not enabled for this platform. LogAnalyticsEvent called but will do nothing.")); }
////void UFirebaseManager::ConfigureFirebaseAndroid() {}
////void UFirebaseManager::ConfigureFirebaseIOS() {}
////#endif // PLATFORM_ANDROID || PLATFORM_IOS


#include "FirebaseManager.h"

//#include "firebase/app.h"
//#include "firebase/analytics.h"
//#include "firebase/crashlytics.h"

UFirebaseManager::UFirebaseManager()    
{
    //firebase::App* App = firebase::App::Create();

    //firebase::analytics::Initialize(*App);
    //firebase::analytics::LogEvent("firebase_init_test");

    //firebase::crashlytics::Log("Crashlytics initialized");
}
//UFirebaseManager::UFirebaseManager()
//    : FirebaseApp(nullptr)
//{
//    firebase::App* App = firebase::App::Create();
//}

//void UFirebaseManager::InitializeFirebase()
//{
//    FirebaseApp = firebase::App::Create();
//}
void TestFirebaseLink()
{
    //const char* AppName = firebase::kDefaultAppName;
    
   // firebase::App* App = firebase::App::Create();
    //firebase::
    // 
    //  = firebase::kInitResultSuccess;
    //int count = firebase::
    //auto version = firebase::AppOptions::set_project_id());//  GetVersionString();
}