#pragma once

#include "CoreMinimal.h"
#include "ItemDataStructs.h"
#include "GameFramework/SaveGame.h"
#include "SaveData.generated.h"

struct FToyTextData;
enum class EToyType : uint8;
class UDataTable;

UCLASS()
class UNKNOWN_API USaveData : public USaveGame
{
	GENERATED_BODY()

public:
	
	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(SaveGame)
	FName ID;

	UPROPERTY(SaveGame)
	EToyType ToyType;

	UPROPERTY(SaveGame)
	FToyTextData ToyTextData;

	UPROPERTY(SaveGame)
	FToyAssetData ToyAssetData;
};
