// Fill out your copyright notice in the Description page of Project Settings.

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
	UFUNCTION(BlueprintCallable)
	TArray<UOutlineActorComponent*> GetRegisteredOutlineComponents() const {return RegisteredOutlineActorComponents.Array();}

	UFUNCTION(BlueprintCallable)
	FGameplayTagContainer GetVisibleGameplayTagContainer() const {return VisibleGameplayTagContainer;}

	UFUNCTION(BlueprintCallable)
	void AddVisibleTag(FGameplayTag AddGameplayTag);

	UFUNCTION(BlueprintCallable)
	bool RemoveVisibleTag(FGameplayTag RemoveGameplayTag);

	UFUNCTION(BlueprintCallable)
	void ClearVisibleTag();

	UFUNCTION(BlueprintCallable)
	void SetVisibleTagContainer(FGameplayTagContainer Container);
	
	UPROPERTY(BlueprintAssignable)
	FOnOutlineActorComponentUpdate ComponentUpdatedEvent;

	UPROPERTY(BlueprintAssignable)
	FOnOutlineVisibleTagsUpdated VisibleTagsUpdatedEvent;

	UFUNCTION()
	void OnComponentUpdatedEvent(UOutlineActorComponent* UpdatedComponent);

	UFUNCTION()
	void OnVisibleTagsUpdatedEvent();
	
	void RegisterOutlineComponent(UOutlineActorComponent* OutlineActorComponent);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
