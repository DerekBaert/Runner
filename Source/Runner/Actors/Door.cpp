// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "KeyPickup.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetSimulatePhysics(true);
	//RootComponent = Mesh;
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	AActor* Player = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass());

	// This is throwing errors
	Cast<APlayerCharacter>(Player)->KeyCountUpdated.AddDynamic(this, &ADoor::OpenDoor);

	TArray<AActor*> Keys;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKeyPickup::StaticClass(), Keys);
	KeysNeeded = Keys.Num();

}

void ADoor::OpenDoor(int32 KeyCount)
{
	if (KeyCount >= KeysNeeded)
	{
		Destroy();
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

