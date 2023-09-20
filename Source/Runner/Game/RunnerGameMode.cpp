// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Logging/StructuredLog.h"
#include "Runner/Actors/Endpoint.h"
#include "Runner/Actors/PlayerCharacter.h"


void ARunnerGameMode::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARunnerGameMode::TimerFunction, 1.0f, true);
	PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	TArray<AActor*> Endpoint;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEndpoint::StaticClass(), Endpoint);
	Cast<AEndpoint>(Endpoint[0])->OnComplete.AddUObject(this, &ARunnerGameMode::LevelComplete);
}

void ARunnerGameMode::TimerFunction()
{
	if (LevelTimer > 0)
	{
		LevelTimer--;
		UE_LOG(LogTemp, Log, TEXT("%d"), LevelTimer);
	}
	else
	{
		// Add game over later
		UE_LOG(LogTemp, Log, TEXT("Timer finished"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void ARunnerGameMode::LevelComplete()
{
	UE_LOG(LogTemp, Log, TEXT("Level Complete"));
	if(DefaultLevelCompleteWidget)
	{
		LevelCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultLevelCompleteWidget);
		if(LevelCompleteWidget)
		{
			const FInputModeGameAndUI InputMode;
			Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetInputMode(InputMode);
			LevelCompleteWidget->AddToViewport();
		}
	}

}

void ARunnerGameMode::PauseGame(bool PauseGame)
{
	if(PauseGame)
	{
		const FInputModeGameAndUI InputMode;
		Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetInputMode(InputMode);
	}
	else
	{
		const FInputModeGameOnly InputMode;
		Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->SetInputMode(InputMode);
	}
	
	UGameplayStatics::SetGamePaused(GetWorld(), PauseGame);
}
