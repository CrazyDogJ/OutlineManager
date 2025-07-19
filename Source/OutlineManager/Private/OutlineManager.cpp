// Copyright 2025 Vzen Lu. All Rights Reserved.

#include "OutlineManager.h"
#include "GameplayTagsManager.h"

#define LOCTEXT_NAMESPACE "FOutlineManagerModule"

void FOutlineManagerModule::StartupModule()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	Manager.AddNativeGameplayTag(FName("Outline.Identity.Item"));
	Manager.AddNativeGameplayTag(FName("Outline.Identity.Player"));
	Manager.AddNativeGameplayTag(FName("Outline.Identity.Temp"));
}

void FOutlineManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOutlineManagerModule, OutlineManager)