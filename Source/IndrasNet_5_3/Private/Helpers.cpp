
#include "Helpers.h"


TArray<FVector> UHelpers::GenerateRandomPointsOnSphere(FVector Center, float Radius, int NumPoints)
{
    TArray<FVector> Points;

    // Some comment to test
    for (int i = 0; i < NumPoints; i++)
    {
        // Generate two random numbers
        float Theta = FMath::RandRange(0.0f, 2 * PI);
        float Phi = FMath::Acos(2 * FMath::RandRange(0.0f, 1.0f) - 1);

        // Convert spherical coordinates to Cartesian coordinates
        float X = Radius * FMath::Sin(Phi) * FMath::Cos(Theta);
        float Y = Radius * FMath::Sin(Phi) * FMath::Sin(Theta);
        float Z = Radius * FMath::Cos(Phi);

        // Add the center offset and store the point in the array
        FVector Point = FVector(X, Y, Z) + Center;
        Points.Add(Point);
    }

    return Points;
}

TArray<FVector> UHelpers::GenerateSpawnPoints(const FVector& Center, float MinRadius, float MaxRadius, int32 NumPoints)
{
    TArray<FVector> SpawnPoints;
    const float GoldenRatio = (1.0f + FMath::Sqrt(5.0f)) / 2.0f; // Golden ratio

    for (int32 i = 0; i < NumPoints; ++i)
    {
        float Phi = FMath::Acos(1.0f - 2.0f * (i + 0.5f) / NumPoints);
        float Theta = 2.0f * PI * GoldenRatio * i;

        // Randomly interpolate between MinRadius and MaxRadius
        float Radius = FMath::FRandRange(MinRadius, MaxRadius);

        float X = Radius * FMath::Sin(Phi) * FMath::Cos(Theta);
        float Y = Radius * FMath::Sin(Phi) * FMath::Sin(Theta);
        float Z = Radius * FMath::Cos(Phi);

        FVector SpawnPoint = Center + FVector(X, Y, Z);
        SpawnPoints.Add(SpawnPoint);

        // Print statement
        //UE_LOG(LogSpawnPoints, Log, TEXT("Generated Spawn Point: %s"), *SpawnPoint.ToString());
    }
    return SpawnPoints;
}

TArray<FVector> UHelpers::GenerateSpawnPointsInPlayerFOV(const FVector& Center, const FRotator& PlayerRotation, float MinRadius, float MaxRadius, int32 NumPoints, float FOV)
{
    TArray<FVector> SpawnPoints;
    const float GoldenRatio = (1.0f + FMath::Sqrt(5.0f)) / 2.0f; // Golden ratio
    const FVector ForwardVector = PlayerRotation.Vector(); // Player's forward direction

    for (int32 i = 0; i < NumPoints; ++i)
    {
        float Phi = FMath::Acos(1.0f - 2.0f * (i + 0.5f) / NumPoints);
        float Theta = 2.0f * PI * GoldenRatio * i;

        // Randomly interpolate between MinRadius and MaxRadius
        float Radius = FMath::FRandRange(MinRadius, MaxRadius);

        float X = Radius * FMath::Sin(Phi) * FMath::Cos(Theta);
        float Y = Radius * FMath::Sin(Phi) * FMath::Sin(Theta);
        float Z = Radius * FMath::Cos(Phi);

        FVector SpawnPoint = Center + FVector(X, Y, Z);

        // Check if the point is within the FOV
        FVector DirectionToSpawnPoint = (SpawnPoint - Center).GetSafeNormal();
        float DotProduct = FVector::DotProduct(ForwardVector, DirectionToSpawnPoint);
        float Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

        if (Angle <= FOV / 2.0f)
        {
            SpawnPoints.Add(SpawnPoint);
            // Print statement
            //UE_LOG(LogSpawnPoints, Log, TEXT("Generated Spawn Point: %s"), *SpawnPoint.ToString());
        }
    }

    // Print the total number of generated points
    //UE_LOG(LogSpawnPoints, Log, TEXT("Total Generated Spawn Points: %d"), SpawnPoints.Num());

    return SpawnPoints;
}

TArray<FVector> UHelpers::GenerateSpawnPointsOnSpehereInPlayerFOV(const FVector& Center, const FRotator& PlayerRotation, float Radius, int32 NumPoints, float FOV)
{
    TArray<FVector> SpawnPoints;
    const float GoldenRatio = (1.0f + FMath::Sqrt(5.0f)) / 2.0f; // Golden ratio
    const FVector ForwardVector = PlayerRotation.Vector(); // Player's forward direction

    int32 i = 0;
    while (i < NumPoints) {
        float Phi = FMath::Acos(1.0f - 2.0f * (i + 0.5f) / NumPoints);
        float Theta = 2.0f * PI * GoldenRatio * i;

        float X = Radius * FMath::Sin(Phi) * FMath::Cos(Theta);
        float Y = Radius * FMath::Sin(Phi) * FMath::Sin(Theta);
        float Z = Radius * FMath::Cos(Phi);

        FVector SpawnPoint = Center + FVector(X, Y, Z);
        // Check if the point is within the FOV
        FVector DirectionToSpawnPoint = (SpawnPoint - Center).GetSafeNormal();
        float DotProduct = FVector::DotProduct(ForwardVector, DirectionToSpawnPoint);
        float Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));

        if (Angle <= FOV / 2.0f)
        {
            SpawnPoints.Add(SpawnPoint);
        }
        i++;
    }

    return SpawnPoints;
}


FLinearColor UHelpers::HexToLinearColor(const FText& ColorText, const FLinearColor& ErrorColor)
{
    FString ColorString = ColorText.ToString();
    FLinearColor Result;

    // Remove the '#' character if present
    if (ColorString.StartsWith("#"))
    {
        ColorString.RemoveAt(0);
    }

    // Convert the string to upper case to handle lower case inputs
    ColorString = ColorString.ToUpper();

    // Check if the string has 6 or 8 characters (for RGB or RGBA)
    if (ColorString.Len() == 6 || ColorString.Len() == 8)
    {
        // Convert the hex string to an integer
        uint32 HexValue = FParse::HexNumber(*ColorString);
        if (ColorString.Len() == 6)
        {
            Result.R = ((HexValue >> 16) & 0xFF) / 255.0f;
            Result.G = ((HexValue >> 8) & 0xFF) / 255.0f;
            Result.B = (HexValue & 0xFF) / 255.0f;
            Result.A = 1.0f;
        }
        else // Length is 8
        {
            Result.R = ((HexValue >> 24) & 0xFF) / 255.0f;
            Result.G = ((HexValue >> 16) & 0xFF) / 255.0f;
            Result.B = ((HexValue >> 8) & 0xFF) / 255.0f;
            Result.A = (HexValue & 0xFF) / 255.0f;
        }
    }
    else
    {
        UE_LOG(LogCore, Warning, TEXT("Invalid color string length: %s"), *ColorString);
        Result = ErrorColor;
    }

    return Result;
}

FVector UHelpers::GetRandomLocationInCube(FVector Center, float Radius)
{
    float X = FMath::RandRange(Center.X - Radius, Center.X + Radius);
    float Y = FMath::RandRange(Center.Y - Radius, Center.Y + Radius);
    float Z = FMath::RandRange(Center.Z - Radius, Center.Z + Radius);

    return FVector(X, Y, Z);
}