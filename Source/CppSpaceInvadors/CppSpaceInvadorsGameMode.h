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



protected: 

	///* The widget Class to use for our hub screen*/
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Score", Meta = (BluePrintProtected = "true"))
	//TSubclassOf<class UUserWidget> HUDWidgetClass;

	///* The instance of the HUD */
	//UPROPERTY()
	//class UUserWidget* CurrentWidget;
private:
	/* Controls all the enemies */

};
