#include "UnknownHUD.h"

#include "Unknown/UserInterface/Interaction/InteractionWidget.h"
#include "Unknown/UserInterface/Inventory/PlayerInventoryWidget.h"
#include "Unknown/UserInterface/Inventory/ShelfInventoryWidget.h"
#include "Unknown/UserInterface/SaveLoad/SaveLoadWidget.h"
#include "Unknown/UserInterface/Settings/SettingsWidget.h"

AUnknownHUD::AUnknownHUD()
{
}

void AUnknownHUD::BeginPlay()
{
	Super::BeginPlay();

	if (SaveLoadWidgetClass)
	{
		SaveLoadWidget = CreateWidget<USaveLoadWidget>(GetWorld(), SaveLoadWidgetClass);
		SaveLoadWidget->AddToViewport();
		SaveLoadWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (SettingsWidgetClass)
	{
		SettingsWidget = CreateWidget<USettingsWidget>(GetWorld(), SettingsWidgetClass);
		SettingsWidget->AddToViewport();
		SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UInteractionWidget>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(); 
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (PlayerInventoryWidgetClass)
	{
		PlayerInventoryWidget = CreateWidget<UPlayerInventoryWidget>(GetWorld(), PlayerInventoryWidgetClass);
		PlayerInventoryWidget->AddToViewport();
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
	if (ShelfInventoryWidgetClass)
	{
		ShelfInventoryWidget = CreateWidget<UShelfInventoryWidget>(GetWorld(), ShelfInventoryWidgetClass);
		ShelfInventoryWidget->AddToViewport();
		ShelfInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AUnknownHUD::ShowSaveLoadWidget()
{
	if (SaveLoadWidget)
	{
		SaveLoadWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AUnknownHUD::HideSaveLoadWidget()
{
	if (SaveLoadWidget)
	{
		SaveLoadWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AUnknownHUD::ShowSettingsWidget()
{
	if (SettingsWidget)
	{
		SettingsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AUnknownHUD::HideSettingsWidget()
{
	if (SettingsWidget)
	{
		SettingsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AUnknownHUD::HideInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AUnknownHUD::UpdateInteractionWidget()
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}
		/*if (PlayerCharacter)
		{
			InteractionWidget->UpdateWidget(PlayerCharacter->TagInFocus);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("HUD: no valid player character found in world.")); 
		}*/
	}
}

void AUnknownHUD::ShowPlayerInventoryWidget()
{
	if (PlayerInventoryWidget)
	{
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AUnknownHUD::HidePlayerInventoryWidget()
{
	/*if (PlayerInventoryWidget)
	{
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}*/
}

void AUnknownHUD::HideShelfInventoryWidget()
{
	if (ShelfInventoryWidget)
	{
		ShelfInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AUnknownHUD::UpdateShelfInventoryWidget()
{
}


