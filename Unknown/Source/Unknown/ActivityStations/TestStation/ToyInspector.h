﻿#pragma once

#include "CoreMinimal.h"
#include "ToyInspector.generated.h"

class UUnknownGameInstance;
class AUnknownHUD;
class APCharacter;
class APController;
class UStaticMeshComponent;
class UMaterial;
class UAnimMontage;

UCLASS()
class AToyInspector : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	AToyInspector();

	virtual void BeginPlay() override;

	void RotateToy();

	void StopRotateToy();
	
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

	
protected:

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ToyMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterial* ToyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* ToyAnimMontage;
	
};