// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CoffeeShopSimTarget : TargetRules
{
	public CoffeeShopSimTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V6;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		bOverrideBuildEnvironment = true;
        CppStandard = CppStandardVersion.Cpp20;
        ExtraModuleNames.Add("CoffeeShopSim");
	}
}
