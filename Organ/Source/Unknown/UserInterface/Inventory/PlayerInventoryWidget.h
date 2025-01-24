#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInventoryWidget.generated.h"

class UMonsterStateLoggerWidget;
class UShelfInventoryWidget;
class UHorizontalBox;
class URinseObjectsWidget;
class UOrganCutterWidget;
class UUnknownGameInstance;
class APCharacter;
class APController;
class UButton;
class UTextBlock;
class UBorder;


UCLASS()
class ORGAN_API UPlayerInventoryWidget: public UUserWidget
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

	UPROPERTY()
	UUnknownGameInstance* GameInstance;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	URinseObjectsWidget* RinseTool;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UMonsterStateLoggerWidget* MonsterStateLogger;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UOrganCutterWidget* OrganCutter;


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
	UShelfInventoryWidget* ShelfInventory;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* CutText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UBorder* CutBorder;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* RinseText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UBorder* RinseBorder;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* DefendText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UBorder* DefendBorder;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* TestText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UBorder* TestBorder;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* PlayerInventory;
};
