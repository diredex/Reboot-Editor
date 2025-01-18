// Copyright Epic Games, Inc. All Rights Reserved.

#include "RebootStyle.h"
#include "Reboot.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FRebootStyle::StyleInstance = nullptr;

void FRebootStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FRebootStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FRebootStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("RebootStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FRebootStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("RebootStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("Reboot")->GetBaseDir() / TEXT("Resources"));

	Style->Set("Reboot.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	Style->Set("Reboot.ForceRestartAction", new IMAGE_BRUSH_SVG(TEXT("forcerestarticon"), Icon20x20));
	return Style;
}

void FRebootStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FRebootStyle::Get()
{
	return *StyleInstance;
}
