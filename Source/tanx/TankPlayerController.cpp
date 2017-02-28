// Fill out your copyright notice in the Description page of Project Settings.

#include "tanx.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("TankPlayerController BeginPlay"));
    ATank* posessedTank = GetControlledTank();
    if(!posessedTank) {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller not posessing tank"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller posessing tank %s"), *(posessedTank->GetName()));
    }
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardCrosshairs();
}

ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const {
    // Get crosshair screen location
    int32 viewportSizeX, viewportSizeY;
    GetViewportSize(viewportSizeX, viewportSizeY);
    auto crossHairScreenLocation = FVector2D(viewportSizeX * crosshairXPercentOffset, viewportSizeY * crosshairYPercentOffset);
    //UE_LOG(LogTemp, Warning, TEXT("Crosshairs @: %s"), *(crossHairScreenLocation.ToString()));
    
    FVector cameraWorldLoc, worldDirection;
    if(DeprojectScreenPositionToWorld( crossHairScreenLocation.X, crossHairScreenLocation.Y, cameraWorldLoc, worldDirection )){
        GetLookVectorHitLocation(worldDirection, HitLocation);
        return true;
    }
    
    return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector &HitLocation) const {
    FHitResult hitResult;
    auto startLocation = PlayerCameraManager->GetCameraLocation();
    auto endLocation = startLocation+(lookDirection*lineTraceRange);
    if(GetWorld()->LineTraceSingleByChannel(
            hitResult,
            startLocation,
            endLocation,
            ECollisionChannel::ECC_Visibility
       )){
        HitLocation = hitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false;
}

void ATankPlayerController::AimTowardCrosshairs()
{
    if(!GetControlledTank()) { return; }
    
    FVector HitLocation;
    if(GetSightRayHitLocation(HitLocation)){
        //UE_LOG(LogTemp, Warning, TEXT("Aiming toward: %s"), *(HitLocation.ToString()));
    }
}
