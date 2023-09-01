// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyPickup.h"
#include "Logging/StructuredLog.h"
#include "PlayerCharacter.h"

// Sets default values
AKeyPickup::AKeyPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

}

// Called when the game starts or when spawned
void AKeyPickup::BeginPlay()
{
	Super::BeginPlay();
	if(Sphere)
	{
		Sphere->OnComponentBeginOverlap.AddDynamic(this, &AKeyPickup::OnBeginOverlap);
	}
}

void AKeyPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOGFMT(LogTemp, Log, "DEBUG: Overlap Triggered");
	if (OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		PickedUp.Broadcast();
		Destroy();
	}
}

// Called every frame
void AKeyPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

