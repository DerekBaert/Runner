// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Logging/StructuredLog.h"
#include "Components/ArrowComponent.h"

using UEILPS = UEnhancedInputLocalPlayerSubsystem;
using UEIC = UEnhancedInputComponent;

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetSimulatePhysics(true);
	RootComponent = Cube;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Cube);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Cube);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Cube)
	{
		Cube->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHit);
		Cube->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
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
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEIC* EnhancedInputComponent = CastChecked<UEIC>(PlayerInputComponent)) 
	{
		if (MoveAction) 
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TurnRightLeft);
		}
		else 
		{
			UE_LOGFMT(LogTemp, Log, "DEBUG: Player Input Failed to Set up");
		}
	}
}

void APlayerCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
}

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void APlayerCharacter::TurnRightLeft(const FInputActionValue& Value)
{
	// Rotate character to face new direction

	// Placeholder to test inputs
	const float MovementAxis = Value.Get<float>();

	const FVector CubeForce{ 0.0f, MovementAxis * 1000, 0.0f };
	Cube->AddForce(CubeForce, NAME_None, true);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	const FVector Force{ Speed, 0.0f, 0.0f };
	Cube->AddForce(Force, NAME_None, true);
}

