// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay() 
{
    Super::BeginPlay();
    
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction() 
{
    Super::HandleDestruction();
    // Destroy turret
}

// Called every frame
void APawnTurret::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if(!PlayerPawn || ReturnDistanceToPlayer() > TurretRange)
        return;
    
    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition() 
{
    // Check if player is null (doesn't exist) or is dead
    if(!PlayerPawn) return;
    // Check if player is in range
    if(ReturnDistanceToPlayer() <= TurretRange)
        Fire();
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if(!PlayerPawn) return 0.f;

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
