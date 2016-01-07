// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/GameMode.h"
#include "CppSpaceInvadorsGameMode.generated.h"

// The GameMode defines the game being played. It governs the game rules, scoring, what actors
// are allowed to exist in this game type, and who may enter the game.
//
// This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of CppSpaceInvadorsCharacter

UCLASS(minimalapi)
class ACppSpaceInvadorsGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ACppSpaceInvadorsGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected: 

	UPROPERTY(EditAnywhere, Category = "Enemy")

	TSubclassOf<class AEnemyHolder> eHolder;


	/* Reset the level and set everything back to pos */
	UFUNCTION(BlueprintCallable, Category = "GamePlay")
	void resetLvl();

private:

	// the player lives for the moment 
	int32 pLives;

	class AMyPlayer* player;

	class AEnemyHolder* enemyHolder;

};
