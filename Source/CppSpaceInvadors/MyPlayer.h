// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PaperFlipbookComponent.h"
#include "Bullet.h"
#include "MyPlayer.generated.h"


UCLASS()
class CPPSPACEINVADORS_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

	/** Hit box */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* hitBox;

public:


	/** Returns Collection Sphere subobject **/
	FORCEINLINE class UBoxComponent* getHitBox() const { return hitBox; }

	// Sets default values for this character's properties
	AMyPlayer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	/* Return the mesh for the pickup*/
	FORCEINLINE  class UPaperFlipbookComponent* GetFlipBook() const { return flipBook; }

	/* Accessor function for current score*/
	UFUNCTION(BlueprintPure, Category = "player")
		int32 getCurrentScore();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void  updateScore(int32 s);

	/* Accessor function for current score*/
	UFUNCTION(BlueprintPure, Category = "player")
	int32 getLives();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void  setLives(int32 s);

	UFUNCTION(BlueprintCallable, Category = "Player")
	void  setIsBulletActive(bool newState);
	
	UFUNCTION(BlueprintCallable, Category = "Player")
	void  playerHit();

protected:



	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<class ABullet> bullet;

	void MoveRight(float Value);

	void Fire();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (BluePrintProtected))
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (BluePrintProtected))
	FVector startLocation;

private:

	/* Current score of our characer*/
	UPROPERTY(VisibleAnywhere, Category = "Score")
	int32 score;

	/* Current score of our characer*/
	UPROPERTY(VisibleAnywhere, Category = "Score")
	int32 lives;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* flipBook;


	bool isBulletActive;

};
