#pragma once

#include "CoreMinimal.h"
#include "Brushes/SlateImageBrush.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "Unknown/Data/ItemInterface.h"
#include "Unknown/Data/ItemDataStructs.h"
#include "OrganRinse.generated.h"

class UUnknownGameInstance;
class UPlayerInventoryWidget;
class URinseObjectsWidget;
struct FSlateImageBrush;
class AUnknownHUD;
class APCharacter;
class APController;
class UBoxComponent;
class UStaticMeshComponent;
class UStaticMesh;
class UMaterialInstance;
class UTimelineComponent;
class UCurveFloat;
class UDataTable;

UCLASS()
class AOrganRinse : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	AOrganRinse();
	
	virtual void BeginPlay() override;

	void CloseAndDestroy();

	void SpawnOrgansToRinse();

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	AUnknownHUD* HUD;

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;

	UPROPERTY()
	UUnknownGameInstance* GameInstance;

	UPROPERTY()
	URinseObjectsWidget* RinseObjectsWidget;

	UPROPERTY()
	UPlayerInventoryWidget* PlayerInventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName OrganTag;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DissolveTimelineCurveFloat;

	float DissolveProgressValue;

	FOnTimelineEvent OnTimelineEnd;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* DissolveTimelineComp;

	FOnTimelineFloat UpdateFunctionFloat;

	// From ItemDataStructs

	UPROPERTY(EditAnywhere, Category="Item Data")
	UDataTable* ToyDataTable;

	UPROPERTY(EditAnywhere, Category="Item Data")
	TArray<FName> AllToyIDs;
	
	UPROPERTY(EditAnywhere, Category="Item Data")
	FName DesiredToyID;

	UPROPERTY(EditAnywhere, Category="Item Data")
	int32 ToyQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ToyMeshComponent;

protected:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void UpdateTimelineComp(float Output);
	
	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* OrganProximityTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* OrganMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstance* OrganMaterialInstance;

	UPROPERTY()
	UTexture2D* IconBrushTexture;

	UPROPERTY()
	FText ToyNameText;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMeshComponent*> HiddenTreasures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SpawnedTreasure;*/
};
