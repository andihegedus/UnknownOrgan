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

	InspectToyButton->OnClicked.AddDynamic(this, &UShelfSlotWidget::InspectToyTrigger);

	InspectToyButton->SetVisibility(ESlateVisibility::Collapsed);
	DescriptionBorder->SetVisibility(ESlateVisibility::Hidden);
	ToyDescription->SetVisibility(ESlateVisibility::Hidden);
}

void UShelfSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UShelfSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	InspectToyButton->SetVisibility(ESlateVisibility::Visible);
	
}

void UShelfSlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	InspectToyButton->SetVisibility(ESlateVisibility::Collapsed);
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

	DescriptionBorder->SetVisibility(ESlateVisibility::Visible);
	ToyDescription->SetVisibility(ESlateVisibility::Visible);
}
