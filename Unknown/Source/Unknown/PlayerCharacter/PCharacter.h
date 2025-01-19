#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "PCharacter.generated.h"

class AMonster;
class AToyInspector;
class AUnknownHUD;
class APController;
class USpringArmComponent;
class UCameraComponent;
class AOrganRinse;

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

	void StartInteraction();

	void StopInteraction();

	void RotatePlayerCameraLeft();

	void RotatePlayerCameraRight();
	

	// PROPERTIES & VARIABLES
	// -----------------------------
	
	UPROPERTY()
	APController* PlayerController;
	
	UPROPERTY(EditAnywhere)
	AUnknownHUD* HUD;

	UPROPERTY()
	AOrganRinse* OrganRinse;

	UPROPERTY()
	AToyInspector* ToyInspector;

	UPROPERTY()
	AMonster* Monster;

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

	void CheckForInteraction();

	// PROPERTIES & VARIABLES
	// -----------------------------

	const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes{ObjectTypeQuery2};
	
	FVector LineTraceStart;

	float CheckInteractionDistance;
	
	float SwatCount;

	UPROPERTY()
	TArray<AActor*> Actors;
	
	FTimerHandle MonsterTimerHandle;

	
};
