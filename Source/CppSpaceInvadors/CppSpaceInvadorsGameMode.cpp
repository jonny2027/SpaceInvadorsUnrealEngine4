// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "CppSpaceInvadors.h"
#include "CppSpaceInvadorsGameMode.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyHolder.h"
#include "MyPlayerController.h"

ACppSpaceInvadorsGameMode::ACppSpaceInvadorsGameMode()
{

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/MyPlayer_BP"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// use our own player controller class
	PlayerControllerClass = AMyPlayerController::StaticClass();
	


}


void ACppSpaceInvadorsGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	
	AActor* play =  UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector playerLocation = FVector(1110, 0, -1200);
	FRotator playerRotation = FRotator(0, 0, 0);

	// Check for a valid World: 
	UWorld* const world = GetWorld();
	if (world)
	{
		// Set the spawn params
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;
		FVector locationToSpawn =FVector(0, 0,  0);
		FTransform tranformOfSpawn;
		tranformOfSpawn.SetLocation(locationToSpawn);

		// Spawn enemy holder
		enemyHolder = world->SpawnActor<AEnemyHolder>(eHolder,tranformOfSpawn);
	}

	player = Cast<AMyPlayer>(play);
	
}
void ACppSpaceInvadorsGameMode::Tick(float DeltaSeconds)
{

	if (player->isPlayerDead())
	{
		resetLvl();
		player->setIsPlayerDead(false);
	}
}
void ACppSpaceInvadorsGameMode::resetLvl()
{
	enemyHolder->resetEnemy();
	
}
