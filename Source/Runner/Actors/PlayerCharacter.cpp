// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include <string>

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"
#include "Components/ArrowComponent.h"
#include "KeyPickup.h"
#include "PointPickup.h"

using UEILPS = UEnhancedInputLocalPlayerSubsystem;
using UEIC = UEnhancedInputComponent;

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	RootComponent = Mesh;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Mesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh)
	{
		Mesh->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
		Mesh->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	}		

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController())) 
	{
		const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (UEILPS* SubSystem = ULocalPlayer::GetSubsystem<UEILPS>(LocalPlayer)) 
		{
			if (InputMappingContext) {
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
			else
			{
				UE_LOGFMT(LogTemp, Log, "DEBUG: Mapping context failed.");
			}
		}
	}
	TArray<AActor*> Keys;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKeyPickup::StaticClass(), Keys);
	for (int i = 0; i < Keys.Num(); i++)
	{
		Cast<AKeyPickup>(Keys[i])->PickedUp.AddUObject(this, &APlayerCharacter::IncrementKeyCount);
	}

	TArray<AActor*> Points;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APointPickup::StaticClass(), Points);
	for (int i = 0; i < Points.Num(); i++)
	{
		Cast<APointPickup>(Points[i])->PickedUp.AddDynamic(this, &APlayerCharacter::AddPoints);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEIC* EnhancedInputComponent = CastChecked<UEIC>(PlayerInputComponent)) 
	{
		if (MoveAction) 
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::RotateRightLeft);
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::InputFinished);
		}
		else 
		{
			UE_LOGFMT(LogTemp, Log, "DEBUG: Player Input Failed to Set up");
		}
	}
}

// Increments key count by 1 when key broadcasts that it has been picked up
void APlayerCharacter::IncrementKeyCount()
{
	KeyCount++;
	UE_LOG(LogTemp, Log, TEXT("KeyCount: %d"), KeyCount);
	KeyCountUpdated.Broadcast(KeyCount);
}

// Adds points from broadcasting point pickup
void APlayerCharacter::AddPoints(int32 PointValue)
{
	Score += PointValue;
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APlayerCharacter::RotateRightLeft(const FInputActionValue& Value)
{
	// Reduce speed 
	Speed = TurnSpeed;

	// Rotate character to face new direction
	const float MovementAxis = Value.Get<float>();
	Mesh->AddLocalRotation(FRotator(0, MovementAxis, 0));

}

void APlayerCharacter::InputFinished()
{
	Speed = NormalSpeed;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const FVector Force = Mesh->GetForwardVector() * Speed;
	Mesh->AddForce(Force, NAME_None, true);
	
}

