#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveLoadWidget.generated.h"

class APCharacter;
class APController;
class UButton;

UCLASS()
class USaveLoadWidget : public UUserWidget
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
	


protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	// PROPERTIES & VARIABLES
	// -----------------------------
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* NewGameButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* LoadGameButton;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* SettingsButton;
	
	
};
