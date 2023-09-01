// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetSimulatePhysics(true);
	RootComponent = Cube;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	AActor* Player = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());

	// This is throwing errors
	Cast<APlayerCharacter>(Player)->KeyCountUpdated.BindUFunction(this, "OpenDoor");
}

void ADoor::OpenDoor()
{
	Destroy();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

