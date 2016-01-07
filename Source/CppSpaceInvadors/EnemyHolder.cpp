// Fill out your copyright notice in the Description page of Project Settings.

#include "CppSpaceInvadors.h"
#include "EnemyHolder.h"
#include "Bullet.h"
#include "Enemy.h"


// Sets default values
AEnemyHolder::AEnemyHolder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setting number of enemies 
	numOfRows = 10;

	numOfCols = 5;

	// Setting default gab between eneimes 
	gapBetweenEnemies = 165.0f;

	movePerMovment = 50.0f;

	// Setting the default location where enemies will start spawning from 
	toLeftLocation = FVector(0, 0, 0);	
	
	// Time gap between movement
	moveDelay = 2.85f;

	distanceFromSide = 50;

	// Spawn the spawn delay range 
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;


	moveDownDistance = 50.0f;

}

// Called when the game starts or when spawned
void AEnemyHolder::BeginPlay()
{
	Super::BeginPlay();

	// Spawn enemies 
	spawnEnemies();

	// Set movement timer
	/* works out a random timering delay */
	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemyHolder::makeEnemyFire, SpawnDelay, false);
}

// Called every frame
void AEnemyHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timerSinceMove += DeltaTime;
	if (timerSinceMove > moveDelay)
	{
		moveEnemies();
		timerSinceMove = 0;
		makeEnemyFire();
	}
	FMath::Rand() % 500 == 0;
	if()
}

void AEnemyHolder::resetEnemy()
{
	spawnEnemies();
	// delete spawn bullets
	for (auto b : bullets)
	{
		if (b && !b->IsActorBeingDestroyed())
		{
			b->Destroy();
		}
	}
	bullets.Empty();
}
void AEnemyHolder::moveEnemyDown()
{
	// Loop for all the enemies 
	for (auto e : Enemies)
	{
		auto location = e->GetActorLocation();
		e->SetActorLocation(FVector(location.X, location.Y, location.Z - moveDownDistance));
		if (movingRight == true)
		{
			movingRight = false;
		}
		else
		{
			movingRight = true;
		}
	}
}

void AEnemyHolder::makeEnemyFire()
{

	int32 enemyToFire = FMath::RandRange(0, Enemies.Num() -1 );
	bullets.Add(Enemies[enemyToFire]->fire());
}

void setMovementActive(bool bShouldMove)
{
	if (bShouldMove)
	{
		
	//	GetWorldTimerManager().SetTimer(movementTimer, this, &AEnemyHolder::moveEnemies, moveDelay, false);
		
	}
	else {
		// clear timer
		//GetWorldTimerManager().ClearTimer(movementTimer);
	}

}


void AEnemyHolder::spawnEnemies()
{

	// Remove any enmies left on the screen

	for (auto e : Enemies)
	{
		e->Destroy();
	}

	// Check for a valid World: 
	UWorld* const world = GetWorld();
	if (world)
	{
		// Set the spawn params
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;

		// Loop for the colums
		for (int col = 0; col < numOfCols; col++)
		{
			// Loop for the Rows 
			for (int row = 0; row < numOfRows; row++)
			{


				// Set Location of spawning 
				// Location based off the top left location then moved based of the distance between the enmies 
				FVector locationToSpawn = toLeftLocation - FVector(-row * gapBetweenEnemies, 0, col * gapBetweenEnemies);
				FTransform tranformOfSpawn;
				tranformOfSpawn.SetLocation(locationToSpawn);
				//  Spawn 
				AEnemy* const spawnedEnemy = world->SpawnActor<AEnemy>(enemyObj, tranformOfSpawn, spawnParams);

				Enemies.Add(spawnedEnemy);
					

			}
		}
	}
	

	furthestLeft = Enemies[0];
	furthestRight = Enemies[numOfCols * numOfRows - 1];

}


void AEnemyHolder::moveEnemies()
{


	
	for (auto g : Enemies)
	{
		FVector location = g->GetActorLocation();



		if (movingRight)
		{
			location += FVector(movePerMovment, 0, 0);
		}
		else
		{
			location -= FVector(movePerMovment, 0, 0);

		}
	
		//if (g->GetActorLocation().X >= furthestRightPoint)
		//{
		//
		//	if (movingRight)
		//	{
		//		movingRight = false;
		//	}
		//	else
		//	{
		//		movingRight = true;

		//	}
		//	moveEnemiesDown();
		//}

		g->SetActorLocation(location);
	}

	if (furthestRight->GetActorLocation().X > 1780 && movingRight == true)
	{
		moveEnemyDown();
		movingRight = false;
	}
	else if (furthestLeft->GetActorLocation().X < -150 && movingRight == false)
	{
		moveEnemyDown();
		movingRight = true;
	}
}

