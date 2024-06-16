// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CoffeeShopSimEditorTarget : TargetRules
{
	public CoffeeShopSimEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        //bOverrideBuildEnvironment = true;
        ExtraModuleNames.Add("CoffeeShopSim");
	}
}
