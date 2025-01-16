#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "Unknown/DataAndInterface/ItemInterface.h"
#include "Unknown/DataAndInterface/ItemDataStructs.h"
#include "OrganRinse.generated.h"

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

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	AUnknownHUD* HUD;

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;

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

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMeshComponent*> HiddenTreasures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SpawnedTreasure;*/
};
