// Copyright 2025 Vzen Lu. All Rights Reserved.

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
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Outline")
	TMap<int, FLinearColor> OutlineColors;

	UPROPERTY(BlueprintReadOnly, Category = "Outline")
	TMap<int, UMaterialInterface*> OutlineInstanceMaterials;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Outline")
	UMaterialInterface* OutlineMaterial;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Outline")
	FName ColorPropertyName = "OutlineColor";

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Outline")
	FName CustomStencilPropertyName = "StencilValue";
	
	virtual void AddedToCamera(APlayerCameraManager* Camera) override;
	virtual void ModifyPostProcess(float DeltaTime, float& PostProcessBlendWeight, FPostProcessSettings& PostProcessSettings) override;
};
