#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionWidget.generated.h"

class USlider;
class APCharacter;
class AOrganCutter;

UCLASS()
class ORGAN_API UInteractionWidget: public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	void UpdateWidget(const TArray<FName> Tags);
	

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	AOrganCutter* OrganComp;

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	USlider* InteractionProgressBar;
	
protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	
};
