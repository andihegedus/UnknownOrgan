// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnknownGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UNKNOWN_API AUnknownGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// FUNCTIONS
	// -----------------------------
	
	AUnknownGameModeBase(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	
};
