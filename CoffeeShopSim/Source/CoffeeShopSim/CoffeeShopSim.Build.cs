// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CoffeeShopSim : ModuleRules
{
	public CoffeeShopSim(ReadOnlyTargetRules Target) : base(Target)
	{
		CppStandard = CppStandardVersion.Cpp20;  // Set to C++20
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Slate",
                "SlateCore",
                "InputCore",
				"UMG"
            }
        );
    }
}
