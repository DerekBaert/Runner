// Fill out your copyright notice in the Description page of Project Settings.


#include "MySaveGame.h"

void UMySaveGame::AddScore(int32 NewScore)
{
	PlayerScores.Add(NewScore);
	PlayerScores.Sort();
}
