// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"

// Sets default values
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	sceneComponent = RootComponent;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(sceneComponent);

	ProjecTileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	ProjecTileSpawnPoint->SetupAttachment(CannonMesh);
}



bool ACannon::CanFire()
{
	return shells > 0;
}

void ACannon::Fire()
{
	if (!IsReadyToFire() || !CanFire())
	{
		return;
	}
	bReadyToFire = false;


	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Green, "Fire - Projectile");
			shells = shells - 1; 
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjecTileSpawnPoint->GetComponentLocation(), ProjecTileSpawnPoint->GetComponentRotation());
			if (projectile)
			{
				projectile->Start();
			}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Red, "Fire - Trace");
		shells = shells - 1;



	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}



void ACannon::Reload()
{
	bReadyToFire = true;

}

void ACannon::FireSpecial()
{
	if (!IsReadyToFire() || !CanFire())
	{
		return;
	}
	bReadyToFire = false;

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Green, "Fire - Projectile");
		shells = shells - 1;
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjecTileSpawnPoint->GetComponentLocation(), ProjecTileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Red, "Fire - Trace");
		shells = shells - 1;



	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, 1 / FireRate, false);
}

