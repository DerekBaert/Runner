// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameMode.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"


void ARunnerGameMode::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARunnerGameMode::TimerFunction, 1.0f, true);
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
			LevelCompleteWidget->AddToViewport();
		}
	}
}

void ARunnerGameMode::PauseGame(bool PauseGame)
{
	UGameplayStatics::SetGamePaused(GetWorld(), PauseGame);
}
