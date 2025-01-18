#include "RebootSettings.h"

URebootSettings::URebootSettings()
	: bForceRestartDefault(false)           // Default: Force restart is disabled
	, bCheckForMultipleInstances(true)      // Default: Check for multiple instances
	, bAutoCloseMultipleInstances(false)    // Default: Do not auto-close by default
	, bAllowMultipleInstances(true)         // Default: Allow multiple instances
{
}

void URebootSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// Check if a property was changed
	if (PropertyChangedEvent.Property)
	{
		// Prompt the user to restart the editor
		PromptRestartEditor();
	}
}

void URebootSettings::PromptRestartEditor()
{
	FText Message = FText::FromString(TEXT("The settings have been changed. Would you like to restart the editor to apply them?"));
    
	// Show the Yes/No dialog box
	EAppReturnType::Type Response = FMessageDialog::Open(EAppMsgType::YesNo, Message);
    
	if (Response == EAppReturnType::Yes)
	{
		RestartEditor();
	}
}

void URebootSettings::RestartEditor()
{
	// Restart the editor
	FUnrealEdMisc::Get().RestartEditor(false);
}
