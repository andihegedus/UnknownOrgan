#include "ShelfInventoryWidget.h"

#include "ShelfSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/ActivityStations/RinseStation/OrganRinse.h"
#include "Unknown/ActivityStations/TestStation/ToyInspector.h"
#include "Unknown/Data/ItemDataStructs.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"
#include "Unknown/System/UnknownHUD.h"

void UShelfInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerController = Cast<APController>(PlayerCharacter->GetWorld()->GetFirstPlayerController());

		PlayerCharacter->OnInventoryStateUpdated.AddUObject(this, &UShelfInventoryWidget::UpdateWidget);

		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: PlayerController valid!"));
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true; 
			PlayerController->bEnableMouseOverEvents = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: PlayerController not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: PlayerCharacter not valid."));
	}
}

void UShelfInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UShelfInventoryWidget::UpdateWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: Update widget fired!"));
	
	GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());
	
	if (GameInstance)
	{
		if (GameInstance->AcquiredToyIDs.Num() >= 1)
		{
			InventoryScrollBox->ClearChildren();
			
			for (int i = 0; i < GameInstance->AcquiredToyIDs.Num(); i++)
			{
				if (PlayerCharacter->HUD->ShelfSlotWidgetClass)
				{
					//ShelfSlot = CreateWidget<UShelfSlotWidget>(this, PlayerCharacter->HUD->ShelfSlotWidgetClass);
					ShelfSlot = CreateWidget<UShelfSlotWidget>(this, PlayerCharacter->HUD->ShelfSlotWidgetClass);
					ShelfSlot->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: ShelfSlotClass not valid."));
				}
					
				if (ShelfSlot)
				{
					InventoryScrollBox->AddChild(ShelfSlot);

					if (PlayerCharacter)
					{
						if (PlayerCharacter->OrganRinse)
						{
							const FToyData* ToyData = PlayerCharacter->OrganRinse->ToyDataTable->FindRow<FToyData>(GameInstance->AcquiredToyIDs[i], GameInstance->AcquiredToyIDs[i].ToString());

							ShelfSlot->ToyName->SetText(ToyData->ToyTextData.NameText);
							IconBrushTexture = ToyData->ToyAssetData.Icon;
							ShelfSlot->ToyImage->SetBrushFromTexture(IconBrushTexture);
							ShelfSlot->ToyID->SetText(ToyData->ToyTextData.IDText);
						}
						else if (PlayerCharacter->ToyInspector)
						{
							const FToyData* ToyData = PlayerCharacter->ToyInspector->ToyDataTable->FindRow<FToyData>(GameInstance->AcquiredToyIDs[i], GameInstance->AcquiredToyIDs[i].ToString());

							ShelfSlot->ToyName->SetText(ToyData->ToyTextData.NameText);
							IconBrushTexture = ToyData->ToyAssetData.Icon;
							ShelfSlot->ToyImage->SetBrushFromTexture(IconBrushTexture);
							ShelfSlot->ToyID->SetText(ToyData->ToyTextData.IDText);
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: PlayerCharacter/OrganRinse ref not valid."));
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: PlayerCharacter not valid."));
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: ShelfSlot not valid."));
				}
			}

			if (ShelfSlot)
			{
				//InventorySlotBox->AddChildToWrapBox(ShelfSlot);;
				InventoryScrollBox->AddChild(ShelfSlot);
				UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: Non-array single built."));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: ShelfSlot not valid."));
			}
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: ShelfSlotClass not valid."));
		}
				
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UShelfInventoryWidget: No IDs in GameInstance array."));
	}
	
}
