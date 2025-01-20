#include "UnknownGameInstance.h"

#include "Data/SaveData.h"
#include "Kismet/GameplayStatics.h"

UUnknownGameInstance::UUnknownGameInstance()
{
}

void UUnknownGameInstance::Init()
{
	Super::Init();

	LoadGame();
}

void UUnknownGameInstance::CreateSaveFile()
{
	GameSaveInstance = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));

	UGameplayStatics::SaveGameToSlot(GameSaveInstance, "Save1", 0);

	GameSaveInstance->SavedIDs.Empty();
	UGameplayStatics::DeleteGameInSlot("Save1", 0);
}

void UUnknownGameInstance::SaveGame()
{
	GameSaveInstance = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot("Save1", 0));

	if (GameSaveInstance != nullptr)
	{
		GameSaveInstance->SavedIDs = AcquiredToyIDs;
		UGameplayStatics::SaveGameToSlot(GameSaveInstance, "Save1",0);
	}
	else if (!UGameplayStatics::DoesSaveGameExist("Save1", 0))
	{
		CreateSaveFile();
	}
}

void UUnknownGameInstance::LoadGame()
{
	GameSaveInstance = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot("Save1", 0));

	if (GameSaveInstance != nullptr)
	{
		AcquiredToyIDs = GameSaveInstance->SavedIDs;
	}
	else if (!UGameplayStatics::DoesSaveGameExist("Save1", 0))
	{
		CreateSaveFile();
	}
}
