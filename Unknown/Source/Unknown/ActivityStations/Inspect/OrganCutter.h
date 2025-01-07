#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OrganCutter.generated.h"

class APCharacter;

UCLASS()
class AOrganCutter: public APawn
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	AOrganCutter();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	protected:
	// FUNCTIONS
	// -----------------------------

	virtual void BeginPlay() override;
};
