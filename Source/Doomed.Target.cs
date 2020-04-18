/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

using UnrealBuildTool;
using System.Collections.Generic;

public class DoomedTarget : TargetRules
{
	public DoomedTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Doomed" } );
	}
}
