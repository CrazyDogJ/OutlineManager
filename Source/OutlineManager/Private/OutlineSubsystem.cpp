// Copyright 2025 Vzen Lu. All Rights Reserved.

#include "OutlineSubsystem.h"

void UOutlineSubsystem::AddVisibleTag(FGameplayTag AddGameplayTag)
{
	if (AddGameplayTag.IsValid())
	{
		VisibleGameplayTagContainer.AddTag(AddGameplayTag);
		VisibleTagsUpdatedEvent.Broadcast();
	}
}

bool UOutlineSubsystem::RemoveVisibleTag(FGameplayTag RemoveGameplayTag)
{
	bool Removed = VisibleGameplayTagContainer.RemoveTag(RemoveGameplayTag);
	
	if (Removed)
	{
		VisibleTagsUpdatedEvent.Broadcast();
	}
	
	return Removed;
}

void UOutlineSubsystem::ClearVisibleTag()
{
	if (!VisibleGameplayTagContainer.IsEmpty())
	{
		VisibleGameplayTagContainer = FGameplayTagContainer::EmptyContainer;
		VisibleTagsUpdatedEvent.Broadcast();
	}
}

void UOutlineSubsystem::SetVisibleTagContainer(FGameplayTagContainer Container)
{
	VisibleGameplayTagContainer = Container;
	VisibleTagsUpdatedEvent.Broadcast();
}

void UOutlineSubsystem::OnComponentUpdatedEvent(UOutlineActorComponent* UpdatedComponent)
{
	const bool Enable = VisibleGameplayTagContainer.HasAny(UpdatedComponent->Properties.IdentityGameplayTag);
	UpdatedComponent->ToggleOutline(Enable);
}

void UOutlineSubsystem::OnVisibleTagsUpdatedEvent()
{
	for (auto Itr : RegisteredOutlineActorComponents)
	{
		OnComponentUpdatedEvent(Itr);
	}
}

void UOutlineSubsystem::RegisterOutlineComponent(UOutlineActorComponent* OutlineActorComponent)
{
	RegisteredOutlineActorComponents.Add(OutlineActorComponent);
	ComponentUpdatedEvent.Broadcast(OutlineActorComponent);
}

void UOutlineSubsystem::UnregisterOutlineComponent(UOutlineActorComponent* OutlineActorComponent)
{
	RegisteredOutlineActorComponents.Remove(OutlineActorComponent);
	ComponentUpdatedEvent.Broadcast(OutlineActorComponent);
}

void UOutlineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ComponentUpdatedEvent.AddDynamic(this, &UOutlineSubsystem::OnComponentUpdatedEvent);
	VisibleTagsUpdatedEvent.AddDynamic(this, &UOutlineSubsystem::OnVisibleTagsUpdatedEvent);
}
