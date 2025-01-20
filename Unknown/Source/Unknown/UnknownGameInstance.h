#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UnknownGameInstance.generated.h"

class USaveData;
class FName;

UCLASS()
class UUnknownGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------

	UUnknownGameInstance();
	
	virtual void Init() override;
	
	void CreateSaveFile();

	void SaveGame();

	void LoadGame();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	USaveData* GameSaveInstance;

	UPROPERTY()
	TArray<FName> AcquiredToyIDs;

	//UPROPERTY()
	//UDataTable* ToyDataTable;

	UPROPERTY()
	int32 MonsterPositionID;

	bool bOrganExtruded;

	bool bOrganDissected;
};
