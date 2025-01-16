// Copyright Epic Games, Inc. All Rights Reserved.

#include "Reboot.h"
#include "RebootStyle.h"
#include "RebootCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformMisc.h"
#include "Misc/MessageDialog.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "Misc/CommandLine.h"

static const FName RebootTabName("Reboot");

#define LOCTEXT_NAMESPACE "FRebootModule"

void FRebootModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FRebootStyle::Initialize();
	FRebootStyle::ReloadTextures();

	FRebootCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FRebootCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FRebootModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FRebootModule::RegisterMenus));
}

void FRebootModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FRebootStyle::Shutdown();

	FRebootCommands::Unregister();
}

void FRebootModule::PluginButtonClicked()
{
	const FText DialogText = LOCTEXT("RestartEditorDialog", "Do you want to restart the editor?");
	const auto Result = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

	if (Result == EAppReturnType::Yes)
	{
		// Use Unreal Engine's built-in method to restart the editor
		FUnrealEdMisc::Get().RestartEditor(false); // 'false' prevents showing the crash reporter
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("User cancelled editor restart."));
	}
}

void FRebootModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FRebootCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FRebootCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRebootModule, Reboot)