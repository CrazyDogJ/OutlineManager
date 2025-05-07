// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "CameraModifier_Outline.generated.h"

/**
 * 
 */
UCLASS()
class OUTLINEMANAGER_API UCameraModifier_Outline : public UCameraModifier
{
	GENERATED_BODY()

public:
	/** Pre set custom stencil color */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TMap<int, FLinearColor> OutlineColors;

	UPROPERTY(BlueprintReadOnly)
	TMap<int, UMaterialInterface*> OutlineInstanceMaterials;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UMaterialInterface* OutlineMaterial;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName ColorPropertyName = "OutlineColor";

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FName CustomStencilPropertyName = "StencilValue";
	
	virtual void AddedToCamera(APlayerCameraManager* Camera) override;
	virtual void ModifyPostProcess(float DeltaTime, float& PostProcessBlendWeight, FPostProcessSettings& PostProcessSettings) override;
};
