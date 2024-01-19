// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CoffeeShopSim : ModuleRules
{
	public CoffeeShopSim(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule" });

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Slate",
                "SlateCore",
                "InputCore"
            }
        );
    }
}
