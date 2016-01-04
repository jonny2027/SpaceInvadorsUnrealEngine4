// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "Enemy.generated.h"

UCLASS()
class CPPSPACEINVADORS_API AEnemy : public AActor
{
	GENERATED_BODY()

	/** Hit box */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* hitBox;
public:	
	// Sets default values for this actor's properties
	AEnemy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


	/* Return the mesh for the pickup*/
	FORCEINLINE  class UPaperFlipbookComponent* GetFlipBook() const { return alien; }

	/** Returns Collection Sphere subobject **/
	FORCEINLINE class UBoxComponent* getHitBox() const { return hitBox; }

	/* When the enemy has been hit  */

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void beenHit();


	UFUNCTION(BlueprintPure, Category = "Enemy")
	float getScore();


	UFUNCTION(BlueprintCallable, Category = "Enemy")
	void fire();

protected:

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<class ABullet> bullet;

	/*Score to give to player if killed*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy", Meta = (BluePrintProtected))
	float scoreCollected;

private:

	/* Alien's sprite sheet */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* alien;
};
