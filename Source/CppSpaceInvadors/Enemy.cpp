// Fill out your copyright notice in the Description page of Project Settings.

#include "CppSpaceInvadors.h"
#include "Enemy.h"
#include "bullet.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	scoreCollected = 50.0f;

	// Create hit box 

	hitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("hitBox"));
	hitBox->AttachTo(RootComponent);
	hitBox->SetBoxExtent(FVector(75, 5, 60));
	RootComponent = hitBox;

	// Create the flipbook 
	alien = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("alien"));
	alien->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
void AEnemy::fire()
{
	if (bullet != NULL)
	{


		// Check for a valid World: 
		UWorld* const World = GetWorld();

		if (World)
		{
			// Set the spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// Get a random location to spawn at
			FVector SpawnLocation = GetActorLocation();

			// Get a random rotation for the spawned item
			FRotator SpawnRotation;
			SpawnRotation.Yaw = 0.0f;
			SpawnRotation.Pitch = 0.0f;
			SpawnRotation.Roll = 0.0f;

			// spawn the pickup
			ABullet* const SpawnBullet = World->SpawnActor<ABullet>(bullet, SpawnLocation, SpawnRotation, SpawnParams);


			SpawnBullet->setFirier(this);
		}


	}
}
void AEnemy::beenHit()
{
	
}	
float AEnemy::getScore()
{
	return scoreCollected;
}
