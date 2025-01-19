#include "OrganCutterWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/UnknownGameInstance.h"
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

	GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());
	
	OrganCutterSlider->OnValueChanged.AddDynamic(this, &UOrganCutterWidget::CloseAndDestroy);
	OrganSlider2->OnValueChanged.AddDynamic(this, &UOrganCutterWidget::CloseAndDestroy);
	OrganSlider3->OnValueChanged.AddDynamic(this, &UOrganCutterWidget::CloseAndDestroy);
	ExtrudeOrganButton->OnClicked.AddDynamic(this, &UOrganCutterWidget::ExtrudeNewOrgan);

	OrganImage->SetVisibility(ESlateVisibility::Hidden);
	OrganImage2->SetVisibility(ESlateVisibility::Hidden);
	OrganImage3->SetVisibility(ESlateVisibility::Hidden);
	OrganImage4->SetVisibility(ESlateVisibility::Hidden);

	OrganCutterSlider->SetVisibility(ESlateVisibility::Hidden);
	OrganSlider2->SetVisibility(ESlateVisibility::Hidden);
	OrganSlider3->SetVisibility(ESlateVisibility::Hidden);

	bOrganExtruded = false;
	bOrganDissected = false;

	if (GameInstance)
	{
		GameInstance->bOrganExtruded = bOrganExtruded;
		GameInstance->bOrganDissected = bOrganDissected;
	}
	
}

void UOrganCutterWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UOrganCutterWidget::ExtrudeNewOrgan()
{
	UE_LOG(LogTemp, Warning, TEXT("UOrganCutterWidget: Extrude Organ!"));
	
	OrganImage->SetVisibility(ESlateVisibility::Visible);
	OrganImage2->SetVisibility(ESlateVisibility::Hidden);
	OrganImage3->SetVisibility(ESlateVisibility::Hidden);
	OrganImage4->SetVisibility(ESlateVisibility::Hidden);

	OrganCutterSlider->SetVisibility(ESlateVisibility::Visible);
	OrganSlider2->SetVisibility(ESlateVisibility::Hidden);
	OrganSlider3->SetVisibility(ESlateVisibility::Hidden);

	bOrganExtruded = true;

	if (GameInstance)
	{
		GameInstance->bOrganExtruded = bOrganExtruded;
	}
}

void UOrganCutterWidget::CloseAndDestroy(float Value)
{
	if (bOrganExtruded && OrganCutterSlider->GetValue() >= 1 && OrganImage->IsVisible())
	{
		OrganImage->SetVisibility(ESlateVisibility::Hidden);
		OrganImage2->SetVisibility(ESlateVisibility::Visible);
		OrganImage3->SetVisibility(ESlateVisibility::Visible);
		
		OrganCutterSlider->SetVisibility(ESlateVisibility::Hidden);
		OrganSlider2->SetVisibility(ESlateVisibility::Visible);
		OrganSlider3->SetVisibility(ESlateVisibility::Visible);
	}
	if (bOrganExtruded && OrganSlider2->GetValue() >= 1 && OrganImage2->IsVisible())
	{
		OrganSlider2->SetVisibility(ESlateVisibility::Hidden);
		OrganImage2->SetVisibility(ESlateVisibility::Hidden);

		if (!OrganSlider2->IsVisible() && !OrganSlider3->IsVisible() && !OrganImage->IsVisible())
		{
			OrganImage4->SetVisibility(ESlateVisibility::Visible);
		}
	}
	if (bOrganExtruded && OrganSlider3->GetValue() >= 1 && OrganImage3->IsVisible())
	{
		OrganSlider3->SetVisibility(ESlateVisibility::Hidden);
		OrganImage3->SetVisibility(ESlateVisibility::Hidden);

		if (!OrganSlider2->IsVisible() && !OrganSlider3->IsVisible() && !OrganImage->IsVisible())
		{
			OrganImage4->SetVisibility(ESlateVisibility::Visible);
			
			bOrganDissected = true;

			if (GameInstance)
			{
				GameInstance->bOrganDissected = bOrganDissected;
			}
		}
	}
}

void UOrganCutterWidget::ResetCutter()
{
	OrganImage->SetVisibility(ESlateVisibility::Hidden);
	OrganImage2->SetVisibility(ESlateVisibility::Hidden);
	OrganImage3->SetVisibility(ESlateVisibility::Hidden);
	OrganImage4->SetVisibility(ESlateVisibility::Hidden);

	OrganCutterSlider->SetVisibility(ESlateVisibility::Hidden);
	OrganSlider2->SetVisibility(ESlateVisibility::Hidden);
	OrganSlider3->SetVisibility(ESlateVisibility::Hidden);

	OrganCutterSlider->SetValue(0.f);
	OrganSlider2->SetValue(0.f);
	OrganSlider3->SetValue(0.f);

	bOrganExtruded = false;

	if (GameInstance)
	{
		GameInstance->bOrganExtruded = bOrganExtruded;
	}
}
