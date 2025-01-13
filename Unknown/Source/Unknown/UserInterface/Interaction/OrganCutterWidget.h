#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OrganCutterWidget.generated.h"


class APCharacter;
class APController;
class USlider;
class UTextBlock;
class UImage;
class UHorizontalBox;

UCLASS()
class UNKNOWN_API UOrganCutterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	void UpdateWidget();

	UFUNCTION()
	void CloseAndDestroy(float Value);
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* OrganCutterSlider;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* OrganSlider2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* OrganSlider3;

	protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* MeatBox;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* OrganImage;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* OrganImage2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* OrganImage3;
};
