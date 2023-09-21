// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameMode.h"

#include "MySaveGame.h"
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

	Player = Cast<APlayerCharacter>(PlayerController->GetPawn());

	if (SaveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("DefaultSlot", 0)))
	{
		if(SaveGame)
		{
			UE_LOG(LogTemp, Log, TEXT("Scores Loaded"));
		}
	}
	else
	{
		SaveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
		if(SaveGame)
		{
			UE_LOG(LogTemp, Log, TEXT("Save slot created"));
		}
	}

	for(int32 score : SaveGame->PlayerScores)
	{
		UE_LOGFMT(LogTemp, Log, "Score: '{0}'", score);
	}

}

void ARunnerGameMode::TimerFunction()
{
	if (LevelTimer > 0)
	{
		LevelTimer--;
		//UE_LOG(LogTemp, Log, TEXT("%d"), LevelTimer);
	}
	else
	{
		// Add game over later
		//UE_LOG(LogTemp, Log, TEXT("Timer finished"));
		Player->GameOver();
		GameOverWidget->AddToViewport();
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}
}

void ARunnerGameMode::LevelComplete()
{

	UE_LOG(LogTemp, Log, TEXT("Level Complete"));
	if(DefaultLevelCompleteWidget)
	{
		LevelCompleteWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultLevelCompleteWidget);
		GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultGameOverWidget);

		if(LevelCompleteWidget)
		{
			const FInputModeGameAndUI InputMode;
			PlayerController->SetInputMode(InputMode);

			SaveGame->AddScore(Player->Score + LevelTimer);

			if (UGameplayStatics::SaveGameToSlot(SaveGame, "DefaultSlot", 0))
			{
				UE_LOG(LogTemp, Log, TEXT("Score Saved"));
			}

			LevelCompleteWidget->AddToViewport();
			GetWorldTimerManager().ClearTimer(TimerHandle);
		}
	}

}

void ARunnerGameMode::PauseGame(bool PauseGame)
{
	if(PauseGame)
	{
		const FInputModeGameAndUI InputMode;
		PlayerController->SetInputMode(InputMode);
	}
	else
	{
		const FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
	
	UGameplayStatics::SetGamePaused(GetWorld(), PauseGame);
}
