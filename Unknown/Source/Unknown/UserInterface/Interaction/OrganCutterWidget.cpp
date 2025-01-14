#include "OrganCutterWidget.h"

#include "Components/Image.h"
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

	OrganCutterSlider->OnValueChanged.AddDynamic(this, &UOrganCutterWidget::CloseAndDestroy);
	OrganSlider2->OnValueChanged.AddDynamic(this, &UOrganCutterWidget::CloseAndDestroy);
	OrganSlider3->OnValueChanged.AddDynamic(this, &UOrganCutterWidget::CloseAndDestroy);

	OrganImage->SetVisibility(ESlateVisibility::Visible);
	OrganImage2->SetVisibility(ESlateVisibility::Collapsed);
	OrganImage3->SetVisibility(ESlateVisibility::Collapsed);
	OrganImage4->SetVisibility(ESlateVisibility::Collapsed);

	OrganCutterSlider->SetVisibility(ESlateVisibility::Visible);
	OrganSlider2->SetVisibility(ESlateVisibility::Collapsed);
	OrganSlider3->SetVisibility(ESlateVisibility::Collapsed);
}

void UOrganCutterWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UOrganCutterWidget::UpdateWidget()
{
}

void UOrganCutterWidget::CloseAndDestroy(float Value)
{
	if (OrganCutterSlider->GetValue() >= 1 && OrganImage->IsVisible())
	{
		OrganImage->SetVisibility(ESlateVisibility::Collapsed);
		OrganImage2->SetVisibility(ESlateVisibility::Visible);
		OrganImage3->SetVisibility(ESlateVisibility::Visible);
		
		OrganCutterSlider->SetVisibility(ESlateVisibility::Collapsed);
		OrganSlider2->SetVisibility(ESlateVisibility::Visible);
		OrganSlider3->SetVisibility(ESlateVisibility::Visible);
	}
	if (OrganSlider2->GetValue() >= 1 && OrganImage2->IsVisible())
	{
		OrganSlider2->SetVisibility(ESlateVisibility::Collapsed);
		OrganImage2->SetVisibility(ESlateVisibility::Hidden);

		if (!OrganSlider2->IsVisible() && !OrganSlider3->IsVisible() && !OrganImage->IsVisible())
		{
			OrganImage4->SetVisibility(ESlateVisibility::Visible);
		}
	}
	if (OrganSlider3->GetValue() >= 1 && OrganImage3->IsVisible())
	{
		OrganSlider3->SetVisibility(ESlateVisibility::Collapsed);
		OrganImage3->SetVisibility(ESlateVisibility::Hidden);

		if (!OrganSlider2->IsVisible() && !OrganSlider3->IsVisible() && !OrganImage->IsVisible())
		{
			OrganImage4->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UOrganCutterWidget: Slider value is less than 1, image cannot be destroyed."));
	}
}
