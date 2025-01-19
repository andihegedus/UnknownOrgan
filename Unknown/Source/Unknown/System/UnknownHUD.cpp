#include "UnknownHUD.h"

#include "Unknown/UserInterface/Interaction/InteractionWidget.h"
#include "Unknown/UserInterface/Interaction/MonsterStateLoggerWidget.h"
#include "Unknown/UserInterface/Interaction/OrganCutterWidget.h"
#include "Unknown/UserInterface/Interaction/RinseObjectsWidget.h"
#include "Unknown/UserInterface/Inventory/PlayerInventoryWidget.h"
#include "Unknown/UserInterface/Inventory/ShelfInventoryWidget.h"
#include "Unknown/UserInterface/Inventory/ShelfSlotWidget.h"
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
	if (ShelfSlotWidgetClass)
	{
		ShelfSlotWidget = CreateWidget<UShelfSlotWidget>(GetWorld(), ShelfSlotWidgetClass);
		ShelfSlotWidget->AddToViewport();
		ShelfSlotWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (OrganCutterWidgetClass)
	{
		OrganCutterWidget = CreateWidget<UOrganCutterWidget>(GetWorld(), OrganCutterWidgetClass);
		OrganCutterWidget->AddToViewport();
		OrganCutterWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (RinseObjectsWidgetClass)
	{
		RinseObjectsWidget = CreateWidget<URinseObjectsWidget>(GetWorld(), RinseObjectsWidgetClass);
		RinseObjectsWidget->AddToViewport();
		RinseObjectsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (MonsterStateLoggerWidgetClass)
	{
		MonsterStateLoggerWidget = CreateWidget<UMonsterStateLoggerWidget>(GetWorld(), MonsterStateLoggerWidgetClass);
		MonsterStateLoggerWidget->AddToViewport();
		MonsterStateLoggerWidget->SetVisibility(ESlateVisibility::Collapsed);
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
		}
		else
		{
			SaveLoadWidget->SetVisibility(ESlateVisibility::Visible);

			HidePlayerInventoryWidget();
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
	}
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

void AUnknownHUD::ShowOrganCutterWidget()
{
	if (OrganCutterWidget)
	{
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

void AUnknownHUD::ShowRinseObjectsWidget()
{
	if (RinseObjectsWidget)
	{
		RinseObjectsWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AUnknownHUD::UpdateRinseObjectsWidget()
{
}

void AUnknownHUD::HideRinseObjectsWidget()
{
	if (RinseObjectsWidget)
	{
		RinseObjectsWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AUnknownHUD::ShowMonsterLogger()
{
	if (MonsterStateLoggerWidget)
	{
		MonsterStateLoggerWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AUnknownHUD::HideMonsterLogger()
{
	if (MonsterStateLoggerWidget)
	{
		MonsterStateLoggerWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}


