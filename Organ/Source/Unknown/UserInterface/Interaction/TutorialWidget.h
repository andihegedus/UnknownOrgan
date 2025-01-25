#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

class UButton;
class UHorizontalBox;
class APCharacter;
class APController;
class UUnknownGameInstance;
class AUnknownHUD;

UCLASS()
class UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void CloseCutTutorialBox();

	UFUNCTION()
	void CloseRinseTutorialBox();

	UFUNCTION()
	void CloseDefendTutorialBox();

	UFUNCTION()
	void CloseInspectTutorialBox();

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;

	UPROPERTY()
	UUnknownGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
	AUnknownHUD* HUD;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* CutBox;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* RinseBox;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* DefendBox;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* InspectBox;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* CutCloseButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* RinseCloseButton;
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* DefendCloseButton;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UButton* InspectCloseButton;
	
};
