#include "UnknownHUD.h"

#include "Unknown/UserInterface/Interaction/InteractionWidget.h"
#include "Unknown/UserInterface/Interaction/OrganCutterWidget.h"
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
		SaveLoadWidget->SetVisibility(ESlateVisibility::Visible);
	}
	if (OrganCutterWidgetClass)
	{
		OrganCutterWidget = CreateWidget<UOrganCutterWidget>(GetWorld(), OrganCutterWidgetClass);
		OrganCutterWidget->AddToViewport();
		OrganCutterWidget->SetVisibility(ESlateVisibility::Visible);

		UE_LOG(LogTemp, Warning, TEXT("UUnknownHUD: ShowOrganCutterWidget valid."));
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
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (ShelfInventoryWidgetClass)
	{
		ShelfInventoryWidget = CreateWidget<UShelfInventoryWidget>(GetWorld(), ShelfInventoryWidgetClass);
		ShelfInventoryWidget->AddToViewport();
		ShelfInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	
}

void AUnknownHUD::ShowHideSaveLoadWidget()
{
	if (SaveLoadWidget)
	{
		if (SaveLoadWidget->IsVisible())
		{
			SaveLoadWidget->SetVisibility(ESlateVisibility::Collapsed);

			ShowPlayerInventoryWidget();
			ShowOrganCutterWidget();
		}
		else
		{
			SaveLoadWidget->SetVisibility(ESlateVisibility::Visible);

			HidePlayerInventoryWidget();
			HideOrganCutterWidget();
		}
		
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
	UE_LOG(LogTemp, Warning, TEXT("UUnknownHUD: UpdateInterationWidget triggered."));
	
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
	if (PlayerInventoryWidget)
	{
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AUnknownHUD::ShowShelfInventoryWidget()
{
	if (ShelfInventoryWidget)
	{
		ShelfInventoryWidget->SetVisibility(ESlateVisibility::Visible);

		SaveLoadWidget->SetVisibility(ESlateVisibility::Collapsed);

		WidgetTags.Empty();
		
		CurrentTag = "ShelfInventory";
		WidgetTags.Add(CurrentTag);
	}
}

void AUnknownHUD::HideShelfInventoryWidget()
{
	if (ShelfInventoryWidget)
	{
		ShelfInventoryWidget->SetVisibility(ESlateVisibility::Collapsed);

		WidgetTags.Empty();
	}
}

void AUnknownHUD::UpdateShelfInventoryWidget()
{
}

void AUnknownHUD::ShowOrganCutterWidget()
{
	if (OrganCutterWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("UUnknownHUD: ShowOrganCutterWidget valid."));
		OrganCutterWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AUnknownHUD::UpdateOrganCutterWidget()
{
	
}

void AUnknownHUD::HideOrganCutterWidget()
{
	if (OrganCutterWidget)
	{
		OrganCutterWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}


