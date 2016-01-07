// Fill out your copyright notice in the Description page of Project Settings.

#include "CppSpaceInvadors.h"
#include "Bullet.h"
#include "MyPlayer.h"


// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
//
//

	
		hitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("hitBox"));
	hitBox->SetBoxExtent(FVector(75, 5, 60));
	RootComponent = hitBox;
	// Create the flipbook 
	flipBook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("flipBook"));

	flipBook->AttachTo(RootComponent);


	// Setting default speed
	speed = 2.5f;

	lives = 3;
	
	isBulletActive = false;


	startLocation = FVector(1110, 0, -1500.0);
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	//FRotator ActorRotation = GetActorRotation();


	SetActorLocation(startLocation);

}

// Called every frame
void AMyPlayer::Tick( float DeltaTime )
{

	
	Super::Tick( DeltaTime );
	SetActorRotation(FQuat(FRotator(0, 0, 0)));

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAction("Fire", IE_Released, this, &AMyPlayer::Fire);


	InputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);
}

void AMyPlayer::MoveRight(float Value)
{

	if ((Controller != NULL) && (Value != 0.0f) && this->GetActorLocation().X < 1950 && this->GetActorLocation().X > -150)
	{
		FTransform newLocation;
		
		newLocation.SetLocation(FVector(this->GetActorLocation().X + Value * speed, this->GetActorLocation().Y, this->GetActorLocation().Z));
		newLocation.SetRotation(FQuat(FRotator(0, 0, 0)));
		SetActorTransform(newLocation);
	}
	else if (this->GetActorLocation().X >= 1950)
	{
		SetActorLocation(FVector(1949, this->GetActorLocation().Y, this->GetActorLocation().Z));
	}
	else if (this->GetActorLocation().X <= -150)
	{
		SetActorLocation(FVector(-149, this->GetActorLocation().Y, this->GetActorLocation().Z));

	}


}

void AMyPlayer::Fire()
{
	if (bullet != NULL)
	{
		// Make sure bullet is not active
		if (!isBulletActive)
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
				isBulletActive = true;

				SpawnBullet->setFirier(this);
			}
		}
	}
}

void  AMyPlayer::setLives(int32 s)
{
	lives = s;
}
int32 AMyPlayer::getLives()
{
	return lives;
}

void AMyPlayer::playerHit()
{
	lives -= 1;
	isDead = true;
	ABullet* const testBullet = Cast<ABullet>(bullet);
	if (testBullet && !testBullet->IsPendingKill()) {
		testBullet->Destroy();
	}
}
void  AMyPlayer::updateScore(int32 s)
{
	score += s;
}	

int32 AMyPlayer::getCurrentScore()
{
	return score;
}

void   AMyPlayer::setIsBulletActive(bool newState)
{
	isBulletActive = newState;
}

bool AMyPlayer::isPlayerDead()
{
	return isDead;
	
}

void  AMyPlayer::setIsPlayerDead(bool newState)
{
	isDead = newState;
}