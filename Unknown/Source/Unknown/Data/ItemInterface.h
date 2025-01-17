#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

class APCharacter;

UENUM()
enum class ECollectableType : uint8
{
	Toy UMETA(DisplayName = "Toy")
};

USTRUCT()
struct FCollectableData
{
	GENERATED_BODY()

	// FUNCTIONS
	// -----------------------------

	FCollectableData() : CollectableType(ECollectableType::Toy),
	Name(FText::GetEmpty()),
	Description(FText::GetEmpty()),
	Colorway(FText::GetEmpty()),
	Quantity(0)
	{};
	


	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY(EditInstanceOnly)
	ECollectableType CollectableType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Description;

	UPROPERTY(EditInstanceOnly)
	FText Colorway;
	
	UPROPERTY(EditInstanceOnly)
	int8 Quantity;
};


UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class UNKNOWN_API IItemInterface
{
	GENERATED_BODY()

public:
	// FUNCTIONS
	// -----------------------------

	// For timed interactions (hold to test collectable functionality)
	virtual void BeginTest();
	virtual void EndTest();

	// Direct interact implementation
	virtual void TestCollectable(APCharacter* PlayerCharacter);
	
	// PROPERTIES & VARIABLES
	// -----------------------------
	
	FCollectableData CollectableData;
};
