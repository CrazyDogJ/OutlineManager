// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "OutlineActorComponent.generated.h"

USTRUCT(BlueprintType)
struct FOutlineCompProperties
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int CustomStencilValue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer IdentityGameplayTag;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class OUTLINEMANAGER_API UOutlineActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOutlineActorComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing=OnRep_Properties)
	FOutlineCompProperties Properties;

	UFUNCTION()
	void OnRep_Properties();

	UFUNCTION(BlueprintCallable)
	void ToggleOutline(bool bEnable);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void AddIdentityTag(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	bool RemoveIdentityTag(FGameplayTag Tag);
	
protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
