#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PCharacter.generated.h"


class AUnknownHUD;

UCLASS()
class UNKNOWN_API APCharacter: public ACharacter
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------

	APCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void OpenCloseWidget();
	
	void OpenShelfInventory();

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY(EditAnywhere)
	AUnknownHUD* HUD;
};
