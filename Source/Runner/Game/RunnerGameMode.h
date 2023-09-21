// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MySaveGame.h"
#include "GameFramework/GameModeBase.h"
#include "../Actors/PlayerCharacter.h"
#include "GameFramework/SaveGame.h"
#include "RunnerGameMode.generated.h"


/**
 * 
 */
UCLASS()
class RUNNER_API ARunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:

	void BeginPlay();

	void TimerFunction();
	
	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	TSubclassOf<UUserWidget> DefaultLevelCompleteWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
	TSubclassOf<UUserWidget> DefaultGameOverWidget;

	UPROPERTY()
	UUserWidget* LevelCompleteWidget;

	UPROPERTY()
	UUserWidget* GameOverWidget;;

	UPROPERTY()
	APlayerController* PlayerController;

	UPROPERTY()
	APlayerCharacter* Player;

	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 LevelTimer = 300;
	void LevelComplete();
	void PauseGame(bool PauseGame);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Default)
	UMySaveGame* SaveGame;
};
