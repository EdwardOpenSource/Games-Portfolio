// Fill out your copyright notice in the Description page of Project Settings.


#include "MariogameMode.h"
void AMariogameMode::ResetScore()
{
	PlayerScore = 0;
}

void AMariogameMode::AddScore(int ScoreToAdd)
{
	PlayerScore += ScoreToAdd;
}

int AMariogameMode::GetScore()
{
	return PlayerScore;
}