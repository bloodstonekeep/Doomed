/*******************************************************
  * This file is part of project Doomed.
 *******************************************************/

using UnrealBuildTool;
using System.Collections.Generic;

public class DoomedEditorTarget : TargetRules
{
	public DoomedEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "Doomed" } );
	}
}
