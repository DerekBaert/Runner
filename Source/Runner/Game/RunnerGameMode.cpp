// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameMode.h"
#include "Logging/StructuredLog.h"


void ARunnerGameMode::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARunnerGameMode::TimerFunction, 1.0f, true);
}

void ARunnerGameMode::TimerFunction()
{
	if (levelTimer > 0)
	{
		levelTimer--;
		UE_LOG(LogTemp, Log, TEXT("%d"), levelTimer);
	}
	else
	{
		// Add game over later
		UE_LOG(LogTemp, Log, TEXT("Timer finished"));
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}	
	
}
