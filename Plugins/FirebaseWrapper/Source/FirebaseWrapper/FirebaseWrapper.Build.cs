//// Copyright Epic Games, Inc. All Rights Reserved.

//using UnrealBuildTool;

//public class FirebaseWrapper : ModuleRules
//{
//	public FirebaseWrapper(ReadOnlyTargetRules Target) : base(Target)
//	{
//		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

//		PublicIncludePaths.AddRange(
//			new string[] {
//				// ... add public include paths required here ...
//			}
//			);


//		PrivateIncludePaths.AddRange(
//			new string[] {
//				// ... add other private include paths required here ...
//			}
//			);


//		PublicDependencyModuleNames.AddRange(
//			new string[]
//			{
//				"Core",
//				// ... add other public dependencies that you statically link with here ...
//			}
//			);


//		PrivateDependencyModuleNames.AddRange(
//			new string[]
//			{
//				"CoreUObject",
//				"Engine",
//				"Slate",
//				"SlateCore",
//				// ... add private dependencies that you statically link with here ...	
//			}
//			);


//		DynamicallyLoadedModuleNames.AddRange(
//			new string[]
//			{
//				// ... add any modules that your module loads dynamically here ...
//			}
//			);
//	}
//}

using UnrealBuildTool;
using System.IO;

public class FirebaseWrapper : ModuleRules
{
    public FirebaseWrapper(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // Path to your extracted Firebase C++ SDK
        string ThirdPartyPath = Path.GetFullPath(
            Path.Combine(ModuleDirectory, "../../ThirdParty/FirebaseSDK")
        );

        //// IMPORTANT: include root must contain "firebase/"
        string FirebaseIncludePath = Path.Combine(ThirdPartyPath, "Include");

        PublicSystemIncludePaths.Add(FirebaseIncludePath);



        //Target.bOverrideBuildEnvironment = true;

        // Core Unreal modules
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine"
            }
        );
        //PublicIncludePaths.AddRange(
        //   new string[] {
        //      Path.Combine(ModuleDirectory, "include")
        // });

        // Windows-specific definitions
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // PublicDefinitions.Add("INTERNAL_EXPERIMENTAL=0");
            // PublicDefinitions.Add("INTERNAL_EXPERIMENTAL=0");


            string FirebaseLibPath = Path.Combine(
                ThirdPartyPath,
                "libs",
                "windows",
                "VS2022", //"VS2019",
                "MD",
                "x64",
                "Release"
            );


            PublicAdditionalLibraries.Add(Path.Combine(FirebaseLibPath, "flatbuffers.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(FirebaseLibPath, "firebase_app.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(FirebaseLibPath, "firebase_analytics.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(FirebaseLibPath, "zlibstatic.lib"));
            //bUseStaticCRT = false;

            //PublicSystemLibraries.Add("zlibstatic.lib");
            //PublicDependencyModuleNames.Add("zlib");
            //PublicSystemLibraries.Add("zlib.lib");

            //PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "firebase_app.lib"));


            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicSystemLibraries.AddRange(new string[]
                {
                    "Crypt32.lib",
                    "Secur32.lib",
                    "Ws2_32.lib",
                    "Winhttp.lib",
                    "Bcrypt.lib",
                    "Advapi32.lib"
                });
            }

            //PublicSystemLibraries.Add(Path.Combine("crypt32.lib"));
            // PublicSystemLibraries.Add("crypt32.lib");


            //PublicSystemLibraries.Add(Path.Combine("ws2_32.lib"));
            //PublicSystemLibraries.Add(Path.Combine("wldap32.lib"));

            //PublicSystemLibraries.Add(Path.Combine("userenv.lib"));
            //PublicSystemLibraries.Add(Path.Combine("iphlpapi.lib"));
            //PublicSystemLibraries.Add(Path.Combine("psapi.lib"));
            //PublicSystemLibraries.Add(Path.Combine("dbghelp.lib"));
            //PublicSystemLibraries.Add(Path.Combine("bcrypt.lib"));

            //PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "firebase_app.lib"));
            //PublicAdditionalLibraries.Add(
            //   Path.Combine(FirebaseLibPath, "firebase_analytics.lib"));
            //PublicAdditionalLibraries.Add(
            //   Path.Combine(FirebaseLibPath, "firebase_auth.lib"));
            // DO NOT link Firebase libs yet (we fix this later step-by-step)
        }
    }
}