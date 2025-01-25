#include "TutorialWidget.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"
#include "Unknown/System/UnknownHUD.h"
#include "Unknown/UserInterface/Inventory/PlayerInventoryWidget.h"

void UTutorialWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerController = Cast<APController>(PlayerCharacter->GetWorld()->GetFirstPlayerController());

		GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());

		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("UPlayerInventoryWidget: PlayerController valid!"));
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true; 
			PlayerController->bEnableMouseOverEvents = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UPlayerInventoryWidget: PlayerController not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlayerInventoryWidget: PlayerCharacter not valid."));
	}

	HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	CutCloseButton->OnClicked.AddDynamic(this, &UTutorialWidget::CloseCutTutorialBox);
	RinseCloseButton->OnClicked.AddDynamic(this, &UTutorialWidget::CloseRinseTutorialBox);
	DefendCloseButton->OnClicked.AddDynamic(this, &UTutorialWidget::CloseDefendTutorialBox);
	InspectCloseButton->OnClicked.AddDynamic(this, &UTutorialWidget::CloseInspectTutorialBox);

	CutBox->SetVisibility(ESlateVisibility::Collapsed);
	RinseBox->SetVisibility(ESlateVisibility::Collapsed);
	DefendBox->SetVisibility(ESlateVisibility::Collapsed);
	InspectBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();
}


void UTutorialWidget::CloseCutTutorialBox()
{
	CutBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UTutorialWidget::CloseRinseTutorialBox()
{
	RinseBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UTutorialWidget::CloseDefendTutorialBox()
{
	DefendBox->SetVisibility(ESlateVisibility::Collapsed);

	if (HUD)
	{
		HUD->PlayerInventoryWidget->LeftArrowButton->SetColorAndOpacity(FLinearColor::White);
		HUD->PlayerInventoryWidget->LeftArrowButton->SetIsEnabled(true);
	}
}

void UTutorialWidget::CloseInspectTutorialBox()
{
	InspectBox->SetVisibility(ESlateVisibility::Collapsed);

	if (GameInstance)
	{
		GameInstance->bIsInTutorial = false;
	}

	if (HUD)
	{
		HUD->PlayerInventoryWidget->LeftArrowButton->SetColorAndOpacity(FLinearColor::White);
		HUD->PlayerInventoryWidget->LeftArrowButton->SetIsEnabled(true);
		HUD->PlayerInventoryWidget->RightArrowButton->SetColorAndOpacity(FLinearColor::White);
		HUD->PlayerInventoryWidget->RightArrowButton->SetIsEnabled(true);
	}
}

