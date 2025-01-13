#include "OrganCutterWidget.h"

#include "Components/Slider.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"


void UOrganCutterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerController = Cast<APController>(PlayerCharacter->GetWorld()->GetFirstPlayerController());

		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("UOrganCutterWidget: PlayerController valid!"));
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true; 
			PlayerController->bEnableMouseOverEvents = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UOrganCutterWidget: PlayerController not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UOrganCutterWidget: PlayerCharacter not valid."));
	}
}

void UOrganCutterWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UOrganCutterWidget::UpdateWidget()
{
}
