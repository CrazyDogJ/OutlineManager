// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraModifier_Outline.h"

#include "Kismet/KismetMaterialLibrary.h"

void UCameraModifier_Outline::AddedToCamera(APlayerCameraManager* Camera)
{
	Super::AddedToCamera(Camera);

	for (auto Itr : OutlineColors)
	{
		auto InstanceMat = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), OutlineMaterial);
		InstanceMat->SetVectorParameterValue(ColorPropertyName, Itr.Value);
		InstanceMat->SetScalarParameterValue(CustomStencilPropertyName, Itr.Key);
		OutlineInstanceMaterials.Add(Itr.Key, InstanceMat);
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
		Final.Add(FWeightedBlendable(1.0, Itr.Value));
	}
	PostProcessSettings.WeightedBlendables.Array = Final;
}
