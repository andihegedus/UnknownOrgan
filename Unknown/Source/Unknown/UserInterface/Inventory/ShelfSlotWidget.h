#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShelfSlotWidget.generated.h"

class UBorder;
class UTextBlock;
class UImage;
class FText;
class APCharacter;
class APController;

UCLASS()
class UNKNOWN_API UShelfSlotWidget : public UUserWidget
{

	GENERATED_BODY()

public:
	// FUNCTIONS
	// -----------------------------


	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;

protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* ToyImage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* ToyName;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* ToyDescription;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UBorder* DescriptionBorder;
};
