// Fill out your copyright notice in the Description page of Project Settings.


#include "PointPickup.h"
#include "Logging/StructuredLog.h"
#include "PlayerCharacter.h"


// Sets default values
APointPickup::APointPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void APointPickup::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh)
	{
		Mesh->OnComponentBeginOverlap.AddDynamic(this, &APointPickup::OnBeginOverlap);
	}
}

void APointPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOGFMT(LogTemp, Log, "DEBUG: Overlap Triggered");
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		PickedUp.Broadcast(PointValue);
		Destroy();
	}
}

// Called every frame
void APointPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

