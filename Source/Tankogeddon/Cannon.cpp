// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Engine/Engine.h>
#include <TimerManager.h>
#include <Engine/World.h>

#include "Tankogeddon.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = RootComp;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
    Mesh->SetupAttachment(RootComponent);

    ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
    ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void ACannon::Fire()
{
    if (!bReadyToFire || NumAmmo <= 0)
    {
        return;
    }

    bReadyToFire = false;
    --NumAmmo;
    
    if (Type == ECannonType::FireProjectile)
    {
        GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, TEXT("Fire - projectile"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, TEXT("Fire - trace"));
    }

    GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1.f / FireRate, false);
    UE_LOG(LogTankogeddon, Log, TEXT("Fire! Ammo left: %d"), NumAmmo);
}

void ACannon::FireSpecial()
{
    if (!bHasSpecialFire || !bReadyToFire || NumAmmo <= 0)
    {
        return;
    }

    bReadyToFire = false;
    --NumAmmo;

    if (Type == ECannonType::FireProjectile)
    {
        GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, TEXT("Fire special - projectile"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, TEXT("Fire special - trace"));
    }

    GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1.f / FireRate, false);
    UE_LOG(LogTankogeddon, Log, TEXT("FireSpecial! Ammo left: %d"), NumAmmo);
}

bool ACannon::IsReadyToFire() const
{
    return bReadyToFire;
}

bool ACannon::HasSpecialFire() const
{
    return bHasSpecialFire;
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
    bReadyToFire = true;
    NumAmmo = MaxAmmo;
}

void ACannon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
}

void ACannon::Reload()
{
    bReadyToFire = true;
}
