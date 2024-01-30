// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerIntroGameMode.generated.h"

UCLASS(minimalapi)
class AMultiplayerIntroGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMultiplayerIntroGameMode();

	UFUNCTION(BlueprintCallable)
	void HostLANGame();

	UFUNCTION(BlueprintCallable)
	void JoinLANGame();
};



