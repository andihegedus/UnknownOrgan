#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UnknownHUD.generated.h"

class APCharacter;

class USaveLoadWidget;
class USettingsWidget;
class UInteractionWidget;
class UPlayerInventoryWidget;
class UShelfInventoryWidget;

UCLASS()
class UNKNOWN_API AUnknownHUD : public AHUD
{
	GENERATED_BODY()
public:
	// FUNCTIONS
	// -----------------------------

	AUnknownHUD();

	virtual void BeginPlay() override;

	void ShowHideSaveLoadWidget();
	//void HideSaveLoadWidget();

	void ShowSettingsWidget();
	void HideSettingsWidget();

	void HideInteractionWidget();
	void UpdateInteractionWidget();

	void ShowPlayerInventoryWidget();
	void HidePlayerInventoryWidget();

	void ShowShelfInventoryWidget();
	void HideShelfInventoryWidget();
	void UpdateShelfInventoryWidget();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, Category="Widgets")
	TArray<FName> WidgetTags;

	UPROPERTY(VisibleAnywhere, Category="Widgets")
	FName CurrentTag;

	bool bIsMenuVisible;
	bool bIsWidgetVisible;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<USaveLoadWidget> SaveLoadWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<USettingsWidget> SettingsWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UInteractionWidget> InteractionWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UShelfInventoryWidget> ShelfInventoryWidgetClass;

protected:
	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	USaveLoadWidget* SaveLoadWidget;

	UPROPERTY()
	USettingsWidget* SettingsWidget;

	UPROPERTY()
	UInteractionWidget* InteractionWidget;
	
	UPROPERTY()
	UPlayerInventoryWidget* PlayerInventoryWidget;

	UPROPERTY()
	UShelfInventoryWidget* ShelfInventoryWidget;
};
