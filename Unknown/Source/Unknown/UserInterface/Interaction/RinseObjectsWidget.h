#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RinseObjectsWidget.generated.h"


class UProgressBar;
class APCharacter;
class APController;
class UImage;
class UHorizontalBox;

UCLASS()
class UNKNOWN_API URinseObjectsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	void UpdateWidget();

	UFUNCTION()
	void CloseAndDestroy(float Value);

	UFUNCTION()
	void RinseOrgan(float Value);
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* RinseProgressBar1;

	/*UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* RinseProgressBar2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* RinseProgressBar3;*/

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
	UImage* OrganImage1;

	/*UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* OrganImage2;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UImage* OrganImage3;*/
	
};
