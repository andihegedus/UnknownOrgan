#include "UnknownGameInstance.h"

#include "Data/SaveData.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter/PCharacter.h"

UUnknownGameInstance::UUnknownGameInstance()
{
}

void UUnknownGameInstance::Init()
{
	Super::Init();

	bIsInTutorial = false;

	
}

void UUnknownGameInstance::CreateSaveFile()
{
	UGameplayStatics::DeleteGameInSlot("Save1", 0);
	
	GameSaveInstance = Cast<USaveData>(UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass()));

	GameSaveInstance->SavedIDs.Empty();
	
	UGameplayStatics::SaveGameToSlot(GameSaveInstance, "Save1", 0);

	bIsInTutorial = true;
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

		PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (PlayerCharacter)
		{
			PlayerCharacter->OnInventoryStateUpdated.Broadcast();
		}
	}
	else if (!UGameplayStatics::DoesSaveGameExist("Save1", 0))
	{
		CreateSaveFile();
	}

	bIsInTutorial = false;
}
