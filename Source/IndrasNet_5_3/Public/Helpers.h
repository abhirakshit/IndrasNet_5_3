// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Helpers.generated.h"

/**
 * 
 */
UCLASS()
class INDRASNET_5_3_API UHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintPure, Category = "Math|Sphere")
		static TArray<FVector> GenerateRandomPointsOnSphere(FVector Center, float Radius, int NumPoints);

	UFUNCTION(BlueprintPure, Category = "Math|Lattice")
		static TArray<FVector> GenerateSpawnPoints(const FVector& Center, float MinRadius, float MaxRadius, int32 NumPoints);

	UFUNCTION(BlueprintPure, Category = "Math|Lattice")
		static TArray<FVector> GenerateSpawnPointsInPlayerFOV(const FVector& Center, const FRotator& PlayerRotation, float MinRadius, float MaxRadius, int32 NumPoints, float FOV);

	UFUNCTION(BlueprintPure, Category = "Math|Lattice")
		static TArray<FVector> GenerateSpawnPointsOnSpehereInPlayerFOV(const FVector& Center, const FRotator& PlayerRotation, float Radius, int32 NumPoints, float FOV);

	UFUNCTION(BlueprintCallable, Category = "Math|Cube")
		static FVector GetRandomLocationInCube(FVector Center, float Radius);

	UFUNCTION(BlueprintPure, Category = "Math|Color")
		static FLinearColor HexToLinearColor(const FText& ColorText, const FLinearColor& ErrorColor);
};
