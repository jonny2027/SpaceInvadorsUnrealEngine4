// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbookComponent.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

/* type of owner */
UENUM(BlueprintType)
enum class EOwnerType
{
	EPlayer,
	EEnemy,
	EUnknown
};

UCLASS()
class CPPSPACEINVADORS_API ABullet : public AActor
{
	GENERATED_BODY()
		/** Hit box */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* hitBox;
public:	
	// Sets default values for this actor's properties
	ABullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FORCEINLINE class UPaperFlipbookComponent* GetFlipBook() const { return flipBook; }

	/* Returns the current owner*/
	UFUNCTION(BlueprintPure, Category = "Bullet")
	EOwnerType GetCurrentOwner() const;

	/*Sets a new Playing sate*/
	void SetCurrentOwner(EOwnerType newState);


	UFUNCTION(BlueprintPure, Category = "Bullet")
	int32 getScore();

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	void  setFirier(AActor* Char);

	UFUNCTION(BlueprintPure, Category = "Bullet")
	bool getIsActive();

	UFUNCTION(BlueprintCallable, Category = "Bullet")
	void  setIsActive(bool newState);

protected:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", Meta = (BluePrintProtected))
	AActor* firingChar;

	/* Flip book */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* flipBook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", Meta = (BluePrintProtected))
	float bulletSpeed;

	/*The ammount of score the bullet has collceted*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", Meta = (BluePrintProtected))
	int32 scoreCollected;

	/*if bullet is active*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet", Meta = (BluePrintProtected))
	bool isActive;
private: 

	void testHitAgainstAliens(TArray<AActor*> c);
	
	void testHitAgainstPlayer(TArray<AActor*> c);


	EOwnerType currentOwner; 
};
