#include "PlayerInventoryWidget.h"

#include "Components/Button.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"


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
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlayerInventoryWidget: PlayerCharacter not valid."));
	}
}
