// Fill out your copyright notice in the Description page of Project Settings.


#include "Endpoint.h"

#include "PlayerCharacter.h"
#include "../Game/RunnerGameMode.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEndpoint::AEndpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called when the game starts or when spawned
void AEndpoint::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ARunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (CollisionBox)
	{
		CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEndpoint::OnBeginOverlap);
	}
	
}

void AEndpoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(APlayerCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Log, TEXT("Endpoint Triggered"));
		GameMode->LevelComplete();
	}
}

// Called every frame
void AEndpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

