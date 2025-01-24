#include "InteractionWidget.h"

#include "Components/Slider.h"


void UInteractionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InteractionProgressBar->SetValue(0.f);
}

void UInteractionWidget::UpdateWidget(const TArray<FName> Tags)
{
}

