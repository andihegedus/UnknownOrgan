#include "SaveLoadWidget.h"

#include "Components/Button.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"
#include "Unknown/System/UnknownHUD.h"


void ORGAN_API USaveLoadWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerCharacter)
	{
		PlayerController = Cast<APController>(PlayerCharacter->GetWorld()->GetFirstPlayerController());

		GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());

		HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

		if (PlayerController)
		{
			UE_LOG(LogTemp, Warning, TEXT("USaveLoadWidget: PlayerController valid!"));
			PlayerController->bShowMouseCursor = true;
			PlayerController->bEnableClickEvents = true; 
			PlayerController->bEnableMouseOverEvents = true;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("USaveLoadWidget: PlayerController not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USaveLoadWidget: PlayerCharacter not valid."));
	}

	NewGameButton->OnClicked.AddDynamic(this, &USaveLoadWidget::NewGame);
	LoadGameButton->OnClicked.AddDynamic(this, &USaveLoadWidget::LoadGame);
}

void USaveLoadWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void USaveLoadWidget::NewGame()
{
	if (GameInstance)
	{
		GameInstance->CreateSaveFile();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USaveLoadWidget: GameInstance not valid."));
	}

	if (HUD)
	{
		HUD->ShowHideSaveLoadWidget();
	}
}

void USaveLoadWidget::LoadGame()
{
	if (GameInstance)
	{
		GameInstance->LoadGame();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("USaveLoadWidget: GameInstance not valid."));
	}

	if (HUD)
	{
		HUD->ShowHideSaveLoadWidget();
	}
}
