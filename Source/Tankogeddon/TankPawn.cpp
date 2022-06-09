


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Cannon.h"


ATankPawn::ATankPawn()
{

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	BodyMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->AttachToComponent(TurretMesh,FAttachmentTransformRules::KeepRelativeTransform);

}

void ATankPawn::MoveForward(float AxisValue)
{
	_targetForwardAxisValue = AxisValue;
}

void ATankPawn::RotateRight(float Value)
{
	targetRotateAxisValue = Value;
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	Controller = Cast<ATankPlayerController>(GetController());

	SetupCannon();
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//movement
	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = currentLocation + forwardVector * MoveSpeed * _targetForwardAxisValue * DeltaTime;
	SetActorLocation(movePosition, true);

	//rotation
	float YawRotation = targetRotateAxisValue * RotationSpeed * DeltaTime;
	FRotator ActorRotation = GetActorRotation();
	YawRotation = ActorRotation.Yaw + YawRotation;
	FRotator NewRotation = FRotator(0.0f, YawRotation, 0.0f);
	SetActorRotation(NewRotation);

	//turretrotation
	if (Controller)
	{
		FVector mousePosition = Controller->GetMousePosition();
		FRotator currRotation = TurretMesh->GetComponentRotation();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePosition);
		targetRotation.Pitch = NewRotation.Pitch;
		targetRotation.Roll = NewRotation.Roll;

		TurretMesh->SetWorldRotation(FMath::Lerp(NewRotation, targetRotation, TurretRotationSpeedKey));
	}
}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	
	}

}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}



void ATankPawn::SetupCannon()
{
	if (Cannon)
	{
		Cannon->Destroy();
	}
	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = this;
	spawnParams.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, spawnParams);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

