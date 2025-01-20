#include "MonsterStateLoggerWidget.h"

#include "Components/TextBlock.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/ActivityStations/DefendStation/Monster.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"

void UMonsterStateLoggerWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerController = Cast<APController>(PlayerCharacter->GetWorld()->GetFirstPlayerController());

		GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());

		PlayerCharacter->OnMonsterStateUpdated.AddUObject(this, &UMonsterStateLoggerWidget::RefreshMonsterState);

		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("UMonsterStateLoggerWidget: PlayerController valid!"));
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true; 
			PlayerController->bEnableMouseOverEvents = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("UMonsterStateLoggerWidget: PlayerController not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMonsterStateLoggerWidget: PlayerCharacter valid!"));
	}
}

void UMonsterStateLoggerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMonsterStateLoggerWidget::SetStateText() const
{

}

void UMonsterStateLoggerWidget::RefreshMonsterState()
{
	if (GameInstance)
	{
		if (GameInstance->MonsterPositionID == 1)
		{
			this->SetVisibility(ESlateVisibility::HitTestInvisible);
			NewTextString = "...buzz...buzz...";
			MonsterStateText->SetText(FText::FromString(NewTextString));
		}
		else if (GameInstance->MonsterPositionID == 3)
		{
			this->SetVisibility(ESlateVisibility::HitTestInvisible);
			NewTextString = "A trinket is being stolen from your shelf! Act fast!";
			MonsterStateText->SetText(FText::FromString(NewTextString));
		}
		else
		{
			this->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UMonsterStateLoggerWidget: GameInstance not valid."));
	}
}
