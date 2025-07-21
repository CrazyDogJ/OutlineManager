// Copyright 2025 Vzen Lu. All Rights Reserved.

#include "OutlineActorComponent.h"

#include "OutlineSubsystem.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Components/MeshComponent.h"

UOutlineActorComponent::UOutlineActorComponent()
{
	Properties = FOutlineCompProperties();
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UOutlineActorComponent::SetOutlineProperties(FOutlineCompProperties InProperty)
{
	Properties = InProperty;
	if (GetOwner()->HasAuthority())
	{
		OnRep_Properties();
	}
}

void UOutlineActorComponent::OnRep_Properties()
{
	GetWorld()->GetSubsystem<UOutlineSubsystem>()->ComponentUpdatedEvent.Broadcast(this);
}

void UOutlineActorComponent::ToggleOutline(bool bEnable)
{
	if (!GetOwner())
	{
		return;
	}

	// Should ignore self outline.
	if (Properties.bIgnoreSelf)
	{
		// Ignore local pawn
		if (GetOwner()->GetLocalRole() == ROLE_AutonomousProxy)
		{
			return;
		}
		// Ignore local pawn when listen server.
		if (auto OwnerPawn = Cast<APawn>(GetOwner()))
		{
			if (OwnerPawn->IsLocallyControlled())
			{
				return;
			}
		}
	}

	// Set stencil for every mesh component.
	auto Comps = GetOwner()->GetComponents();
	for (auto Comp : Comps)
	{
		if (auto MeshComp = Cast<UMeshComponent>(Comp))
		{
			MeshComp->SetRenderCustomDepth(bEnable);
			MeshComp->SetCustomDepthStencilValue(bEnable ? Properties.CustomStencilValue : 0);
		}
	}
}

void UOutlineActorComponent::AddIdentityTag(FGameplayTag Tag)
{
	if (Tag.IsValid())
	{
		Properties.IdentityGameplayTag.AddTag(Tag);
		OnRep_Properties();
	}
}

bool UOutlineActorComponent::RemoveIdentityTag(FGameplayTag Tag)
{
	if (Tag.IsValid())
	{
		if (Properties.IdentityGameplayTag.RemoveTag(Tag))
		{
			OnRep_Properties();
			return true;
		}
	}
	return false;
}

void UOutlineActorComponent::SetStencilValue(int StencilValue)
{
	if (Properties.CustomStencilValue != StencilValue)
	{
		Properties.CustomStencilValue = StencilValue;
		OnRep_Properties();
	}
}

void UOutlineActorComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetSubsystem<UOutlineSubsystem>()->RegisterOutlineComponent(this);
}

void UOutlineActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Properties.IdentityGameplayTag = FGameplayTagContainer::EmptyContainer;
	Properties.CustomStencilValue = -1;
	
	GetWorld()->GetSubsystem<UOutlineSubsystem>()->UnregisterOutlineComponent(this);
}

void UOutlineActorComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UOutlineActorComponent, Properties);
}
