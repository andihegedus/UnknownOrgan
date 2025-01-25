#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "RinseObjectsWidget.generated.h"


class FOnButtonClickedEvent;
class UButton;
class UTextBlock;
class UProgressBar;
class APCharacter;
class APController;
class UImage;
class UHorizontalBox;
class AUnknownHUD;

UCLASS()
class ORGAN_API URinseObjectsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------

	UFUNCTION()
	void CloseWidget();
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;

	UPROPERTY(EditAnywhere)
	AUnknownHUD* HUD;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* TreasureImage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* TreasureText;

	FOnButtonClickedEvent OnButtonClickedEvent;


protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* RinseBox;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* CloseButton;
};
