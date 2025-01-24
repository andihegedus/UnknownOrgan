#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SaveLoadWidget.generated.h"

class APCharacter;
class APController;
class UUnknownGameInstance;
class UButton;
class AUnknownHUD;

UCLASS()
class ORGAN_API USaveLoadWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void NewGame();

	UFUNCTION()
	void LoadGame();

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
	UButton* NewGameButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* LoadGameButton;
	
	//UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	//UButton* SettingsButton;
	
	
};
