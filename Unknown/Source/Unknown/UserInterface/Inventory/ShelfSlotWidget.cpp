#include "ShelfSlotWidget.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Unknown/ActivityStations/TestStation/ToyInspector.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"


void UShelfSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerController = Cast<APController>(PlayerCharacter->GetWorld()->GetFirstPlayerController());

		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true; 
			PlayerController->bEnableMouseOverEvents = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UShelfSlotWidget: PlayerController not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UShelfSlotWidget: PlayerCharacter not valid."));
	}

	InspectToyButton->SetVisibility(ESlateVisibility::Visible);
	InspectToyButton->OnClicked.AddDynamic(this, &UShelfSlotWidget::InspectToyTrigger);
}

void UShelfSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UShelfSlotWidget::InspectToyTrigger()
{
	if (PlayerCharacter)
	{
		DesiredID = ToyID->GetText();

		if (PlayerCharacter->ToyInspector)
		{
			PlayerCharacter->ToyInspector->SwapMesh(DesiredID);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UShelfSlotWidget: ToyInspector ref from PlayerCharacter not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UShelfSlotWidget: PlayerCharacter not valid."));
	}
}
