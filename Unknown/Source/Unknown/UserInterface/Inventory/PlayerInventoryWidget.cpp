#include "PlayerInventoryWidget.h"

#include "Camera/CameraComponent.h"
#include "Components/Button.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"
#include "Unknown/UserInterface/Interaction/OrganCutterWidget.h"
#include "Unknown/UserInterface/Interaction/RinseObjectsWidget.h"


void UPlayerInventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

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
	
	LeftArrowButton->OnClicked.AddDynamic(this, &UPlayerInventoryWidget::OnLeftArrowClicked);
	RightArrowButton->OnClicked.AddDynamic(this, &UPlayerInventoryWidget::OnRightArrowClicked);

	WBP_RinseTool->SetVisibility(ESlateVisibility::Collapsed);
}

void UPlayerInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerInventoryWidget::UpdateWidget()
{
	
}


void UPlayerInventoryWidget::OnLeftArrowClicked()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->RotatePlayerCameraLeft();

		if (PlayerCharacter->TagInFocus.Contains("Cut"))
		{
			WBP_OrganCutter->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			WBP_OrganCutter->SetVisibility(ESlateVisibility::Collapsed);
		}
		if (PlayerCharacter->TagInFocus.Contains("Rinse"))
		{
			WBP_RinseTool->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			WBP_RinseTool->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlayerInventoryWidget: PlayerCharacter not valid."));
	}
}

void UPlayerInventoryWidget::OnRightArrowClicked()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->RotatePlayerCameraRight();

		/*if (PlayerCharacter->CameraComp->GetComponentRotation() == FRotator(0,0,0))
		{
			WBP_OrganCutter->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			WBP_OrganCutter->SetVisibility(ESlateVisibility::Collapsed);
		}*/

		if (PlayerCharacter->TagInFocus.Contains("Cut"))
		{
			WBP_OrganCutter->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			WBP_OrganCutter->SetVisibility(ESlateVisibility::Collapsed);
		}
		if (PlayerCharacter->TagInFocus.Contains("Rinse"))
		{
			WBP_RinseTool->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			WBP_RinseTool->SetVisibility(ESlateVisibility::Collapsed);
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlayerInventoryWidget: PlayerCharacter not valid."));
	}
}
