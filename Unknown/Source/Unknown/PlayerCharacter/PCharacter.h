#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PCharacter.generated.h"

class AUnknownHUD;
class APController;
class USpringArmComponent;
class UCameraComponent;

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

	void RotatePlayerCameraLeft();

	void RotatePlayerCameraRight();

	// PROPERTIES & VARIABLES
	// -----------------------------
	
	UPROPERTY()
	APController* PlayerController;
	
	UPROPERTY(EditAnywhere)
	AUnknownHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	USpringArmComponent* SpringArmComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera");
	UCameraComponent* CameraComp;

	FRotator PlayerCameraRotation;

	UPROPERTY(VisibleAnywhere)
	TArray<FName> TagInFocus;
	
	UPROPERTY(VisibleAnywhere)
	FName CurrentTag;

	


protected:
	// FUNCTIONS
	// -----------------------------
	
	void CheckForInteractable();
	void FoundInteractable();

	// PROPERTIES & VARIABLES
	// -----------------------------

	FVector LineTraceStart;

	float CheckInteractionDistance;
};
