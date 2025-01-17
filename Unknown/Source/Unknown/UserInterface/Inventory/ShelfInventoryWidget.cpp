#include "ShelfInventoryWidget.h"

#include "ShelfSlotWidget.h"
#include "Components/ScrollBox.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"

void UShelfInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());

	if (PlayerCharacter)
	{
		PlayerController = Cast<APController>(PlayerCharacter->GetWorld()->GetFirstPlayerController());

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
}

void UShelfInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UShelfInventoryWidget::UpdateWidget()
{
	if (GameInstance)
	{
		for (int i = 0; i < GameInstance->AcquiredToyIDs.Num() - 1; i++)
		{
			UShelfSlotWidget* CollectableSlot = CreateWidget<UShelfSlotWidget>(this, ShelfSlotClass);

			InventoryScrollBox->AddChild(CollectableSlot);
		}
	}
}
