// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "CppSpaceInvadors.h"
#include "CppSpaceInvadorsGameMode.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"
//#include "Blueprint/UserWidget.h"
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
	
	
	AActor* player =  UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector playerLocation = FVector(1110, 0, -1200);
	FRotator playerRotation = FRotator(0, 0, 0);

	//player->SetActorLocation(playerLocation);
	//player->SetActorRotation(playerRotation);

	//if (HUDWidgetClass != nullptr)
	//{
	//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	//	if (CurrentWidget != nullptr)
	//	{
	//		CurrentWidget->AddToViewport();
	//	}

	//}
}
