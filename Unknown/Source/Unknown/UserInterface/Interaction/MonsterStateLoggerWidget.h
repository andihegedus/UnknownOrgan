#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MonsterStateLoggerWidget.generated.h"

class AMonster;
class UTextBlock;
class UHorizontalBox;
class APCharacter;
class APController;

UCLASS()
class UNKNOWN_API UMonsterStateLoggerWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	// FUNCTIONS
	// -----------------------------

	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;
	
	void SetStateText() const;

	void RefreshMonsterState();

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;

	UPROPERTY()
	AMonster* Monster;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* MonsterStateText;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UHorizontalBox* StateBox;
};
