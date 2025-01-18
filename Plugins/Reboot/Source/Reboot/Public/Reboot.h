// Copyright Ninth Spark Interactive, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Engine/Engine.h"

class FToolBarBuilder;
class FMenuBuilder;

class FRebootModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	void ForceRestartEditor();
	
private:

	void RegisterMenus();
	void PrintWarning(const FString& Message, float Duration = 0.f);


private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
