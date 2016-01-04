// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemyHolder.generated.h"


UCLASS()
class CPPSPACEINVADORS_API AEnemyHolder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyHolder();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds ) override;

	//UFUNCTION(BlueprintCallable, Category = "Enemy")
	//void setMovementActive(bool bShouldMove);

protected:

	/* The Object that going to used to spawn */
	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<class AEnemy> enemyObj;

	/* Number of Rows of enemys*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 numOfRows;

	/* Number of Collums of enemys*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int32 numOfCols;

	/* The size of gap between enemy spawns */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float gapBetweenEnemies;

	/* How far each enmie will move after each update */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float movePerMovment;

	FTimerHandle SpawnTimer;

	/*minimum fire delay*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;

	/*maxmum fire delay*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;

	/* The location where first Enemy will start spawning from with other being spawned relative to this */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	FVector toLeftLocation; 

	/* time before movement*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float moveDelay;

	/* The distance from the spawn point to the furthest point of movement*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float distanceFromSide;


	/* Handle the spawning the enemy*/
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void makeEnemyFire();

private: 

	UPROPERTY()
	class AEnemy* furthestLeft;

	UPROPERTY()
	class AEnemy* furthestRight;


	/* Handle the spawning the enemy*/
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void spawnEnemies();

	/* Handle the spawning the enemy*/
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void moveEnemies();

	UPROPERTY()
	float timerSinceMove;

	/* A Array with all Enemies spawned*/
	TArray<class AEnemy*> Enemies;

	void moveEnemiesDown();
	bool movingRight = true;

	/* The current fire delay*/
	float SpawnDelay;
};
