#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OrganCutter.generated.h"

class AUnknownHUD;
class APCharacter;
class APController;
class UBoxComponent;
class UStaticMeshComponent;
class UStaticMesh;

UCLASS()
class ORGAN_API AOrganCutter: public APawn
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	
	AOrganCutter();
	
	virtual void BeginPlay() override;

	void CloseAndDestroy();

	void SwapOrganMesh();
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UStaticMesh*> ExtraOrgans;

	
};
