#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShelfInventoryWidget.generated.h"

class UScrollBox;
class UShelfSlotWidget;
class APCharacter;
class APController;
class UUnknownGameInstance;

UCLASS()
class UNKNOWN_API UShelfInventoryWidget: public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	void UpdateWidget();

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;
	
	UPROPERTY()
	UUnknownGameInstance* GameInstance;

protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UScrollBox* InventoryScrollBox;
	
	//UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	//UShelfSlotWidget* WBP_ShelfSlot;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UShelfSlotWidget> ShelfSlotClass;
	
};
