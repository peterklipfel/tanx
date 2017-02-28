// Fill out your copyright notice in the Description page of Project Settings.

#include "tanx.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("TankAIController BeginPlay"));
    ATank* posessedTank = GetControlledTank();
    if(!posessedTank) {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller not posessing tank"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller posessing tank %s"), *(posessedTank->GetName()));
    }
    ATank* playerTank = GetPlayerTank();
    if (!playerTank) {
        UE_LOG(LogTemp, Warning, TEXT("Player tank not found"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Player tank found: %s"), *(posessedTank->GetName()));
    }
}

ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
    APawn* tank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!tank) {
        UE_LOG(LogTemp, Warning, TEXT("first player controller not found by AI controller"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("first player controller found by AI controller"));
    }
    return Cast<ATank>(tank);
}
