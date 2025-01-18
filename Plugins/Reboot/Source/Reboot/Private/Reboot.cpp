// Copyright Ninth Spark Interactive, Inc. All Rights Reserved.

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
#include "Editor/UnrealEd/Public/UnrealEdMisc.h"
#include "InstanceManager.h"
#include "ISettingsModule.h"
#include "RebootSettings.h"

static const FName RebootTabName("Reboot");

#define LOCTEXT_NAMESPACE "FRebootModule"

void FRebootModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	const URebootSettings* Settings = GetDefault<URebootSettings>();
	FRebootStyle::Initialize();
	FRebootStyle::ReloadTextures();

	FRebootCommands::Register();

	// Register the settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Editor",                  // Category
			"Plugins",                 // Section
			"Reboot",                  // Name
			LOCTEXT("RebootSettingsName", "Reboot Settings"),
			LOCTEXT("RebootSettingsDescription", "Configure Reboot plugin settings."),
			GetMutableDefault<URebootSettings>()
		);
	}
	
	PluginCommands = MakeShareable(new FUICommandList);
	
	// Map the Force Restart action to the ForceRestartEditor function
	PluginCommands->MapAction(
		FRebootCommands::Get().ForceRestartAction,
		FExecuteAction::CreateRaw(this, &FRebootModule::ForceRestartEditor)
	);


	if (Settings->bForceRestartDefault)
	{
		PluginCommands->MapAction(
		FRebootCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FRebootModule::ForceRestartEditor),
		FCanExecuteAction());
	}

	else
	{
		PluginCommands->MapAction(
		FRebootCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FRebootModule::PluginButtonClicked),
		FCanExecuteAction());
	}

	
	if (Settings->bCheckForMultipleInstances)
	{
		if (Settings->bAllowMultipleInstances)
		{
			if (!FInstanceManager::IsPrimaryInstance())
			{
				FText Message = FText::FromString(TEXT("Another Instance is Already running"));
    
				// Show the Yes/No dialog box
				EAppReturnType::Type Response = FMessageDialog::Open(EAppMsgType::Ok, Message);
			}
			
		}

		if (!Settings->bAllowMultipleInstances)
		{
			if (!FInstanceManager::IsPrimaryInstance())
			{
				if (Settings->bAutoCloseMultipleInstances)
				{
					FInstanceManager::ForceAcquireLock();
				}
				else
				{
					const FText DialogText = FText::FromString(
					"Another instance of this project is already running. Do you want to terminate it and continue?");
					const EAppReturnType::Type Result = FMessageDialog::Open(EAppMsgType::YesNo, DialogText);

					if (Result == EAppReturnType::Yes)
					{
						FInstanceManager::ForceAcquireLock();
					}
					else
					{
						FPlatformMisc::RequestExit(true); // Exit without errors
					}
				}
			}
		}
	}

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

	FInstanceManager::ReleaseLock();

	// Unregister the settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Editor", "Plugins", "Reboot");
	}
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

void FRebootModule::ForceRestartEditor()
{
	// Log the force restart action
	UE_LOG(LogTemp, Log, TEXT(" Force Restarting editor"));

	// Directly restart the editor without showing a confirmation dialog
	FUnrealEdMisc::Get().RestartEditor(false);
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
			
			Section.AddMenuEntryWithCommandList(
				FRebootCommands::Get().ForceRestartAction,
				PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FRebootCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);

				// TODO: Toolbar Force Restart Feature.
				// FToolMenuEntry& ForceRestartEntry = Section.AddEntry(
				// 	FToolMenuEntry::InitToolBarButton(FRebootCommands::Get().ForceRestartAction)
				// );
				// ForceRestartEntry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FRebootModule::PrintWarning(const FString& Message, float Duration)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Red, Message);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRebootModule, Reboot)