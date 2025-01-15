#pragma once

#include "CoreMinimal.h"
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

protected:
	// FUNCTIONS
	// -----------------------------

	UFUNCTION()
	void OnMouseOverlapBegin(class UPrimitiveComponent* OverlappedComp);
	
	// PROPERTIES & VARIABLES
	// -----------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* OrganProximityTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* OrganMeshComponent;

	
	
};
