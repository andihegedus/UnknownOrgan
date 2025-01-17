#include "RinseObjectsWidget.h"

#include "Components/Button.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"


void URinseObjectsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerController = Cast<APController>(PlayerCharacter->GetWorld()->GetFirstPlayerController());

		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("URinseObjectsWidget: PlayerController valid!"));
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true; 
			PlayerController->bEnableMouseOverEvents = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("URinseObjectsWidget: PlayerController not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("URinseObjectsWidget: PlayerCharacter not valid."));
	}

	CloseButton->OnClicked.AddDynamic(this, &URinseObjectsWidget::CloseWidget);
}

void URinseObjectsWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URinseObjectsWidget::CloseWidget()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
	UE_LOG(LogTemp, Warning, TEXT("URinseObjectsWidget: CloseWidget fired!"));
}

