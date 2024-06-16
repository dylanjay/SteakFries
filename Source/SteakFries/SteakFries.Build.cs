// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SteakFries : ModuleRules
{
	public SteakFries(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"GameplayAbilities", 
			"Paper2D", 
			"AIModule",
		});

		PublicIncludePaths.AddRange(new string[]
		{
			"SteakFries",
			"SteakFries/Framework/Public",
            "SteakFries/Action/Public",
            "SteakFries/Health/Public",
            "SteakFries/Stage/Public",
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
