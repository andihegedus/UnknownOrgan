#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TreasureSpawner.generated.h"

class APCharacter;

UCLASS()
class UNKNOWN_API ATreasureSpawner: public APawn
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	ATreasureSpawner();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	protected:
	// FUNCTIONS
	// -----------------------------

	virtual void BeginPlay() override;
};
