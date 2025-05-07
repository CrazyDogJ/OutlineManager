// Fill out your copyright notice in the Description page of Project Settings.


#include "OutlineActorComponent.h"

#include "OutlineSubsystem.h"
#include "Net/UnrealNetwork.h"

UOutlineActorComponent::UOutlineActorComponent()
{
	Properties = FOutlineCompProperties();
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
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

	// Ignore local pawn;
	if (GetOwner()->GetLocalRole() == ROLE_AutonomousProxy)
	{
		return;
	}
	
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
	Properties.IdentityGameplayTag.AddTag(Tag);
	OnRep_Properties();
}

bool UOutlineActorComponent::RemoveIdentityTag(FGameplayTag Tag)
{
	return Properties.IdentityGameplayTag.RemoveTag(Tag);
	OnRep_Properties();
}

void UOutlineActorComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetSubsystem<UOutlineSubsystem>()->RegisterOutlineComponent(this);
	GetWorld()->GetSubsystem<UOutlineSubsystem>()->ComponentUpdatedEvent.Broadcast(this);
}

void UOutlineActorComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UOutlineActorComponent, Properties);
}
