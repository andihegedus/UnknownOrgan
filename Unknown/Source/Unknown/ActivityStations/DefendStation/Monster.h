#pragma once

#include "CoreMinimal.h"
#include "Monster.generated.h"

UCLASS()
class AMonster : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	AMonster();

	virtual void BeginPlay() override;

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
	FName MonsterTag;

protected:

	// PROPERTIES & VARIABLES
	// -----------------------------

	// It was a mesh!
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MonsterMeshComponent;
	
};
