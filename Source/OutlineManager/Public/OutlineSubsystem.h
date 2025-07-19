// Copyright 2025 Vzen Lu. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OutlineActorComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "OutlineSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOutlineActorComponentUpdate, UOutlineActorComponent*, UpdatedComponent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutlineVisibleTagsUpdated);

/**
 * 
 */
UCLASS()
class OUTLINEMANAGER_API UOutlineSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TSet<UOutlineActorComponent*> RegisteredOutlineActorComponents;

	UPROPERTY()
	FGameplayTagContainer VisibleGameplayTagContainer;
	
public:
#pragma region Getter
	UFUNCTION(BlueprintCallable, Category = "Outline|Subsystem")
	TArray<UOutlineActorComponent*> GetRegisteredOutlineComponents() const {return RegisteredOutlineActorComponents.Array();}

	UFUNCTION(BlueprintCallable, Category = "Outline|Subsystem")
	FGameplayTagContainer GetVisibleGameplayTagContainer() const {return VisibleGameplayTagContainer;}
#pragma endregion
#pragma region VisibleTagsUpdateFunctions
	UFUNCTION(BlueprintCallable, Category = "Outline|Subsystem")
	void AddVisibleTag(FGameplayTag AddGameplayTag);

	UFUNCTION(BlueprintCallable, Category = "Outline|Subsystem")
	bool RemoveVisibleTag(FGameplayTag RemoveGameplayTag);

	UFUNCTION(BlueprintCallable, Category = "Outline|Subsystem")
	void ClearVisibleTag();

	UFUNCTION(BlueprintCallable, Category = "Outline|Subsystem")
	void SetVisibleTagContainer(FGameplayTagContainer Container);
#pragma endregion
#pragma region Events
	UPROPERTY(BlueprintAssignable, Category = "Outline|Subsystem")
	FOnOutlineActorComponentUpdate ComponentUpdatedEvent;

	UPROPERTY(BlueprintAssignable, Category = "Outline|Subsystem")
	FOnOutlineVisibleTagsUpdated VisibleTagsUpdatedEvent;

	UFUNCTION()
	void OnComponentUpdatedEvent(UOutlineActorComponent* UpdatedComponent);

	UFUNCTION()
	void OnVisibleTagsUpdatedEvent();
#pragma endregion
	
	void RegisterOutlineComponent(UOutlineActorComponent* OutlineActorComponent);
	void UnregisterOutlineComponent(UOutlineActorComponent* OutlineActorComponent);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
