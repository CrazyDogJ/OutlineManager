// Copyright 2025 Vzen Lu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "OutlineActorComponent.generated.h"

USTRUCT(BlueprintType)
struct FOutlineCompProperties
{
	GENERATED_BODY()

	// If visible tag updated, the stencil value we enabled.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Outline")
	int CustomStencilValue;

	// Visible identity gameplay tags.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Outline")
	FGameplayTagContainer IdentityGameplayTag;

	// Should we ignore self controlled pawn's stencil settings?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Outline")
	bool bIgnoreSelf = true;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class OUTLINEMANAGER_API UOutlineActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOutlineActorComponent();

	// Update outline properties in runtime
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Outline")
	void SetOutlineProperties(FOutlineCompProperties InProperty);

	// Set outline properties by default. If you want to set it runtime, please call SetOutlineProperties.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, ReplicatedUsing=OnRep_Properties, Category = "Outline")
	FOutlineCompProperties Properties;

	UFUNCTION()
	void OnRep_Properties();

	// You can toggle outline by your self
	UFUNCTION(BlueprintCallable, Category = "Outline")
	void ToggleOutline(bool bEnable);

	// Add visible identity tag to container
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Outline")
	void AddIdentityTag(FGameplayTag Tag);

	// Remove visible identity tag in container
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Outline")
	bool RemoveIdentityTag(FGameplayTag Tag);

	// Set stencil value
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Outline")
	void SetStencilValue(int StencilValue);
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
