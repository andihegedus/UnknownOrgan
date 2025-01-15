#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "OrganRinse.generated.h"

class AUnknownHUD;
class APCharacter;
class APController;
class UBoxComponent;
class UStaticMeshComponent;
class UStaticMesh;

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

	void DissolveOrgan();

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

	

	
	
};
