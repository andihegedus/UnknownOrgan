// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnknownGameModeBase.h"

#include "System/UnknownHUD.h"

AUnknownGameModeBase::AUnknownGameModeBase(const FObjectInitializer& ObjectInitializer)
{
	HUDClass = AUnknownHUD::StaticClass();
}

void AUnknownGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
