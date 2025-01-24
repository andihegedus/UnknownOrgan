#pragma once

#include "CoreMinimal.h"
#include "ToyInspector.generated.h"

class UBoxComponent;
class UUnknownGameInstance;
class AUnknownHUD;
class APCharacter;
class APController;
class UStaticMeshComponent;
class UMaterial;
class UAnimMontage;

UCLASS()
class ORGAN_API AToyInspector : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	AToyInspector();

	virtual void BeginPlay() override;

	void RotateToy();

	void StopRotateToy();

	UFUNCTION()
	void SwapMesh(FText ID);
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ToyTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName HitBoxTag;

	UPROPERTY(EditAnywhere, Category="Item Data")
	UDataTable* ToyDataTable;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FName DesiredToyID;

	
protected:

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ToyMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* ToyHitBoxExtender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* ToyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* ToyAnimMontage;
	
};
