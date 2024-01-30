// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerIntroGameMode.h"
#include "MultiplayerIntroCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerIntroGameMode::AMultiplayerIntroGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


void AMultiplayerIntroGameMode::HostLANGame()
{
	//The "?Listen" Launches this directory file as a Listen Server
	GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?Listen");
}



void AMultiplayerIntroGameMode::JoinLANGame()
{
	APlayerController* Controller = GetGameInstance()->GetFirstLocalPlayerController();

	if (Controller != nullptr)
	{
		Controller->ClientTravel("192.168.1.170", TRAVEL_Absolute);
	}
}