#include "PlayerInventoryWidget.h"

#include "ShelfInventoryWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"
#include "Unknown/UserInterface/Interaction/MonsterStateLoggerWidget.h"
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

	CutText->SetVisibility(ESlateVisibility::Visible);
	RinseText->SetVisibility(ESlateVisibility::Collapsed);
	DefendText->SetVisibility(ESlateVisibility::Collapsed);
	TestText->SetVisibility(ESlateVisibility::Collapsed);

	CutBorder->SetBrushColor(FLinearColor::Red);
	RinseBorder->SetBrushColor(FLinearColor::Gray);
	DefendBorder->SetBrushColor(FLinearColor::Gray);
	TestBorder->SetBrushColor(FLinearColor::Gray);

	OrganCutter->SetVisibility(ESlateVisibility::Visible);
	RinseTool->SetVisibility(ESlateVisibility::Collapsed);
	ShelfInventory->SetVisibility(ESlateVisibility::Collapsed);
	MonsterStateLogger->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerInventoryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
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
			OrganCutter->SetVisibility(ESlateVisibility::Visible);
			CutText->SetVisibility(ESlateVisibility::Visible);
			CutBorder->SetBrushColor(FLinearColor::Red);
		}
		else
		{
			OrganCutter->ResetCutter();
			CutText->SetVisibility(ESlateVisibility::Collapsed);
			CutBorder->SetBrushColor(FLinearColor::Gray);
		}
		if (PlayerCharacter->TagInFocus.Contains("Rinse") || PlayerCharacter->TagInFocus.Contains("ToRinse"))
		{
			OrganCutter->SetVisibility(ESlateVisibility::Hidden);
			RinseText->SetVisibility(ESlateVisibility::Visible);
			RinseBorder->SetBrushColor(FLinearColor::Blue);
		}
		else
		{
			RinseText->SetVisibility(ESlateVisibility::Collapsed);
			RinseBorder->SetBrushColor(FLinearColor::Gray);
		}
		if (PlayerCharacter->CameraComp->GetComponentRotation() == FRotator(0,180,0))
		{
			DefendText->SetVisibility(ESlateVisibility::Visible);
			DefendBorder->SetBrushColor(FLinearColor::Yellow);
		}
		else
		{
			DefendText->SetVisibility(ESlateVisibility::Collapsed);
			DefendBorder->SetBrushColor(FLinearColor::Gray);
		}
		if (PlayerCharacter->TagInFocus.Contains("Test") || PlayerCharacter->TagInFocus.Contains("ToInspect"))
		{
			OrganCutter->SetVisibility(ESlateVisibility::Hidden);
			ShelfInventory->SetVisibility(ESlateVisibility::Visible);
			TestText->SetVisibility(ESlateVisibility::Visible);
			TestBorder->SetBrushColor(FLinearColor::Green);
		}
		else
		{
			ShelfInventory->SetVisibility(ESlateVisibility::Collapsed);
			TestText->SetVisibility(ESlateVisibility::Collapsed);
			TestBorder->SetBrushColor(FLinearColor::Gray);
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

		if (PlayerCharacter->TagInFocus.Contains("Cut"))
		{
			OrganCutter->SetVisibility(ESlateVisibility::Visible);
			CutText->SetVisibility(ESlateVisibility::Visible);
			CutBorder->SetBrushColor(FLinearColor::Red);
		}
		else
		{
			OrganCutter->ResetCutter();
			CutText->SetVisibility(ESlateVisibility::Collapsed);
			CutBorder->SetBrushColor(FLinearColor::Gray);
		}
		if (PlayerCharacter->TagInFocus.Contains("Rinse"))
		{
			OrganCutter->SetVisibility(ESlateVisibility::Hidden);
			RinseText->SetVisibility(ESlateVisibility::Visible);
			RinseBorder->SetBrushColor(FLinearColor::Blue);
		}
		else
		{
			RinseText->SetVisibility(ESlateVisibility::Collapsed);
			RinseBorder->SetBrushColor(FLinearColor::Gray);
		}
		if (PlayerCharacter->CameraComp->GetComponentRotation() == FRotator(0,180,0))
		{
			DefendText->SetVisibility(ESlateVisibility::Visible);
			DefendBorder->SetBrushColor(FLinearColor::Yellow);
			
		}
		else
		{
			DefendText->SetVisibility(ESlateVisibility::Collapsed);
			DefendBorder->SetBrushColor(FLinearColor::Gray);
		}
		if (PlayerCharacter->TagInFocus.Contains("Test") || PlayerCharacter->TagInFocus.Contains("ToInspect"))
		{
			//ShelfInventory->UpdateWidget();
			OrganCutter->SetVisibility(ESlateVisibility::Hidden);
			ShelfInventory->SetVisibility(ESlateVisibility::Visible);
			TestText->SetVisibility(ESlateVisibility::Visible);
			TestBorder->SetBrushColor(FLinearColor::Green);
		}
		else
		{
			ShelfInventory->SetVisibility(ESlateVisibility::Collapsed);
			TestText->SetVisibility(ESlateVisibility::Collapsed);
			TestBorder->SetBrushColor(FLinearColor::Gray);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UPlayerInventoryWidget: PlayerCharacter not valid."));
	}
}
