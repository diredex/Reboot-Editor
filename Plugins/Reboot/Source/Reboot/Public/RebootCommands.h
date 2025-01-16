// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "RebootStyle.h"

class FRebootCommands : public TCommands<FRebootCommands>
{
public:

	FRebootCommands()
		: TCommands<FRebootCommands>(TEXT("Reboot"), NSLOCTEXT("Contexts", "Reboot", "Reboot Plugin"), NAME_None, FRebootStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
	TSharedPtr<FUICommandInfo> ForceRestartAction;
};
