// Copyright 2025 Vzen Lu. All Rights Reserved.

#include "CameraModifier_Outline.h"

#include "Kismet/KismetMaterialLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"

void UCameraModifier_Outline::AddedToCamera(APlayerCameraManager* Camera)
{
	Super::AddedToCamera(Camera);

	for (auto Itr : OutlineColors)
	{
		auto InstanceMat = UKismetMaterialLibrary::CreateDynamicMaterialInstance(Cast<UObject>(GetWorld()), OutlineMaterial);
		InstanceMat->SetVectorParameterValue(ColorPropertyName, Itr.Value);
		InstanceMat->SetScalarParameterValue(CustomStencilPropertyName, Itr.Key);
		OutlineInstanceMaterials.Add(Itr.Key, Cast<UMaterialInterface>(InstanceMat));
	}
}

void UCameraModifier_Outline::ModifyPostProcess(float DeltaTime, float& PostProcessBlendWeight,
                                                FPostProcessSettings& PostProcessSettings)
{
	Super::ModifyPostProcess(DeltaTime, PostProcessBlendWeight, PostProcessSettings);

	PostProcessBlendWeight = 1.0f;
	TArray<FWeightedBlendable> Final;
	for (auto Itr : OutlineInstanceMaterials)
	{
		Final.Add(FWeightedBlendable(1.0, Cast<UObject>(Itr.Value)));
	}
	PostProcessSettings.WeightedBlendables.Array = Final;
}
