#include "SaveLoadWidget.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"
#include "Unknown/System/UnknownHUD.h"
#include "Unknown/UserInterface/Interaction/TutorialWidget.h"
#include "Unknown/UserInterface/Inventory/PlayerInventoryWidget.h"


void ORGAN_API USaveLoadWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerController = Cast<APController>(PlayerCharacter->GetWorld()->GetFirstPlayerController());

		GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());

		HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("USaveLoadWidget: PlayerController valid!"));
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true; 
			PlayerController->bEnableMouseOverEvents = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("USaveLoadWidget: PlayerController not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USaveLoadWidget: PlayerCharacter not valid."));
	}

	NewGameButton->OnClicked.AddDynamic(this, &USaveLoadWidget::NewGame);
	LoadGameButton->OnClicked.AddDynamic(this, &USaveLoadWidget::LoadGame);
	CloseGameButton->OnClicked.AddDynamic(this, &USaveLoadWidget::CloseGame);
}

void USaveLoadWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USaveLoadWidget::NewGame()
{
	if (GameInstance)
	{
		GameInstance->CreateSaveFile();

		if (GameInstance->bIsInTutorial)
		{
			if (HUD)
			{
				HUD->ShowHideSaveLoadWidget();
				HUD->PlayerInventoryWidget->TutorialWidget->CutBox->SetVisibility(ESlateVisibility::Visible);
				HUD->PlayerInventoryWidget->RightArrowButton->SetColorAndOpacity(FLinearColor::Gray);
				HUD->PlayerInventoryWidget->RightArrowButton->SetIsEnabled(false);
				HUD->PlayerInventoryWidget->LeftArrowButton->SetColorAndOpacity(FLinearColor::Gray);
				HUD->PlayerInventoryWidget->LeftArrowButton->SetIsEnabled(false);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USaveLoadWidget: GameInstance not valid."));
	}
}

void USaveLoadWidget::LoadGame()
{
	if (GameInstance)
	{
		GameInstance->LoadGame();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USaveLoadWidget: GameInstance not valid."));
	}

	if (HUD)
	{
		HUD->ShowHideSaveLoadWidget();
	}
}

void USaveLoadWidget::CloseGame()
{
	if (PlayerController)
	{
		PlayerController->ConsoleCommand("quit");
	}
}
