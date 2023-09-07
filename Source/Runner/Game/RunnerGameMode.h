// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 levelTimer = 5;
	
};
