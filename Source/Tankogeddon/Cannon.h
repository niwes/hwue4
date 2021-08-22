// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "Cannon.generated.h"

class UStaticMeshComponent;
class UArrowComponent;

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* Mesh;
    
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UArrowComponent* ProjectileSpawnPoint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    float FireRate = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    float FireRange = 1000;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    int32 MaxAmmo = 10;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    float FireDamage = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    bool bHasSpecialFire = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
    ECannonType Type = ECannonType::FireProjectile;

    FTimerHandle ReloadTimerHandle;

    bool bReadyToFire = false;

public:
    ACannon();

    void Fire();
    void FireSpecial();

    bool IsReadyToFire() const;
    bool HasSpecialFire() const;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void Reload();

    int32 NumAmmo = 0;
};
