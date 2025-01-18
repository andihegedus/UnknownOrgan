#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShelfInventoryWidget.generated.h"

class UWrapBox;
class UScrollBox;
class UShelfSlotWidget;
class UHorizontalBox;
class APCharacter;
class APController;
class UUnknownGameInstance;
class AUnknownHUD;

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

	UPROPERTY()
	AUnknownHUD* HUD;

protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UScrollBox* InventoryScrollBox;

	UPROPERTY()
	UTexture2D* IconBrushTexture;

	//UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	//UHorizontalBox* InventorySlotBox;
	
	UPROPERTY()
	UShelfSlotWidget* ShelfSlot;

	
	
};
