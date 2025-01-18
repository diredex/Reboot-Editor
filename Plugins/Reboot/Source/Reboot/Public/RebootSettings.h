// Copyright Ninth Spark Interactive, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Editor/EditorEngine.h"
#include "RebootSettings.generated.h"

// Configure Reboot Edior Settings.
UCLASS(Config = Editor, DefaultConfig)
class REBOOT_API URebootSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	// Constructor
	URebootSettings();

	// Category and Section for where this setting will appear in the Editor
	virtual FName GetCategoryName() const override { return TEXT("Plugins"); }
	virtual FName GetSectionName() const override { return TEXT("Reboot"); }

	// 1. Force Restart Default
	UPROPERTY(Config, EditAnywhere, Category = "General", meta = (DisplayName = "Force Restart by Default"))
	bool bForceRestartDefault;

	// 2. Check For Multiple Instances on Startup
	UPROPERTY(Config, EditAnywhere, Category = "Instance Management", meta = (DisplayName = "Check for Multiple Instances on Startup"))
	bool bCheckForMultipleInstances;

	// 3. Automatically Close Multiple Instances of the Project
	UPROPERTY(Config, EditAnywhere, Category = "Instance Management", meta = (DisplayName = "Automatically Close Multiple Instances"))
	bool bAutoCloseMultipleInstances;

	// 4. Allow Multiple Instances of the Same Project
	UPROPERTY(Config, EditAnywhere, Category = "Instance Management", meta = (DisplayName = "Allow Multiple Instances"))
	bool bAllowMultipleInstances;

	
protected:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	void PromptRestartEditor();
	void RestartEditor();
};
