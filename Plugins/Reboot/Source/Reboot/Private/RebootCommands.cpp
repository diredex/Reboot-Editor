// Copyright Epic Games, Inc. All Rights Reserved.

#include "RebootCommands.h"

#define LOCTEXT_NAMESPACE "FRebootModule"

void FRebootCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Reboot", "Execute Reboot action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
