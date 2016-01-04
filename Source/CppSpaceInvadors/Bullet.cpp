// Fill out your copyright notice in the Description page of Project Settings.

#include "CppSpaceInvadors.h"
#include "Enemy.h"
#include "MyPlayer.h"
#include "Bullet.h"


// Sets default values
ABullet::ABullet()
{

	hitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("hitBox"));
	hitBox->AttachTo(RootComponent);
	hitBox->SetBoxExtent(FVector(20, 5, 30));
	RootComponent = hitBox;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	flipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("flipBook"));
	flipBook->AttachTo(RootComponent);

	bulletSpeed = 100.0f;

	scoreCollected = 0;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick( float DeltaTime )
{




	// Cast the actor to Player
	AMyPlayer* const player = Cast<AMyPlayer>(firingChar);
		// Get all overlapping Actors and store them in an array
		TArray<AActor*> CollectedActors;

	if(player)
		{

		hitBox->GetOverlappingActors(CollectedActors);
		testHitAgainstAliens(CollectedActors);
		SetActorLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z + bulletSpeed*DeltaTime));
	}
	else
	{

		hitBox->GetOverlappingActors(CollectedActors,AMyPlayer::StaticClass());
		testHitAgainstPlayer(CollectedActors);
		SetActorLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z - bulletSpeed*DeltaTime));

	}

	Super::Tick( DeltaTime );
	

	
}
void  ABullet::testHitAgainstAliens(TArray<AActor*> c )
{

	TArray<AActor*> CollectedActors = c;

	// Cast the actor to Player
	AMyPlayer* const player = Cast<AMyPlayer>(firingChar);

	// For each Actor we collected
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		// Cast the actor to AEnemy
		AEnemy* const TestEnemy = Cast<AEnemy>(CollectedActors[iCollected]);
		// If the cast is successful and the pickup is valid and active 
		if (TestEnemy && !TestEnemy->IsPendingKill())
		{
			// Get the score of the enemy
			scoreCollected = TestEnemy->getScore();


			// Deactivate the pickup 
			TestEnemy->Destroy();

			if (player)
			{
				player->updateScore(scoreCollected);
				player->setIsBulletActive(false);

			}

			Destroy();
			break;
		}
	}
	if (GetActorLocation().Z > 150)
	{
		Destroy();
		if (player)
		{
			player->setIsBulletActive(false);


		}
	}
}

void  ABullet::testHitAgainstPlayer(TArray<AActor*> c)
{
	if (GetActorLocation().Z < -3000)
	{
		Destroy();
	}
	AActor* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMyPlayer* const testPlayer = Cast<AMyPlayer>(player);

	FVector thisLocation = GetActorLocation();
	FVector PLocation = testPlayer->GetActorLocation();
	FVector PBox = testPlayer->getHitBox()->GetScaledBoxExtent();

	
	
	if (thisLocation.Z + hitBox->GetScaledBoxExtent().Z / 2 >= PLocation.Z - PBox.Z / 2) {
		if (thisLocation.Z - hitBox->GetScaledBoxExtent().Z / 2 <= PLocation.Z + PBox.Z / 2) {
			if (thisLocation.X + hitBox->GetScaledBoxExtent().X / 2 >= PLocation.X - PBox.X / 2)  {
				if (thisLocation.X - hitBox->GetScaledBoxExtent().X / 2 <= PLocation.X + PBox.X / 2) {

						// Deactivate the pickup 
						testPlayer->playerHit();

						Destroy();
					
				}
			}
		}
	}
	//TArray<AActor*> CollectedActors = c;
	//for (int i = 0; i < CollectedActors.Num(); i++)
	//{
	//	// Cast the actor to AEnemy
	//	
	//		// If the cast is successful and the pickup is valid and active 
	//		if (testPlayer && !testPlayer->IsPendingKill())
	//		{

	//
	//		}
	//}
}
	

EOwnerType  ABullet::GetCurrentOwner() const
{
	return currentOwner;
}

void  ABullet::SetCurrentOwner(EOwnerType newState)
{

}

int32 ABullet::getScore()
{
	return scoreCollected;
}

void  ABullet::setFirier(AActor* Char)
{
	firingChar = Char;
}

bool  ABullet::getIsActive()
{
	return isActive;
}

void   ABullet::setIsActive(bool newState)
{
	isActive = newState;
}