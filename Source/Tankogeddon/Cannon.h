 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStructs.h"
#include "Cannon.generated.h"

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACannon();

	bool CanFire();
	void Fire();
	bool IsReadyToFire();
	void Reload();
	void FireSpecial();

	FTimerHandle ReloadTimer;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UArrowComponent* ProjecTileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
		float FireRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
		float FireRange = 1000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
		float FireDamage = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
		ECannonType CannonType = ECannonType::FireProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
		float shells = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire | Components")
		TSubclassOf<class AProjectile> ProjectileClass;

	bool bReadyToFire = true;

	
};
