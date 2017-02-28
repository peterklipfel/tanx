// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANX_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    virtual void Tick(float DeltaTime) override;
    
    ATank* GetControlledTank() const;
    
    virtual void BeginPlay() override;
    
    bool GetSightRayHitLocation(FVector &HitLocation) const;
    bool GetLookVectorHitLocation(FVector lookDirection, FVector &HitLocation) const;
    void AimTowardCrosshairs();
    
    UPROPERTY(EditAnywhere)
    float crosshairXPercentOffset = 0.5;

    UPROPERTY(EditAnywhere)
    float crosshairYPercentOffset = 0.33333;
    
    UPROPERTY(EditAnywhere)
    float lineTraceRange = 10000; // 10 km
};
