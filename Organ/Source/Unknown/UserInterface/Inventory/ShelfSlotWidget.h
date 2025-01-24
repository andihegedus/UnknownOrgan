#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShelfSlotWidget.generated.h"

class UButton;
class UBorder;
class UTextBlock;
class UImage;
class FText;
class APCharacter;
class APController;

UCLASS()
class ORGAN_API UShelfSlotWidget : public UUserWidget
{

	GENERATED_BODY()

public:
	// FUNCTIONS
	// -----------------------------

	UFUNCTION()
	void InspectToyTrigger();

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* ToyImage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* ToyName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* ToyID;

	UPROPERTY()
	FText DesiredID;

protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* InspectToyButton;
};
