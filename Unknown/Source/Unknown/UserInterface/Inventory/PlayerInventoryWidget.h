#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInventoryWidget.generated.h"

class URinseObjectsWidget;
class UOrganCutterWidget;
class APCharacter;
class APController;
class UButton;


UCLASS()
class UNKNOWN_API UPlayerInventoryWidget: public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	void UpdateWidget();

	UFUNCTION()
	void OnLeftArrowClicked();

	UFUNCTION()
	void OnRightArrowClicked();

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

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* LeftArrowButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* RightArrowButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UOrganCutterWidget* WBP_OrganCutter;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	URinseObjectsWidget* WBP_RinseTool;
	
};
