#include "MonsterStateLoggerWidget.h"

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

		PlayerCharacter->OnMonsterStateUpdated.AddUObject(this, &UMonsterStateLoggerWidget::RefreshMonsterState);

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
	//UE_LOG(LogTemp, Warning, TEXT("UMonsterStateLoggerWidget: Broadcast received!"));
}
